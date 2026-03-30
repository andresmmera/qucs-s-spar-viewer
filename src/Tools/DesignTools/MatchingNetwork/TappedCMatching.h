/// @file TappedCMatching.h
/// @brief Tapped-C transformer matching network synthesis (definition)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Mar 30, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#ifndef TAPPEDCMATCHING_H
#define TAPPEDCMATCHING_H

#include "Schematic/Network.h"
#include "Schematic/component.h"

/// @class TappedCMatching
/// @brief Tapped-C transformer matching network synthesis
///
/// The topology is always shunt-series-shunt. Which shunt arm is L and
/// which is C2 depends on the impedance ratio:
///
/// RS >= RL  (step-down):          RS < RL  (step-up, RS/RL swapped):
///
///   ZS ---+---[C1]---+--- ZL        ZS ---+---[C1]---+--- ZL
///         |          |                    |           |
///        [L]        [C2]                [C2]         [L]
///         |          |                    |           |
///        GND        GND                 GND          GND
///
/// Design equations (after swapping RS/RL when RL > RS):
///   Q2 = sqrt((RL/RS)·(Q²+1) − 1)
///   L  = RS / (w0·Q)
///   C2 = Q2 / (RL·w0)
///   C1 = C2·(Q2²+1) / (Q·Q2 − Q2²)
class TappedCMatching : public Network {
public:
    TappedCMatching() {}

    /// @param AS   Design specifications (Z0 = RS, ZL.real() = RL)
    /// @param freq Matching frequency in Hz
    /// @param Q    Loaded Q factor
    TappedCMatching(MatchingNetworkDesignParameters AS, double freq, double Q)
    : Specs(AS), f_match(freq), Q(Q) {}

    virtual ~TappedCMatching() {}

    void synthesize();

private:
    /// @brief Compute L, C1, C2 component values.
    /// @param[out] L   Shunt inductance (H)
    /// @param[out] C1  Series capacitance (F)
    /// @param[out] C2  Shunt capacitance (F)
    /// @param[out] stepUp  True when the original RL > RS (roles are swapped)
    void computeValues(double &L, double &C1, double &C2, bool &stepUp) const;

    MatchingNetworkDesignParameters Specs;
    double f_match;
    double Q;
};

#endif // TAPPEDCMATCHING_H
