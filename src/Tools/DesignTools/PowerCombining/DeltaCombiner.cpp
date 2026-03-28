/// @file DeltaCombiner.cpp
/// @brief Delta resistive power splitter (implementation)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Mar 24, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "DeltaCombiner.h"
#include <cmath>

void DeltaCombiner::synthesize() {

    // Define components' location
    setComponentsLocation();

    double R = Specification.Z0;

    // Input port
    ComponentInfo TermSpar1(QString("T1"), Term, Ports_pos[0]);
    TermSpar1.val["Z"] = num2str(Specification.Z0, Resistance);
    Schematic.appendComponent(TermSpar1);

    // Input node
    NodeInfo N0(QString("N0"), N_pos[0]);
    Schematic.appendNode(N0);

    // Top resistor
    ComponentInfo Rtop(QString("R1"), Resistor, 90, R_pos[0]);
    Rtop.val["R"] = num2str(R, Resistance);
    Schematic.appendComponent(Rtop);

    // Top output node
    NodeInfo N1(QString("N1"), N_pos[1]);
    Schematic.appendNode(N1);

    // Top output port
    ComponentInfo TermSparTop(QString("T2"), Term, 180, Ports_pos[1]);
    TermSparTop.val["Z"] = num2str(Specification.Z0, Resistance);
    Schematic.appendComponent(TermSparTop);

    // Bottom resistor
    ComponentInfo Rbot(QString("R2"), Resistor, 90, R_pos[1]);
    Rbot.val["R"] = num2str(R, Resistance);
    Schematic.appendComponent(Rbot);

    // Bottom output node
    NodeInfo N2(QString("N2"), N_pos[2]);
    Schematic.appendNode(N2);

    // Bottom output port
    ComponentInfo TermSparBottom(QString("T3"), Term, 180, Ports_pos[2]);
    TermSparBottom.val["Z"] = num2str(Specification.Z0, Resistance);
    Schematic.appendComponent(TermSparBottom);

    // Isolation resistor
    ComponentInfo Riso(QString("R3"), Resistor, 0, R_pos[2]);
    Riso.val["R"] = num2str(R, Resistance);
    Schematic.appendComponent(Riso);

    // Wiring

    // Input port to first node
    Schematic.appendWire(TermSpar1.ID, 0, N0.ID, 0);

    // First node to top resistor
    Schematic.appendWire(N0.ID, 0, Rtop.ID, 0);

    // Top resistor to output node
    Schematic.appendWire(Rtop.ID, 1, N1.ID, 0);

    // Top output node to top output port
    Schematic.appendWire(N1.ID, 0, TermSparTop.ID, 0);

    // First node to bottom resistor
    Schematic.appendWire(N0.ID, 0, Rbot.ID, 0);

    // Bottom resistor to bottom output node
    Schematic.appendWire(Rbot.ID, 1, N2.ID, 0);

    // Bottom output node to bottom output port
    Schematic.appendWire(N2.ID, 0, TermSparBottom.ID, 0);

    // Top output node to isolation resistor
    Schematic.appendWire(N1.ID, 0, Riso.ID, 1);

    // Bottom output node to isolation resistor
    Schematic.appendWire(N2.ID, 0, Riso.ID, 0);
}


void DeltaCombiner::setComponentsLocation() {
    ///   Port_in ----[Rtop]---------- Port2
    ///            |          |
    ///            |         [Riso]
    ///            |          |
    ///            └--[Rbot]---------- Port3

    // Spacing between components
    x_spacing = 60;
    y_spacing = 60;

    // Input port
    QPoint Port_in = QPoint(-25, -100);
    Ports_pos.push_back(Port_in);

    QPoint Node_in = QPoint(Port_in.x() + x_spacing, Port_in.y());
    N_pos.append(Node_in);

    // Top resistor
    QPoint Rtop = QPoint(Node_in.x() + x_spacing, Port_in.y());
    R_pos.append(Rtop);

    // Node top outpout
    QPoint Node_out1 = QPoint(Rtop.x() + x_spacing, Port_in.y());
    N_pos.append(Node_out1);

    // Top output port
    QPoint Port_out1 = QPoint(Node_out1.x() + x_spacing, Port_in.y());
    Ports_pos.push_back(Port_out1);

    // Bottom resistor
    QPoint Rbottom = QPoint(Rtop.x(), Port_in.y() + 2*y_spacing);
    R_pos.append(Rbottom);

    // Node bottom outpout
    QPoint Node_out2 = QPoint(Rbottom.x() + x_spacing, Port_in.y() + 2*y_spacing);
    N_pos.append(Node_out2);

    // Bottom output port
    QPoint Port_out2 = QPoint(Node_out2.x() + x_spacing, Port_in.y() + 2*y_spacing);
    Ports_pos.push_back(Port_out2);

    // Isolation resistor
    QPoint Riso = QPoint(Node_out2.x(), Port_in.y() + y_spacing);
    R_pos.append(Riso);
}

