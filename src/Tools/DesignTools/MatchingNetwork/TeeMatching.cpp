/// @file TeeMatching.cpp
/// @brief Tee-section matching network synthesis (implementation)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 6, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

// Reference: RF Design Guide – Systems, Circuits and Equations.
//            Peter Vizmuller, Artech House, 1995.

#include "TeeMatching.h"

// ---------------------------------------------------------------------------
// Synthesis of X1, B1, X2
// ---------------------------------------------------------------------------
//
// Topology overview:
//
//   ZS ---[X1]---+---[X2]--- ZL
//                |
//               [B1]  (combined susceptance from both L-section halves)
//                |
//               GND
//
// The network is decomposed into two back-to-back L-sections that meet at a
// real intermediate resistance Rv = (Q²+1)·min(RS, RL).
//
// 1st half  (source side, Z0 < Rv):
//
//   RS ---[X1]---+--- Rv
//                |
//               [B1a]
//                |
//               GND
//
// 2nd half  (load side, Rv > RL):
//
//   Rv ---+---[X2]--- ZL
//         |
//        [B1b]
//         |
//        GND
//
// The shunt elements share the centre node, so B1 = B1a + B1b.

void TeeMatching::computeReactances(double &X1, double &B1, double &X2) const {
    const double RS = Specs.Z0;
    const double RL = Specs.ZL.real();
    const double XL = Specs.ZL.imag();

    // Virtual intermediate (real) resistance – always > both RS and RL
    const double Rv = (Q * Q + 1.0) * std::min(RS, RL);

    // ------------------------------------------------------------------
    // 1st L-section: RS → Rv  (always RS < Rv, so series-then-shunt form)
    //
    //   RS ---[X1]---+--- Rv
    //                |
    //               [B1a]
    //
    // LP solution: positive B (cap shunt), positive X (ind series)
    // HP solution: negative B (ind shunt), negative X (cap series)
    // ------------------------------------------------------------------
    const double B1a_LP =
        (std::sqrt(Rv / RS) * std::sqrt(Rv * Rv - RS * Rv)) / (Rv * Rv);
    const double X1_LP = 1.0 / B1a_LP + RS / Rv - RS / (B1a_LP * Rv);

    const double B1a_HP = -B1a_LP;
    const double X1_HP = 1.0 / B1a_HP + RS / Rv - RS / (B1a_HP * Rv);

    // ------------------------------------------------------------------
    // 2nd L-section: Rv → ZL  (always Rv > RL, so shunt-then-series form)
    //
    //   Rv ---+---[X2]--- ZL
    //         |
    //        [B1b]
    //
    // LP solution: positive B (cap shunt), positive X (ind series)
    // HP solution: negative B (ind shunt), negative X (cap series)
    // ------------------------------------------------------------------
    const double X2_LP = std::sqrt(RL * (Rv - RL)) - XL;
    const double B1b_LP = std::sqrt((Rv - RL) / RL) / Rv;

    const double X2_HP = -std::sqrt(RL * (Rv - RL)) - XL;
    const double B1b_HP = -std::sqrt((Rv - RL) / RL) / Rv;

    // ------------------------------------------------------------------
    // Combine according to the selected topology mask
    // ------------------------------------------------------------------
    switch (Mask) {
    case TeeNetworkMask::LP_LP:
        X1 = X1_LP;
        B1 = B1a_LP + B1b_LP;
        X2 = X2_LP;
        break;
    case TeeNetworkMask::LP_HP:
        X1 = X1_LP;
        B1 = B1a_LP + B1b_HP;
        X2 = X2_HP;
        break;
    case TeeNetworkMask::HP_LP:
        X1 = X1_HP;
        B1 = B1a_HP + B1b_LP;
        X2 = X2_LP;
        break;
    case TeeNetworkMask::HP_HP:
        X1 = X1_HP;
        B1 = B1a_HP + B1b_HP;
        X2 = X2_HP;
        break;
    }
}

