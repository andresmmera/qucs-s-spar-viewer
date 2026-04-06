/// @file PiMatching.h
/// @brief Pi-section matching network synthesis (definition)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Mar 30, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#ifndef PIMATCHING_H
#define PIMATCHING_H

#include "Schematic/Network.h"
#include "Schematic/component.h"

/// @brief Pi network topology mask (same encoding as TeeNetworkMask)
///
/// The Pi network is built from two back-to-back L-sections sharing a
/// virtual intermediate resistance Rv.  Each half can independently be
/// low-pass (LP) or high-pass (HP):
///
///  | Mask | 1st half | 2nd half |
///  |------|----------|----------|
///  |  1   |   LP     |   LP     |
///  |  2   |   LP     |   HP     |
///  |  3   |   HP     |   LP     |
///  |  4   |   HP     |   HP     |
enum class PiNetworkMask : int {
    LP_LP = 1,
    LP_HP = 2,
    HP_LP = 3,
    HP_HP = 4
};

/// @class PiMatching
/// @brief Pi-section matching network synthesis
///
/// The Pi topology uses a shunt-series-shunt arrangement:
/// @code
///   ZS ---+---[X1]---+--- ZL
///         |          |
///        [B1]       [B2]
///         |          |
///        GND        GND
/// @endcode
///
/// Rv = max(ZS, ZL) / (Q²+1) is always smaller than both ZS and ZL.
///
/// Reference: Microwave and RF Design Networks. Steer, M. 2019.
///            North Carolina State University Libraries. Page 174.
class PiMatching : public Network {
public:
    PiMatching() {}

    /// @param AS   Design specifications
    /// @param freq Matching frequency in Hz
    /// @param Q    Loaded Q factor (must satisfy Q > sqrt(max/min − 1))
    /// @param mask Topology selection
    PiMatching(MatchingNetworkDesignParameters AS, double freq, double Q,
               PiNetworkMask mask)
    : Specs(AS), f_match(freq), Q(Q), Mask(mask) {}

    virtual ~PiMatching() {}

    void synthesize();

private:
    /// @brief Solve the two L-section halves and return B1, X1_combined, B2.
    void computeReactances(double &B1, double &X1, double &B2) const;

    MatchingNetworkDesignParameters Specs;
    double f_match;
    double Q;
    PiNetworkMask Mask;
};

#endif // PIMATCHING_H
