/// @file swr_s11_calculator.h
/// @brief Calculator:  (definition)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 28, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later
///
#ifndef SWR_S11_CALCULATOR_H
#define SWR_S11_CALCULATOR_H

#include <QDialog>
#include "UI/CustomWidgets/CustomDoubleSpinBox.h"
#include "Misc/general.h"

class CustomDoubleSpinBox;
class QLabel;
class QPushButton;
class QTableWidget;
class QGroupBox;
class QComboBox;


/// @class SwrS11CalculatorDialog
/// @brief Dialog for bidirectional conversion between SWR, S11, and reflection coefficient magnitude
///
/// @details The calculator uses the following RF engineering formulas:
/// - From VSWR: |Γ| = (VSWR - 1) / (VSWR + 1)
/// - From |Γ|: VSWR = (1 + |Γ|) / (1 - |Γ|)
/// - From |Γ|: S11 = 20 × log₁₀(|Γ|) dB
/// - From S11: |Γ| = 10^(S11/20)
class SwrS11CalculatorDialog : public QDialog {
    Q_OBJECT

public:
    /// @brief Constructor for the SWR/S11/|Γ| Calculator Dialog
    /// @param parent Pointer to parent widget (default: nullptr)
    explicit SwrS11CalculatorDialog(QWidget *parent = nullptr);

private slots:
     /// @brief Compute output parameters from current input values
    void computeResults();

    /// @brief Slot triggered when any input value changes
    void on_inputChanged();

    /// @brief Slot triggered when calculation mode combo changes
    void on_modeChanged(int index);

    /// @brief Slot to show the HTML reflection coefficient help
    void showDocumentation() {
        QString path = QString("/Calculators/ReflectionCoefficientTools/index.html");
        showHTMLDocs(path);
    }

private:
    /// @brief Enumeration for calculation modes
    enum CalculationMode {
        FROM_VSWR = 0,    ///< Calculate from VSWR input
        FROM_S11_DB = 1,  ///< Calculate from S11 (dB) input
        FROM_GAMMA = 2    ///< Calculate from |Γ| input
    };

    // ========== Input Widgets ==========

    /// @brief Combo box for selecting calculation mode
    ///
    /// @details Options:
    /// - "From VSWR"
    /// - "From S11 (dB)"
    /// - "From |Γ|"
    QComboBox *comboMode;

    /// @brief Spin box for VSWR input
    CustomDoubleSpinBox *spinVSWR;

    /// @brief Spin box for S11 (dB) input
    CustomDoubleSpinBox *spinS11dB;


    /// @brief Spin box for reflection coefficient magnitude |Γ|
    CustomDoubleSpinBox *spinGammaMag;

    /// @brief Label for the active input field
    QLabel *labelInput;

    /// @brief Input group box container
    QGroupBox *inputGroup;

    /// @brief Form layout for input widgets
    QFormLayout *inputForm;

    // ========== Output Widget ==========

    /// @brief Table widget displaying calculated results
    QTableWidget *resultsTable;

    // ========== Helper Methods ==========

    /// @brief Update UI visibility based on calculation mode
    void updateUIForMode();

    /// @brief Calculate |Γ| from VSWR
    /// @param vswr Value of the VSWR
    /// @return Magnitude of the reflection coefficient \in [0, 1]
    double gammaFromVSWR(double vswr) const;

    /// @brief Calculate VSWR from |Γ|
    /// @param gamma Reflection coefficient magnitude \in [0, 1]
    /// @return Voltage Standing Wave Ratio (≥ 1.0)
    double vswrFromGamma(double gamma) const;

    /// @brief  Calculate S11 (dB) from |Γ|
    /// @param gamma Reflection coefficient magnitude \in [0, 1]
    /// @return Return loss in dB
    double s11dBFromGamma(double gamma) const;

    /// @brief  Calculate |Γ| from S11 (dB)
    /// @param s11db Return loss in dB
    /// @return Reflection coefficient magnitude \in [0, 1]
    double gammaFromS11dB(double s11db) const;
};

#endif // SWR_S11_CALCULATOR_H
