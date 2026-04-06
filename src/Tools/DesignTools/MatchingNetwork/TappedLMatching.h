/// @file TappedLMatching.h
/// @brief Tapped-L transformer matching network synthesis (definition)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Mar 30, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#ifndef TAPPEDLMATCHING_H
#define TAPPEDLMATCHING_H

#include "Schematic/Network.h"
#include "Schematic/component.h"

/// @class TappedLMatching
/// @brief Tapped-L transformer matching network synthesis
///
/// Always shunt-series-shunt. The series element is always L1.
/// Which shunt arm is C and which is L2 depends on the impedance ratio:
///
/// RS >= RL  (step-down):          RS < RL  (step-up, RS/RL swapped):
///
///   ZS ---+---[L1]---+--- ZL        ZS ---+---[L1]---+--- ZL
///         |          |                    |           |
///        [C]        [L2]                [L2]         [C]
///         |          |                    |           |
///        GND        GND                 GND          GND
///
/// Design equations (after swapping RS/RL when RL > RS):
///   Q2 = sqrt((RL/RS)·(Q²+1) − 1)
///   C  = Q / (w0·RS)
///   L2 = RL / (Q2·w0)
///   L1 = L2·(Q·Q2 − Q2²) / (Q2²+1)
class TappedLMatching : public Network {
public:
    TappedLMatching() {}

    /// @param AS   Design specifications (Z0 = RS, ZL.real() = RL)
    /// @param freq Matching frequency in Hz
    /// @param Q    Loaded Q factor
    TappedLMatching(MatchingNetworkDesignParameters AS, double freq, double Q)
        : Specs(AS), f_match(freq), Q(Q) {}

    virtual ~TappedLMatching() {}

    void synthesize();

private:
    /// @param[out] C      Shunt capacitance (F)
    /// @param[out] L1     Series inductance (H)
    /// @param[out] L2     Shunt inductance (H)
    /// @param[out] stepUp True when the original RL > RS (roles swapped)
    void computeValues(double &C, double &L1, double &L2, bool &stepUp) const;

    MatchingNetworkDesignParameters Specs;
    double f_match;
    double Q;
};

#endif // TAPPEDLMATCHING_H
