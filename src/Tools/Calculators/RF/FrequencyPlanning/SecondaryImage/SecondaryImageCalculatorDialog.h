/// @file SecondaryImageCalculatorDialog.h
/// @brief Secondary image frequency calculator (definition)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 31, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later


#ifndef SECONDARYIMAGECALCULATORDIALOG_H
#define SECONDARYIMAGECALCULATORDIALOG_H

#include <QDialog>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTableWidget>
#include "Misc/general.h"

/// @class SecondaryImageCalculatorDialog
/// @brief A dialog for calculating image frequencies in dual-conversion superheterodyne receivers
///
/// This calculator determines the local oscillator (LO) frequencies and image frequencies
/// for both stages of a dual-conversion receiver. It uses low-side injection for both stages.
///
/// For each conversion stage:
/// - LO frequency: f_LO = f_in - f_out
/// - Image frequency: f_IM = f_in - 2*f_out
///
/// Stage 1: RF → 1st IF
/// - f_LO1 = f_RF - f_IF1
/// - f_IM1 = f_LO1 - f_IF1
///
/// Stage 2: 1st IF → 2nd IF
/// - f_LO2 = f_IF1 - f_IF2
/// - f_IM2 = f_LO2 - f_IF2
class SecondaryImageCalculatorDialog : public QDialog
{
    Q_OBJECT

public:
    /// @brief Constructor
    /// @param parent Parent widget
    explicit SecondaryImageCalculatorDialog(QWidget *parent = nullptr);
    
    /// @brief Destructor
    ~SecondaryImageCalculatorDialog(){}

private slots:
    /// @brief Calculates all frequencies when any input changes
    /// @details Computes LO and image frequencies for both conversion stages.
    void calculate();

    /// @brief Shows the documentation for the secondary image frequency calculation
    void showDocumentation() {
        QString path = QString("/Calculators/SecondaryImageFrequency/index.html");
        showHTMLDocs(path);
    }

private:
    /// @brief Sets up the user interface
    void setupUI();
    
    /// @brief Formats frequency value for display
    /// @param freq Frequency value in MHz
    /// @return Formatted string with value and "MHz" unit
    QString formatFrequency(double freq) {
        return QString::number(freq, 'f', 1);
    }

    // UI Elements - Inputs
    QDoubleSpinBox* fIF1SpinBox;     ///< Spin box for 1st IF frequency (MHz)
    QDoubleSpinBox* fIF2SpinBox;     ///< Spin box for 2nd IF frequency (MHz)
    QDoubleSpinBox* fRFSpinBox;      ///< Spin box for RF frequency (MHz)
    
    // UI Elements - Results Table
    QTableWidget* resultsTable;      ///< Table displaying calculated results
    
    // UI Elements - Buttons
    QPushButton* docsButton;         ///< Button to access documentation
    
    // Result values
    double f_LO1;    ///< Calculated 1st LO frequency (MHz)
    double f_LO2;    ///< Calculated 2nd LO frequency (MHz)
    double f_IM1;    ///< Calculated 1st image frequency (MHz)
    double f_IM2;    ///< Calculated 2nd image frequency (MHz)
};

#endif // SECONDARYIMAGECALCULATORDIALOG_H
