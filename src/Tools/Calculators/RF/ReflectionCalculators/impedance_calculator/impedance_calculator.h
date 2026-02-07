/// @file impedance_calculator.h
/// @brief Simple calculator: Impedance (Z) to Γ, VSWR and S11 (definition)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 27, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later
///
#ifndef IMPEDANCE_CALCULATOR_H
#define IMPEDANCE_CALCULATOR_H

#include <QDialog>
#include <complex>
#include "UI/CustomWidgets/CustomDoubleSpinBox.h"
#include "Misc/general.h"

class CustomDoubleSpinBox;
class QLabel;
class QPushButton;
class QTableWidget;
class QGroupBox;

/// @class ImpedanceCalculatorDialog
/// @brief Dialog for calculating reflection coefficient, VSWR, and S11 from a complex impedance (Z)
///
/// @details The calculator uses the following RF engineering formulas:
/// - Reflection Coefficient: Γ = (Z - Z₀) / (Z + Z₀)
/// - VSWR: (1 + |Γ|) / (1 - |Γ|)
/// - S11: 20 × log₁₀(|Γ|) dB
class ImpedanceCalculatorDialog : public QDialog {
    Q_OBJECT
    
public:
    /// @brief Constructor for the Impedance Calculator Dialog
    /// @param parent Pointer to parent widget (default: nullptr)
    explicit ImpedanceCalculatorDialog(QWidget *parent = nullptr);

private slots:

    /// @brief Compute the output parameters from the input data
    void computeResults();
    
    /// @brief Slot triggered when any input value changes
    void on_inputChanged();

    /// @brief Slot to show the HTML reflection coefficient help
    void showDocumentation() {
        QString path = QString("/Calculators/ReflectionCoefficientTools/index.html");
        showHTMLDocs(path);
    }

private:
    // ========== Input Widgets ==========

    /// @brief Spin box for real part of Z, Re{Z}
    CustomDoubleSpinBox *spinReZ;
    
    /// @brief Spin box for imaginary part of Z, Im{Z}
    CustomDoubleSpinBox *spinImZ;
    
    /// @brief Spin box for characteristic impedance Z₀ (in Ohms)
    CustomDoubleSpinBox *spinZ0;

    // ========== Output Widgets ==========
    
    // Output
    /// @brief Table widget displaying calculated results
    /// @details Output rows:
    /// - Row 0: Γ (|Γ| ∠ deg) - Reflection coefficient in polar form
    /// - Row 1: VSWR - Voltage Standing Wave Ratio
    /// - Row 2: S₁₁ (dB) - Return loss in decibels
    QTableWidget *resultsTable;

    /// @brief CGet complex impedance from input values
    /// @return Complex number representing Z = Re{Z} + j×Im{Z}
    std::complex<double> impedanceFromInputs() const;
};

#endif // IMPEDANCE_CALCULATOR_H
