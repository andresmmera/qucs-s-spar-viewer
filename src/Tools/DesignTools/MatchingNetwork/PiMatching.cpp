/// @file PiMatching.cpp
/// @brief Pi-section matching network synthesis (implementation)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Mar 30, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

// Reference: Microwave and RF Design Networks. Steer, M. 2019.
//            North Carolina State University Libraries. Page 174.

#include "PiMatching.h"

// ---------------------------------------------------------------------------
// Synthesis of B1, X1, B2
// ---------------------------------------------------------------------------
//
// Topology:
//
//   ZS ---+---[X1]---+--- ZL
//         |          |
//        [B1]       [B2]
//         |          |
//        GND        GND
//
// Rv = max(RS, RL) / (Q²+1)  — always smaller than both RS and RL.
//
// 1st half (source side, RS > Rv):
//
//   RS ---+---[X1a]--- Rv
//         |
//        [B1]
//
// 2nd half (load side, RL > Rv):
//
//   Rv ---[X1b]---+--- ZL
//                 |
//                [B2]
//
// The series elements share the centre branch, so X1 = X1a + X1b.

void PiMatching::computeReactances(double &B1, double &X1, double &B2) const {
    const double RS = Specs.Z0;
    const double RL = Specs.ZL.real();
    const double XL = Specs.ZL.imag();

    // Virtual intermediate resistance — always smaller than both RS and RL
    const double Rv = std::max(RS, RL) / (Q * Q + 1.0);

    // ------------------------------------------------------------------
    // 1st L-section: RS → Rv  (RS > Rv, shunt-then-series form)
    //
    //   RS ---+---[X1a]--- Rv       (XL of Rv = 0, pure real)
    //         |
    //        [B1]
    //
    // LP: positive B (cap shunt), positive X (ind series)
    // HP: negative B (ind shunt), negative X (cap series)
    // ------------------------------------------------------------------
    const double X1a_LP = std::sqrt(Rv * (RS - Rv));
    const double B1_LP  = std::sqrt((RS - Rv) / Rv) / RS;

    const double X1a_HP = -X1a_LP;
    const double B1_HP  = -B1_LP;

    // ------------------------------------------------------------------
    // 2nd L-section: Rv → ZL  (RL > Rv, series-then-shunt form)
    //
    //   Rv ---[X1b]---+--- ZL
    //                 |
    //                [B2]
    // ------------------------------------------------------------------
    const double B2_LP =
        (XL + std::sqrt(RL / Rv) * std::sqrt(RL * RL + XL * XL - Rv * RL)) /
        (RL * RL + XL * XL);
    const double X1b_LP = 1.0 / B2_LP + XL * Rv / RL - Rv / (B2_LP * RL);

    const double B2_HP =
        (XL - std::sqrt(RL / Rv) * std::sqrt(RL * RL + XL * XL - Rv * RL)) /
        (RL * RL + XL * XL);
    const double X1b_HP = 1.0 / B2_HP + XL * Rv / RL - Rv / (B2_HP * RL);

    // ------------------------------------------------------------------
    // Combine according to selected mask
    // ------------------------------------------------------------------
    switch (Mask) {
    case PiNetworkMask::LP_LP:
        B1 = B1_LP;  X1 = X1a_LP + X1b_LP;  B2 = B2_LP;
        break;
    case PiNetworkMask::LP_HP:
        B1 = B1_LP;  X1 = X1a_LP + X1b_HP;  B2 = B2_HP;
        break;
    case PiNetworkMask::HP_LP:
        B1 = B1_HP;  X1 = X1a_HP + X1b_LP;  B2 = B2_LP;
        break;
    case PiNetworkMask::HP_HP:
        B1 = B1_HP;  X1 = X1a_HP + X1b_HP;  B2 = B2_HP;
        break;
    }
}

