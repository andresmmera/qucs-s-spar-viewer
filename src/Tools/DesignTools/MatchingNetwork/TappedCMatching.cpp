/// @file TappedCMatching.cpp
/// @brief Tapped-C transformer matching network synthesis (implementation)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Mar 30, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "TappedCMatching.h"

void TappedCMatching::computeValues(double &L, double &C1, double &C2,
                                    bool &stepUp) const {
    const double w0 = 2.0 * M_PI * f_match;

    double RS = Specs.Z0;
    double RL = Specs.ZL.real();

    // When RL > RS the Python code swaps them; track this so the schematic
    // builder can place L and C2 on the correct sides.
    stepUp = (RL > RS);
    if (stepUp) std::swap(RS, RL);

    const double Q2 = std::sqrt((RL / RS) * (Q * Q + 1.0) - 1.0);
    L  = RS / (w0 * Q);
    C2 = Q2 / (RL * w0);
    C1 = C2 * (Q2 * Q2 + 1.0) / (Q * Q2 - Q2 * Q2);
}

void TappedCMatching::synthesize() {
    double L, C1, C2;
    bool stepUp;
    computeValues(L, C1, C2, stepUp);

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
    // Source-side shunt: L when RS >= RL (step-down), C2 when step-up
    // ------------------------------------------------------------------
    ComponentInfo ShuntSrc, GND_Src;

    if (!stepUp) {
        // Step-down: shunt L on source side
        ShuntSrc.setParams(
            QString("L%1").arg(++Schematic.NumberComponents[Inductor]), Inductor, 0,
            50, 50);
        ShuntSrc.val["L"] = num2str(L, Inductance);
    } else {
        // Step-up: shunt C2 on source side
        ShuntSrc.setParams(
            QString("C%1").arg(++Schematic.NumberComponents[Capacitor]), Capacitor,
            0, 50, 50);
        ShuntSrc.val["C"] = num2str(C2, Capacitance);
    }
    Schematic.appendComponent(ShuntSrc);

    GND_Src.setParams(QString("GND%1").arg(++Schematic.NumberComponents[GND]),
                      GND, 0, 50, 100);
    Schematic.appendComponent(GND_Src);

    // ------------------------------------------------------------------
    // Series C1
    // ------------------------------------------------------------------
    ComponentInfo SeriesC1;
    SeriesC1.setParams(
        QString("C%1").arg(++Schematic.NumberComponents[Capacitor]), Capacitor,
        -90, 100, 0);
    SeriesC1.val["C"] = num2str(C1, Capacitance);
    Schematic.appendComponent(SeriesC1);

    // ------------------------------------------------------------------
    // Load-side node
    // ------------------------------------------------------------------
    NodeInfo LoadNode;
    LoadNode.setParams(
        QString("N%1").arg(++Schematic.NumberComponents[ConnectionNodes]), 150,
        0);
    Schematic.appendNode(LoadNode);

    // ------------------------------------------------------------------
    // Load-side shunt: C2 when RS >= RL (step-down), L when step-up
    // ------------------------------------------------------------------
    ComponentInfo ShuntLoad, GND_Load;

    if (!stepUp) {
        // Step-down: shunt C2 on load side
        ShuntLoad.setParams(
            QString("C%1").arg(++Schematic.NumberComponents[Capacitor]), Capacitor,
            0, 150, 50);
        ShuntLoad.val["C"] = num2str(C2, Capacitance);
    } else {
        // Step-up: shunt L on load side
        ShuntLoad.setParams(
            QString("L%1").arg(++Schematic.NumberComponents[Inductor]), Inductor, 0,
            150, 50);
        ShuntLoad.val["L"] = num2str(L, Inductance);
    }
    Schematic.appendComponent(ShuntLoad);

    GND_Load.setParams(QString("GND%1").arg(++Schematic.NumberComponents[GND]),
                       GND, 0, 150, 100);
    Schematic.appendComponent(GND_Load);

    // ------------------------------------------------------------------
    // Wires
    //
    //  T1 ──N1──[C1]──N2── Zload
    //       |               |
    //   [L or C2]       [C2 or L]
    //       |               |
    //      GND             GND
    // ------------------------------------------------------------------
    Schematic.appendWire(TermSpar1.ID, 0, SourceNode.ID, 0);
    Schematic.appendWire(SourceNode.ID, 0, ShuntSrc.ID, 1);
    Schematic.appendWire(ShuntSrc.ID, 0, GND_Src.ID, 0);
    Schematic.appendWire(SourceNode.ID, 0, SeriesC1.ID, 1);
    Schematic.appendWire(SeriesC1.ID, 0, LoadNode.ID, 0);
    Schematic.appendWire(LoadNode.ID, 0, ShuntLoad.ID, 1);
    Schematic.appendWire(ShuntLoad.ID, 0, GND_Load.ID, 0);
    Schematic.appendWire(Zload.ID, 1, LoadNode.ID, 0);
    Schematic.appendWire(Zload.ID, 0, GND_ZL.ID, 0);
}
