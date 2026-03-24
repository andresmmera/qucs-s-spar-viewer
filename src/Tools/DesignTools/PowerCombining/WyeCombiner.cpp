/// @file WyeCombiner.cpp
/// @brief Direct N-way Wye resistive power splitter (implementation)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Mar 24, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later
///
/// Design equation:
///   R = Z0 * (N - 1) / (N + 1)

#include "WyeCombiner.h"
#include <cmath>

void WyeCombiner::synthesize() {
    // Design equations
    N = Specification.Noutputs;
    R = Specification.Z0 * static_cast<double>(N - 1) /
        static_cast<double>(N + 1);

    // Place components
    buildWye();
}


void WyeCombiner::setComponentsLocation() {
    //   Port_in --[R_in]-- Node --[R1]-- Port1   ← top output(s)
    //                        |----[R2]-- Port2
    //                        :
    //                        └----[Rk]-- Portk   ← bottom output(s)

    // Spacing between components
    x_spacing = 60;
    y_spacing = 60;

    // Input port
    QPoint Port_in = QPoint(-25, -100);
    Ports_pos.push_back(Port_in); // [0]

    // Input resistor
    QPoint Rin = QPoint(Port_in.x() + x_spacing, Port_in.y());
    R_pos.append(Rin);


    // Output resistors, nodes and ports
    double y_ini = Port_in.y();
    for (int i = 0; i < Specification.Noutputs; i++){
        QPoint N = QPoint(Rin.x() + x_spacing, y_ini + i*y_spacing);
        QPoint Ri = QPoint(N.x() + x_spacing, y_ini + i*y_spacing);
        QPoint Porti =  QPoint(Ri.x() + x_spacing, y_ini + i*y_spacing);

        N_pos.append(N);
        R_pos.append(Ri);
        Ports_pos.append(Porti);
    }

}

void WyeCombiner::buildWye() {
    // Define components' location
    setComponentsLocation();

    // Input port
    ComponentInfo TermSpar1(QString("T1"), Term, Ports_pos[0]);
    TermSpar1.val["Z"] = num2str(Specification.Z0, Resistance);
    Schematic.appendComponent(TermSpar1);

    // Input resistor
    ComponentInfo R1(QString("R1"), Resistor, 90, R_pos[0]);
    R1.val["R"] = num2str(R, Resistance);
    Schematic.appendComponent(R1);

    // Wire between input port and resistor
    Schematic.appendWire(TermSpar1.ID, 0, R1.ID, 0);

    ComponentInfo Rout, PortOut;
    NodeInfo Nout;
    // Output resistors, nodes and ports
    for (int i = 0; i < Specification.Noutputs; i++){

        // Output node
        QString N_ID = QString("N%1").arg(i+2);
        Nout.setParams(N_ID, N_pos[i]);
        Schematic.appendNode(Nout);

        // Output resistor
        QString R_ID = QString("R%1").arg(i+2);
        Rout.setParams(R_ID, Resistor, 90, R_pos[i+1]);
        Rout.val["R"] = num2str(R, Resistance);
        Schematic.appendComponent(Rout);

        // Output port
        QString Port_ID = QString("T%1").arg(i+2);
        PortOut.setParams(Port_ID, Term, 180,  Ports_pos[i+1]);
        PortOut.val["Z"] = num2str(Specification.Z0, Resistance);
        Schematic.appendComponent(PortOut);

        // Wire node to resistor
        Schematic.appendWire(N_ID, 0, R_ID, 0);

        // Wire resistor to port
        Schematic.appendWire(R_ID, 1, Port_ID, 0);

        if (i == 0){
            // Wire the first output branch to the input resistor
            Schematic.appendWire(N_ID, 0, R1.ID, 1);
        } else {
            // Wire current node to the previous node
            QString previous_node_ID = QString("N%1").arg(i+1);
            Schematic.appendWire(previous_node_ID, 0, N_ID, 0);
        }
    }

}
