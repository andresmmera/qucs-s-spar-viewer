/// @file AdamsCombiner.h
/// @brief Delta resistive power splitter (definition)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Mar 24, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#ifndef ADAMSCOMBINER_H
#define ADAMSCOMBINER_H

#include "Misc/general.h"
#include "Schematic/Network.h"
#include "Schematic/component.h"

/// @class AdamsCombiner
/// @brief Adams unequal resistive power splitter
/// @details The Adams unequal resistive combiner is a variant of the Wye
/// combiner for unequal power splitting, reported in [1]
///
///
///   Port_in --- [Rs] ----- [Rs] --- Port_out1
///                      |
///                     [Rt]
///                      |
///                      |------------ Port_out2
///                      |
///                     [Ru]
///                      |
///                     ---
///
/// References
/// [1] Greg Adams, "Designing Resistive Unequal Power Dividers", High Frequency Electronics. 2007
/// [2] https://www.microwaves101.com/encyclopedias/resistive-power-splitters
///
class AdamsCombiner : public Network {
public:
    /// @brief Default constructor
    AdamsCombiner() {}

    /// @brief Constructor with power combiner parameters
    /// @param params Power combiner specification parameters
    AdamsCombiner(PowerCombinerParams PS) { Specification = PS; }

    /// @brief Destructor
    virtual ~AdamsCombiner() {}

    /// @brief Synthesize the Wye resistive splitter network
    void synthesize() override;

private:
    /// @brief Power combiner specifications
    struct PowerCombinerParams Specification;

    int    N; ///< Number of output ports
    double R; ///< Series arm resistor value: Z0*(N-1)/(N+1)

    /// @brief Build the resistive Wye schematic
    void buildAdams();

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

    /// Position of the ground
    QPoint GND_pos;
};

#endif // ADAMSCOMBINER
