/// @file DeltaCombiner.h
/// @brief Delta resistive power splitter (definition)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Mar 24, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#ifndef DELTACOMBINER_H
#define DELTACOMBINER_H

#include "Misc/general.h"
#include "Schematic/Network.h"
#include "Schematic/component.h"

/// @class DeltaCombiner
/// @brief Delta resistive power splitter
/// @details The Delta resistive combiner is a network of three resistors connected
/// in Delta shape. It could be implemented for N-outputs, but the layout would be a mesh.
/// For this reason, it is only implemented with two outputs, giving a power split of 6 dB
/// The resistors are all Z0
///
///
/// This value simultaneously matches all ports to Z0 and splits power equally.
///
///   Port_in ----[R0]-------- Port2
///            |        |
///            |       [R0]
///            |        |
///            └--[R0]-------- Port3
///
/// [1] https://www.microwaves101.com/encyclopedias/resistive-power-splitters
class DeltaCombiner : public Network {
public:
    /// @brief Default constructor
    DeltaCombiner() {}

    /// @brief Constructor with power combiner parameters
    /// @param params Power combiner specification parameters
    DeltaCombiner(PowerCombinerParams PS) { Specification = PS; }

    /// @brief Destructor
    virtual ~DeltaCombiner() {}

    /// @brief Synthesize the Wye resistive splitter network
    void synthesize() override;

private:
    /// @brief Power combiner specifications
    struct PowerCombinerParams Specification;

    /// @brief Set component locations for schematic layout
    void setComponentsLocation();

    /// Component spacing parameters
    int x_spacing;  ///< Horizontal spacing between components
    int y_spacing;  ///< Vertical spacing between components

    /// Port locations
    QVector<QPoint> Ports_pos;

    /// Resistors positions
    QVector<QPoint> R_pos;

    /// Nodes positions
    QVector<QPoint> N_pos;
};

#endif // DELTACOMBINER_H
