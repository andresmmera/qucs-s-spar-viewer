/// @file TappedLMatching.cpp
/// @brief Tapped-L transformer matching network synthesis (implementation)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Mar 30, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "TappedLMatching.h"

void TappedLMatching::computeValues(double &C, double &L1, double &L2,
                                    bool &stepUp) const {
    const double w0 = 2.0 * M_PI * f_match;

    double RS = Specs.Z0;
    double RL = Specs.ZL.real();

    stepUp = (RL > RS);
    if (stepUp) std::swap(RS, RL);

    const double Q2 = std::sqrt((RL / RS) * (Q * Q + 1.0) - 1.0);
    C  = Q / (w0 * RS);
    L2 = RL / (Q2 * w0);
    L1 = L2 * (Q * Q2 - Q2 * Q2) / (Q2 * Q2 + 1.0);
}

void TappedLMatching::synthesize() {
    double C, L1, L2;
    bool stepUp;
    computeValues(C, L1, L2, stepUp);

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
            ComplexImpedance, 0, 200, 50);
        Zload.val["Z"] = num2str(Specs.ZL, Resistance);
    } else {
        Zload.setParams(
            QString("SPAR%1").arg(++Schematic.NumberComponents[SPAR_Block]),
            SPAR_Block, -90, 200, 50);
        Zload.val["Path"] = Specs.sim_path;
    }
    Schematic.appendComponent(Zload);

    ComponentInfo GND_ZL;
    GND_ZL.setParams(QString("GND_ZL%1").arg(++Schematic.NumberComponents[GND]),
                     GND, 0, 200, 100);
    Schematic.appendComponent(GND_ZL);

    // ------------------------------------------------------------------
    // Source-side node
    // ------------------------------------------------------------------
    NodeInfo SourceNode;
    SourceNode.setParams(
        QString("N%1").arg(++Schematic.NumberComponents[ConnectionNodes]), 50, 0);
    Schematic.appendNode(SourceNode);

    // ------------------------------------------------------------------
    // Source-side shunt: C when step-down, L2 when step-up
    // ------------------------------------------------------------------
    ComponentInfo ShuntSrc, GND_Src;

    if (!stepUp) {
        ShuntSrc.setParams(
            QString("C%1").arg(++Schematic.NumberComponents[Capacitor]), Capacitor,
            0, 50, 50);
        ShuntSrc.val["C"] = num2str(C, Capacitance);
    } else {
        ShuntSrc.setParams(
            QString("L%1").arg(++Schematic.NumberComponents[Inductor]), Inductor, 0,
            50, 50);
        ShuntSrc.val["L"] = num2str(L2, Inductance);
    }
    Schematic.appendComponent(ShuntSrc);

    GND_Src.setParams(QString("GND%1").arg(++Schematic.NumberComponents[GND]),
                      GND, 0, 50, 100);
    Schematic.appendComponent(GND_Src);

    // ------------------------------------------------------------------
    // Series L1
    // ------------------------------------------------------------------
    ComponentInfo SeriesL1;
    SeriesL1.setParams(
        QString("L%1").arg(++Schematic.NumberComponents[Inductor]), Inductor,
        -90, 100, 0);
    SeriesL1.val["L"] = num2str(L1, Inductance);
    Schematic.appendComponent(SeriesL1);

    // ------------------------------------------------------------------
    // Load-side node
    // ------------------------------------------------------------------
    NodeInfo LoadNode;
    LoadNode.setParams(
        QString("N%1").arg(++Schematic.NumberComponents[ConnectionNodes]), 150,
        0);
    Schematic.appendNode(LoadNode);

    // ------------------------------------------------------------------
    // Load-side shunt: L2 when step-down, C when step-up
    // ------------------------------------------------------------------
    ComponentInfo ShuntLoad, GND_Load;

    if (!stepUp) {
        ShuntLoad.setParams(
            QString("L%1").arg(++Schematic.NumberComponents[Inductor]), Inductor, 0,
            150, 50);
        ShuntLoad.val["L"] = num2str(L2, Inductance);
    } else {
        ShuntLoad.setParams(
            QString("C%1").arg(++Schematic.NumberComponents[Capacitor]), Capacitor,
            0, 150, 50);
        ShuntLoad.val["C"] = num2str(C, Capacitance);
    }
    Schematic.appendComponent(ShuntLoad);

    GND_Load.setParams(QString("GND%1").arg(++Schematic.NumberComponents[GND]),
                       GND, 0, 150, 100);
    Schematic.appendComponent(GND_Load);

    // ------------------------------------------------------------------
    // Wires
    //
    //  T1 ──N1──[L1]──N2── Zload
    //       |               |
    //   [C or L2]       [L2 or C]
    //       |               |
    //      GND             GND
    // ------------------------------------------------------------------
    Schematic.appendWire(TermSpar1.ID, 0, SourceNode.ID, 0);
    Schematic.appendWire(SourceNode.ID, 0, ShuntSrc.ID, 1);
    Schematic.appendWire(ShuntSrc.ID, 0, GND_Src.ID, 0);
    Schematic.appendWire(SourceNode.ID, 0, SeriesL1.ID, 1);
    Schematic.appendWire(SeriesL1.ID, 0, LoadNode.ID, 0);
    Schematic.appendWire(LoadNode.ID, 0, ShuntLoad.ID, 1);
    Schematic.appendWire(ShuntLoad.ID, 0, GND_Load.ID, 0);
    Schematic.appendWire(Zload.ID, 1, LoadNode.ID, 0);
    Schematic.appendWire(Zload.ID, 0, GND_ZL.ID, 0);
}
