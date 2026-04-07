/// @file DoubleTappedResonatorMatching.cpp
/// @brief Double-tapped resonator matching network synthesis (implementation)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Apr 7, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "DoubleTappedResonatorMatching.h"

void DoubleTappedResonatorMatching::computeValues(double &L1, double &L2,
                                                  double &C1,
                                                  double &C2) const {
    const double w0 = 2.0 * M_PI * f_match;
    const double RS = Specs.Z0;
    const double RL = Specs.ZL.real();

    L2 = Ltap; // passed through directly

    L1 = RS / (w0 * Q);

    const double Qsq = Q * Q;
    const double Q2  = std::sqrt((RL / RS) * (Qsq + 1.0) - 1.0);

    const double Leq = (L1 * Qsq) / (1.0 + Qsq) + L2;
    const double Ceq = 1.0 / (w0 * w0 * Leq);

    C2 = Q2 / (w0 * RL);
    const double C2_ = C2 * (1.0 + Q2 * Q2) / (Q2 * Q2);
    C1 = (Ceq * C2_) / (C2_ - Ceq);
}

void DoubleTappedResonatorMatching::synthesize() {
    double L1, L2, C1, C2;
    computeValues(L1, L2, C1, C2);

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
    // Source-side node (junction of port 1, L1 shunt, and L2 series)
    // ------------------------------------------------------------------
    NodeInfo SourceNode;
    SourceNode.setParams(
        QString("N%1").arg(++Schematic.NumberComponents[ConnectionNodes]), 50, 0);
    Schematic.appendNode(SourceNode);

    // ------------------------------------------------------------------
    // Shunt L1  (source side, to GND)
    // ------------------------------------------------------------------
    ComponentInfo ShuntL1;
    ShuntL1.setParams(
        QString("L%1").arg(++Schematic.NumberComponents[Inductor]), Inductor, 0,
        50, 50);
    ShuntL1.val["L"] = num2str(L1, Inductance);
    Schematic.appendComponent(ShuntL1);

    ComponentInfo GND_L1;
    GND_L1.setParams(QString("GND%1").arg(++Schematic.NumberComponents[GND]),
                     GND, 0, 50, 100);
    Schematic.appendComponent(GND_L1);

    // ------------------------------------------------------------------
    // Series L2 (Ltap)
    // ------------------------------------------------------------------
    ComponentInfo SeriesL2;
    SeriesL2.setParams(
        QString("L%1").arg(++Schematic.NumberComponents[Inductor]), Inductor,
        -90, 100, 0);
    SeriesL2.val["L"] = num2str(L2, Inductance);
    Schematic.appendComponent(SeriesL2);

    // ------------------------------------------------------------------
    // Series C1
    // ------------------------------------------------------------------
    ComponentInfo SeriesC1;
    SeriesC1.setParams(
        QString("C%1").arg(++Schematic.NumberComponents[Capacitor]), Capacitor,
        -90, 150, 0);
    SeriesC1.val["C"] = num2str(C1, Capacitance);
    Schematic.appendComponent(SeriesC1);

    // ------------------------------------------------------------------
    // Load-side node (junction of C1 series, C2 shunt, and load)
    // ------------------------------------------------------------------
    NodeInfo LoadNode;
    LoadNode.setParams(
        QString("N%1").arg(++Schematic.NumberComponents[ConnectionNodes]), 175,
        0);
    Schematic.appendNode(LoadNode);

    // ------------------------------------------------------------------
    // Shunt C2  (load side, to GND)
    // ------------------------------------------------------------------
    ComponentInfo ShuntC2;
    ShuntC2.setParams(
        QString("C%1").arg(++Schematic.NumberComponents[Capacitor]), Capacitor,
        0, 175, 50);
    ShuntC2.val["C"] = num2str(C2, Capacitance);
    Schematic.appendComponent(ShuntC2);

    ComponentInfo GND_C2;
    GND_C2.setParams(QString("GND%1").arg(++Schematic.NumberComponents[GND]),
                     GND, 0, 175, 100);
    Schematic.appendComponent(GND_C2);

    // ------------------------------------------------------------------
    // Wires
    //
    //  T1 ──N1──[L2]──[C1]──N2── Zload
    //       |                |
    //      [L1]             [C2]
    //       |                |
    //      GND              GND
    // ------------------------------------------------------------------
    Schematic.appendWire(TermSpar1.ID, 0, SourceNode.ID, 0);
    Schematic.appendWire(SourceNode.ID, 0, ShuntL1.ID, 1);
    Schematic.appendWire(ShuntL1.ID, 0, GND_L1.ID, 0);
    Schematic.appendWire(SourceNode.ID, 0, SeriesL2.ID, 1);
    Schematic.appendWire(SeriesL2.ID, 0, SeriesC1.ID, 1);
    Schematic.appendWire(SeriesC1.ID, 0, LoadNode.ID, 0);
    Schematic.appendWire(LoadNode.ID, 0, ShuntC2.ID, 1);
    Schematic.appendWire(ShuntC2.ID, 0, GND_C2.ID, 0);
    Schematic.appendWire(Zload.ID, 1, LoadNode.ID, 0);
    Schematic.appendWire(Zload.ID, 0, GND_ZL.ID, 0);
}
