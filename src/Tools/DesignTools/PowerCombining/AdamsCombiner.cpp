/// @file AdamsCombiner.cpp
/// @brief Adams unequal resistive power splitter (implementation)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Mar 24, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later


#include "AdamsCombiner.h"
#include <cmath>

void AdamsCombiner::synthesize() {

    // Define components' location
    setComponentsLocation();

    // Design equations (Adams 2007)
    double alpha = 1/Specification.OutputRatio[0]; //At this point, we get 10^(dB/20) because of the UI design. In order to have 10^(-dB/20), we need to invert
    double Rs   = (1.0 - alpha) / (1.0 + alpha);
    double Rp   = (1.0 - Rs*Rs) / (2.0*Rs);
    double Ru   = sqrt(1.0 / (1.0 - 4.0/(2.0*Rp + Rs + 1.0)));
    double Rt   = Rp - Ru/(Ru + 1.0);

    // Scale to system impedance
    double Z0 = Specification.Z0;
    Rs *= Z0;
    Ru *= Z0;
    Rt *= Z0;

    // Input port
    ComponentInfo TermSpar1(QString("T1"), Term, Ports_pos[0]);
    TermSpar1.val["Z"] = num2str(Specification.Z0, Resistance);
    Schematic.appendComponent(TermSpar1);

    // Input top resistor
    ComponentInfo Rtop1(QString("R1"), Resistor, 90, R_pos[0]);
    Rtop1.val["R"] = num2str(Rs, Resistance);
    Schematic.appendComponent(Rtop1);

    // Top output node
    NodeInfo N1(QString("N1"), N_pos[0]);
    Schematic.appendNode(N1);

    // Output top resistor
    ComponentInfo Rtop2(QString("R2"), Resistor, 90, R_pos[1]);
    Rtop2.val["R"] = num2str(Rs, Resistance);
    Schematic.appendComponent(Rtop2);

    // First output port
    ComponentInfo TermSpar2(QString("T2"), Term, 180, Ports_pos[1]);
    TermSpar2.val["Z"] = num2str(Specification.Z0, Resistance);
    Schematic.appendComponent(TermSpar2);

    // First shunt resistor
    ComponentInfo Rshunt1(QString("R3"), Resistor, 0, R_pos[2]);
    Rshunt1.val["R"] = num2str(Rt, Resistance);
    Schematic.appendComponent(Rshunt1);

    // Bottom output node
    NodeInfo N2(QString("N2"), N_pos[1]);
    Schematic.appendNode(N2);

    // Bottom output
    ComponentInfo TermSpar3(QString("T3"), Term, 180, Ports_pos[2]);
    TermSpar3.val["Z"] = num2str(Specification.Z0, Resistance);
    Schematic.appendComponent(TermSpar3);

    // Second shunt resistor
    ComponentInfo Rshunt2(QString("R4"), Resistor, 0, R_pos[3]);
    Rshunt2.val["R"] = num2str(Ru, Resistance);
    Schematic.appendComponent(Rshunt2);

    ComponentInfo Ground(QString("GND1"), GND, GND_pos);
    Schematic.appendComponent(Ground);

    // Wiring
    // Input port to the first top resistor
    Schematic.appendWire(TermSpar1.ID, 0, Rtop1.ID, 0);

    // First top resistor to top node
    Schematic.appendWire(Rtop1.ID, 1, N1.ID, 0);

    // Top node to output resistor
    Schematic.appendWire(N1.ID, 0, Rtop2.ID, 0);

    // Output resistor to top output port
    Schematic.appendWire(Rtop2.ID, 1, TermSpar2.ID, 0);

    // First shunt resistor to top node
    Schematic.appendWire(Rshunt1.ID, 1, N1.ID, 0);

    // First shunt resistor to bottom node
    Schematic.appendWire(Rshunt1.ID, 0, N2.ID, 0);

    // Bottom node to output port
    Schematic.appendWire(N2.ID, 0, TermSpar3.ID, 0);

    // Bottom node to bottom shunt resistor
    Schematic.appendWire(N2.ID, 0, Rshunt2.ID, 1);

    // Bottom shunt resistor to ground
    Schematic.appendWire(Rshunt2.ID, 0, Ground.ID, 0);
}


void AdamsCombiner::setComponentsLocation() {

    ///   Port_in --- [Rtop1] - [N1]---- [Rtop2] --- Port_out1
    ///                          |
    ///                       [Rshunt1]
    ///                          |
    ///                         [N2] ------------- Port_out2
    ///                          |
    ///                       [Rshunt2]
    ///                          |
    ///                         ---
    ///

    // Spacing between components
    x_spacing = 60;
    y_spacing = 60;

    // Input port
    QPoint Port_in = QPoint(-25, -100);
    Ports_pos.push_back(Port_in);

    // Top input resistor
    QPoint Rtop1 = QPoint(Port_in.x() + x_spacing, Port_in.y());
    R_pos.append(Rtop1);

    // Node top output
    QPoint N1 = QPoint(Rtop1.x() + x_spacing, Port_in.y());
    N_pos.append(N1);

    // Top output resistor
    QPoint Rtop2 = QPoint(N1.x() + x_spacing, Port_in.y());
    R_pos.append(Rtop2);

    // Top output port
    QPoint Port_out1 = QPoint(Rtop2.x() + x_spacing, Rtop2.y());
    Ports_pos.push_back(Port_out1);

    // First shunt resistor
    QPoint Rshunt1 = QPoint(N1.x(), Port_in.y() + y_spacing);
    R_pos.append(Rshunt1);

    // Second node
    QPoint N2 = QPoint(Rshunt1.x(), Rshunt1.y() + y_spacing);
    N_pos.append(N2);

    // Bottom output port
    QPoint Port_out2 = QPoint(Port_out1.x(), N2.y());
    Ports_pos.push_back(Port_out2);

    // Second shunt resistor
    QPoint Rshunt2 = QPoint(N2.x(), N2.y() + y_spacing);
    R_pos.append(Rshunt2);

    GND_pos = QPoint(Rshunt2.x(), Rshunt2.y() + y_spacing);
}