// ---------------------------------------------------------------------------
// Schematic builder
// ---------------------------------------------------------------------------
void PiMatching::synthesize() {
    const double w0 = 2.0 * M_PI * f_match;

    double B1, X1, B2;
    computeReactances(B1, X1, B2);

    // ------------------------------------------------------------------
    // Port 1 termination
    // ------------------------------------------------------------------
    ComponentInfo TermSpar1(
        QString("T%1").arg(++Schematic.NumberComponents[Term]), Term, 0, 0, 0);
    TermSpar1.val["Z"] = num2str(Specs.Z0, Resistance);
    Schematic.appendComponent(TermSpar1);

    // ------------------------------------------------------------------
    // Load impedance
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

    ComponentInfo GND_ZL;
    GND_ZL.setParams(QString("GND_ZL%1").arg(++Schematic.NumberComponents[GND]),
                     GND, 0, 225, 100);
    Schematic.appendComponent(GND_ZL);

    // ------------------------------------------------------------------
    // Source-side node (between port 1 and B1)
    // ------------------------------------------------------------------
    NodeInfo SourceNode;
    SourceNode.setParams(
        QString("N%1").arg(++Schematic.NumberComponents[ConnectionNodes]), 50, 0);
    Schematic.appendNode(SourceNode);

    // ------------------------------------------------------------------
    // Shunt element B1  (at source node, to GND)
    // ------------------------------------------------------------------
    ComponentInfo ShuntB1;
    ComponentInfo GND_B1;

    if (B1 > 0.0) {
        const double C = B1 / w0;
        ShuntB1.setParams(
            QString("C%1").arg(++Schematic.NumberComponents[Capacitor]), Capacitor,
            0.0, 50, 50);
        ShuntB1.val["C"] = num2str(C, Capacitance);
    } else {
        const double L = -1.0 / (w0 * B1);
        ShuntB1.setParams(
            QString("L%1").arg(++Schematic.NumberComponents[Inductor]), Inductor, 0,
            50, 50);
        ShuntB1.val["L"] = num2str(L, Inductance);
    }
    Schematic.appendComponent(ShuntB1);

    GND_B1.setParams(QString("GND%1").arg(++Schematic.NumberComponents[GND]),
                     GND, 0, 50, 100);
    Schematic.appendComponent(GND_B1);

    // ------------------------------------------------------------------
    // Series element X1  (between source node and load node)
    // ------------------------------------------------------------------
    ComponentInfo SeriesX1;
    if (X1 < 0.0) {
        const double C = -1.0 / (w0 * X1);
        SeriesX1.setParams(
            QString("C%1").arg(++Schematic.NumberComponents[Capacitor]), Capacitor,
            -90, 100, 0);
        SeriesX1.val["C"] = num2str(C, Capacitance);
    } else {
        const double L = X1 / w0;
        SeriesX1.setParams(
            QString("L%1").arg(++Schematic.NumberComponents[Inductor]), Inductor,
            -90, 100, 0);
        SeriesX1.val["L"] = num2str(L, Inductance);
    }
    Schematic.appendComponent(SeriesX1);

    // ------------------------------------------------------------------
    // Load-side node (between X1 and B2)
    // ------------------------------------------------------------------
    NodeInfo LoadNode;
    LoadNode.setParams(
        QString("N%1").arg(++Schematic.NumberComponents[ConnectionNodes]), 150,
        0);
    Schematic.appendNode(LoadNode);

    // ------------------------------------------------------------------
    // Shunt element B2  (at load node, to GND)
    // ------------------------------------------------------------------
    ComponentInfo ShuntB2;
    ComponentInfo GND_B2;

    if (B2 > 0.0) {
        const double C = B2 / w0;
        ShuntB2.setParams(
            QString("C%1").arg(++Schematic.NumberComponents[Capacitor]), Capacitor,
            0.0, 150, 50);
        ShuntB2.val["C"] = num2str(C, Capacitance);
    } else {
        const double L = -1.0 / (w0 * B2);
        ShuntB2.setParams(
            QString("L%1").arg(++Schematic.NumberComponents[Inductor]), Inductor, 0,
            150, 50);
        ShuntB2.val["L"] = num2str(L, Inductance);
    }
    Schematic.appendComponent(ShuntB2);

    GND_B2.setParams(QString("GND%1").arg(++Schematic.NumberComponents[GND]),
                     GND, 0, 150, 100);
    Schematic.appendComponent(GND_B2);

    // ------------------------------------------------------------------
    // Wires
    //
    //  T1 ──N1──[X1]──N2── Zload
    //       |              |
    //      [B1]           [B2]
    //       |              |
    //      GND            GND
    // ------------------------------------------------------------------
    Schematic.appendWire(TermSpar1.ID, 0, SourceNode.ID, 0);
    Schematic.appendWire(SourceNode.ID, 0, ShuntB1.ID, 1);
    Schematic.appendWire(ShuntB1.ID, 0, GND_B1.ID, 0);
    Schematic.appendWire(SourceNode.ID, 0, SeriesX1.ID, 1);
    Schematic.appendWire(SeriesX1.ID, 0, LoadNode.ID, 0);
    Schematic.appendWire(LoadNode.ID, 0, ShuntB2.ID, 1);
    Schematic.appendWire(ShuntB2.ID, 0, GND_B2.ID, 0);
    Schematic.appendWire(Zload.ID, 1, LoadNode.ID, 0);
    Schematic.appendWire(Zload.ID, 0, GND_ZL.ID, 0);
}
