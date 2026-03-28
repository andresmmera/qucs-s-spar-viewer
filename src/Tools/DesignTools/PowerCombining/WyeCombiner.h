/// @file WyeCombiner.h
/// @brief Direct N-way Wye resistive power splitter (definition)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Mar 24, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#ifndef WYECOMBINER_H
#define WYECOMBINER_H

#include "Misc/general.h"
#include "Schematic/Network.h"
#include "Schematic/component.h"

/// @class WyeCombiner
/// @brief Direct N-way Wye resistive power splitter
/// @details The Wye splitter is the simplest N-way power divider. It connects an input
/// port to N output ports through N resistors, whose values are:
///
///   R = Z0 * (N - 1) / (N + 1)
///
/// This value simultaneously matches all ports to Z0 and splits power equally.
/// The network is inherently lossy: (N-1)/N of the input power is dissipated.
///
///   Port_in --[R_in]-- Node --[R1]-- Port1   ← top output(s)
///                        |----[R2]-- Port2
///                        :
///                        └----[Rk]-- Portk   ← bottom output(s)
/// [1] https://www.microwaves101.com/encyclopedias/resistive-power-splitters
class WyeCombiner : public Network {
public:
    /// @brief Default constructor
    WyeCombiner() {}

    /// @brief Constructor with power combiner parameters
    /// @param params Power combiner specification parameters
    WyeCombiner(PowerCombinerParams PS) { Specification = PS; }

    /// @brief Destructor
    virtual ~WyeCombiner() {}

    /// @brief Synthesize the Wye resistive splitter network
    void synthesize() override;

private:
    /// @brief Power combiner specifications
    struct PowerCombinerParams Specification;

    int    N; ///< Number of output ports
    double R; ///< Series arm resistor value: Z0*(N-1)/(N+1)

    /// @brief Build the resistive Wye schematic
    void buildWye();

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

#endif // WYECOMBINER_H
