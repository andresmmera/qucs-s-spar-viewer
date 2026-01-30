/// @file gamma_calculator.h
/// @brief Calculator: Reflection coefficient (Γ) to Z, VSWR and S11 (definition)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 27, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later
///
#ifndef GAMMA_CALCULATOR_H
#define GAMMA_CALCULATOR_H

#include <QDialog>
#include <complex>
#include "UI/CustomWidgets/CustomDoubleSpinBox.h"

class CustomDoubleSpinBox;
class QLabel;
class QPushButton;
class QTableWidget;
class QGroupBox;



/// @class GammaCalculatorDialog
/// @brief Dialog for calculating impedance, VSWR, and S11 from reflection coefficient (Γ)
///
/// This dialog provides a user interface for converting a complex reflection coefficient (Γ)
/// into various impedance (Z), voltage standing wave ratio (VSWR), and S11 (dB).
///
/// @details Formulas:
/// - Impedance: Z = Z₀ × (1 + Γ) / (1 - Γ)
/// - VSWR: (1 + |Γ|) / (1 - |Γ|)
/// - S11: 20 × log₁₀(|Γ|) dB
class GammaCalculatorDialog : public QDialog {
    Q_OBJECT
public:
    /// @brief Calculator constructor
    /// @param parent Pointer to parent widget
    explicit GammaCalculatorDialog(QWidget *parent = nullptr);

private slots:
    /// @brief Compute the output parameters from the input data
    void computeResults();

    /// @brief Slot triggered when any input value changes
    void on_inputChanged();

private:
    // ========== Input Widgets ==========

    /// @brief Spin box for reflection coefficient magnitude |Γ|
    CustomDoubleSpinBox *spinMag;

    /// @brief Spin box for reflection coefficient angle ∠Γ in degrees
    CustomDoubleSpinBox *spinAngle;

    /// @brief Spin box for characteristic impedance Z₀ (in Ohms)
    CustomDoubleSpinBox *spinZ0;

    // Output
    /// @brief Table widget displaying calculated results
    /// @details Output rows:
    /// - Row 0: Re{Z} (Ω) - Real part of impedance
    /// - Row 1: Im{Z} (Ω) - Imaginary part of impedance
    /// - Row 2: VSWR - Voltage Standing Wave Ratio
    /// - Row 3: S₁₁ (dB) - Return loss
    QTableWidget *resultsTable;

    /// @brief Convert input values to complex reflection coefficient
    /// @return Complex number representing Γ = |Γ| × e^(j∠Γ)
    std::complex<double> gammaFromInputs() const;
};

#endif // GAMMA_CALCULATOR_H
