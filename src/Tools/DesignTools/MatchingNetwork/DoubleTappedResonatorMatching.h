/// @file DoubleTappedResonatorMatching.h
/// @brief Double-tapped resonator matching network synthesis (definition)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Apr 7, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#ifndef DOUBLETAPPEDRESONATORMATCHING_H
#define DOUBLETAPPEDRESONATORMATCHING_H

#include "Schematic/Network.h"
#include "Schematic/component.h"

/// @class DoubleTappedResonatorMatching
/// @brief Double-tapped resonator matching network synthesis
///
/// Topology (fixed, no LP/HP mask):
///
///   ZS ---+---[L2]---[C1]---+--- ZL
///         |                 |
///        [L1]              [C2]
///         |                 |
///        GND               GND
///
/// L2 (Ltap) is a user-specified series inductor that forms part of a
/// resonant tank with C1.  L1 and C2 are determined by the Q and the
/// impedance ratio.
///
/// Design equations:
///   L1  = RS / (w0·Q)
///   Q2  = sqrt((RL/RS)·(Q²+1) − 1)
///   Leq = L1·Q² / (1+Q²) + L2
///   Ceq = 1 / (w0²·Leq)
///   C2  = Q2 / (w0·RL)
///   C2' = C2·(1+Q2²) / Q2²
///   C1  = Ceq·C2' / (C2' − Ceq)
class DoubleTappedResonatorMatching : public Network {
public:
    DoubleTappedResonatorMatching() {}

    /// @param AS   Design specifications (Z0 = RS, ZL.real() = RL)
    /// @param freq Matching frequency in Hz
    /// @param Q    Loaded Q factor
    /// @param Ltap User-specified series inductor L2 (H)
    DoubleTappedResonatorMatching(MatchingNetworkDesignParameters AS, double freq,
                                  double Q, double Ltap)
    : Specs(AS), f_match(freq), Q(Q), Ltap(Ltap) {}

    virtual ~DoubleTappedResonatorMatching() {}

    void synthesize();

private:
    /// @param[out] L1  Shunt inductance (H)
    /// @param[out] L2  Series inductance = Ltap (H), passed through unchanged
    /// @param[out] C1  Series capacitance (F)
    /// @param[out] C2  Shunt capacitance (F)
    void computeValues(double &L1, double &L2, double &C1, double &C2) const;

    MatchingNetworkDesignParameters Specs;
    double f_match; ///< Matching frequency (Hz)
    double Q;       ///< Loaded Q factor
    double Ltap;    ///< User-specified series inductor (H)
};

#endif // DOUBLETAPPEDRESONATORMATCHING_H
