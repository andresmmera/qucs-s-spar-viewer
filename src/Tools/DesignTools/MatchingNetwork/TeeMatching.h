/// @file TeeMatching.h
/// @brief Tee-section matching network synthesis (definition)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 6, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#ifndef TEEMATCHING_H
#define TEEMATCHING_H

#include "Schematic/Network.h"
#include "Schematic/component.h"

/// @brief Tee network topology mask: selects which combination of
///        LP/HP sub-sections is used for the two halves of the Tee.
///
/// The Tee network is built from two back-to-back L-sections that share a
/// virtual intermediate resistance Rv.  Each half can independently be a
/// low-pass (LP) or high-pass (HP) L-section, giving four combinations:
///
///  | Mask | 1st half | 2nd half |
///  |------|----------|----------|
///  |  1   |   LP     |   LP     |
///  |  2   |   LP     |   HP     |
///  |  3   |   HP     |   LP     |
///  |  4   |   HP     |   HP     |
enum class TeeNetworkMask : int {
    LP_LP = 1, ///< Both halves low-pass
    LP_HP = 2, ///< 1st half low-pass, 2nd half high-pass
    HP_LP = 3, ///< 1st half high-pass, 2nd half low-pass
    HP_HP = 4  ///< Both halves high-pass
};

/// @class TeeMatching
/// @brief Tee-section matching network synthesis
///
/// The Tee topology uses a series-shunt-series arrangement:
/// @code
///   ZS ---[X1]---+---[X2]--- ZL
///                |
///               [B1]
///                |
///               GND
/// @endcode
///
/// The virtual intermediate resistance Rv = (Q²+1)·min(ZS, ZL) controls the
/// loaded Q.  Each half is solved as an L-section; the two shunt susceptances
/// are then combined at the centre node.
///
/// Reference: RF Design Guide – Systems, Circuits and Equations.
///            Peter Vizmuller, Artech House, 1995.
class TeeMatching : public Network {
public:
    /// @brief Default constructor
    TeeMatching() {}

    /// @brief Constructor with parameters
    /// @param AS  Design specifications (Z0, ZL, Solution field unused here)
    /// @param freq Matching frequency in Hz
    /// @param Q   Loaded Q factor (must be > Qmin = sqrt(max/min impedance − 1))
    /// @param mask Topology selection (LP_LP, LP_HP, HP_LP, HP_HP)
    TeeMatching(MatchingNetworkDesignParameters AS, double freq, double Q,
                TeeNetworkMask mask)
    : Specs(AS), f_match(freq), Q(Q), Mask(mask) {}

    /// @brief Destructor
    virtual ~TeeMatching() {}

    /// @brief Calculate component values and build the schematic
    void synthesize();

private:
    /// @brief Solve the two L-section halves and return X1, B1_combined, X2.
    ///
    /// @param[out] X1  Series reactance of the source-side L-section
    /// @param[out] B1  Combined shunt susceptance at the centre node
    /// @param[out] X2  Series reactance of the load-side L-section
    void computeReactances(double &X1, double &B1, double &X2) const;

    MatchingNetworkDesignParameters Specs; ///< Design specifications
    double f_match;                        ///< Matching frequency (Hz)
    double Q;                              ///< Loaded Q factor
    TeeNetworkMask Mask;                   ///< LP/HP topology mask
};

#endif // TEEMATCHING_H