// ---------------------------------------------------------------------------
// Schematic builder
// ---------------------------------------------------------------------------
void TeeMatching::synthesize() {
    const double w0 = 2.0 * M_PI * f_match;

    // Compute reactive element values
    double X1, B1, X2;
    computeReactances(X1, B1, X2);

    // ------------------------------------------------------------------
    // Port 1 termination
    // ------------------------------------------------------------------
    ComponentInfo TermSpar1(
        QString("T%1").arg(++Schematic.NumberComponents[Term]), Term, 0, 0, 0);
    TermSpar1.val["Z"] = num2str(Specs.Z0, Resistance);
    Schematic.appendComponent(TermSpar1);

    // ------------------------------------------------------------------
    // Load impedance (constant or from S-parameter file)
    // ------------------------------------------------------------------
    ComponentInfo Zload;
    if (Specs.sim_path.isEmpty()) {
        Zload.setParams(
            QString("Z%1").arg(++Schematic.NumberComponents[ComplexImpedance]),
            ComplexImpedance, 0, 225, 50);
        Zload.val["Z"] = num2str(Specs.ZL, Resistance);
    } else {
        Zload.setParams(
            QString("SPAR%1").arg(++Schematic.NumberComponents[SPAR_Block]),
            SPAR_Block, -90, 225, 50);
        Zload.val["Path"] = Specs.sim_path;
    }
    Schematic.appendComponent(Zload);

    // GND for load
    ComponentInfo GND_ZL;
    GND_ZL.setParams(QString("GND_ZL%1").arg(++Schematic.NumberComponents[GND]),
                     GND, 0, 225, 100);
    Schematic.appendComponent(GND_ZL);

    // ------------------------------------------------------------------
    // Series element X1  (between port 1 and centre node)
    // ------------------------------------------------------------------
    ComponentInfo SeriesX1;
    if (X1 < 0.0) {
        // Capacitor:  X = -1/(w·C)  →  C = -1/(w·X)
        const double C = -1.0 / (w0 * X1);
        SeriesX1.setParams(
            QString("C%1").arg(++Schematic.NumberComponents[Capacitor]), Capacitor,
            -90, 50, 0);
        SeriesX1.val["C"] = num2str(C, Capacitance);
    } else {
        // Inductor:  X = w·L  →  L = X/w
        const double L = X1 / w0;
        SeriesX1.setParams(
            QString("L%1").arg(++Schematic.NumberComponents[Inductor]), Inductor,
            -90, 50, 0);
        SeriesX1.val["L"] = num2str(L, Inductance);
    }
    Schematic.appendComponent(SeriesX1);

    // ------------------------------------------------------------------
    // Centre node
    // ------------------------------------------------------------------
    NodeInfo CentreNode;
    CentreNode.setParams(
        QString("N%1").arg(++Schematic.NumberComponents[ConnectionNodes]), 100,
        0);
    Schematic.appendNode(CentreNode);

    // ------------------------------------------------------------------
    // Shunt element B1  (at centre node, to GND)
    // ------------------------------------------------------------------
    ComponentInfo ShuntB1;
    ComponentInfo GND_Shunt;

    if (B1 > 0.0) {
        // Capacitor:  B = w·C  →  C = B/w
        const double C = B1 / w0;
        ShuntB1.setParams(
            QString("C%1").arg(++Schematic.NumberComponents[Capacitor]), Capacitor,
            0.0, 100, 50);
        ShuntB1.val["C"] = num2str(C, Capacitance);
    } else {
        // Inductor:  B = -1/(w·L)  →  L = -1/(w·B)
        const double L = -1.0 / (w0 * B1);
        ShuntB1.setParams(
            QString("L%1").arg(++Schematic.NumberComponents[Inductor]), Inductor, 0,
            100, 50);
        ShuntB1.val["L"] = num2str(L, Inductance);
    }
    Schematic.appendComponent(ShuntB1);

    GND_Shunt.setParams(
        QString("GND%1").arg(++Schematic.NumberComponents[GND]), GND, 0, 100,
        100);
    Schematic.appendComponent(GND_Shunt);

    // ------------------------------------------------------------------
    // Series element X2  (between centre node and load)
    // ------------------------------------------------------------------
    ComponentInfo SeriesX2;
    if (X2 < 0.0) {
        const double C = -1.0 / (w0 * X2);
        SeriesX2.setParams(
            QString("C%1").arg(++Schematic.NumberComponents[Capacitor]), Capacitor,
            -90, 150, 0);
        SeriesX2.val["C"] = num2str(C, Capacitance);
    } else {
        const double L = X2 / w0;
        SeriesX2.setParams(
            QString("L%1").arg(++Schematic.NumberComponents[Inductor]), Inductor,
            -90, 150, 0);
        SeriesX2.val["L"] = num2str(L, Inductance);
    }
    Schematic.appendComponent(SeriesX2);

    // ------------------------------------------------------------------
    // Wires
    //
    //  T1 ──[X1]──N1──[X2]── Zload
    //              |
    //             [B1]
    //              |
    //             GND
    // ------------------------------------------------------------------
    Schematic.appendWire(TermSpar1.ID, 0, SeriesX1.ID, 1);
    Schematic.appendWire(SeriesX1.ID, 0, CentreNode.ID, 0);
    Schematic.appendWire(CentreNode.ID, 0, ShuntB1.ID, 1);
    Schematic.appendWire(ShuntB1.ID, 0, GND_Shunt.ID, 0);
    Schematic.appendWire(CentreNode.ID, 0, SeriesX2.ID, 1);
    Schematic.appendWire(Zload.ID, 1, SeriesX2.ID, 0);
    Schematic.appendWire(Zload.ID, 0, GND_ZL.ID, 0);
}
