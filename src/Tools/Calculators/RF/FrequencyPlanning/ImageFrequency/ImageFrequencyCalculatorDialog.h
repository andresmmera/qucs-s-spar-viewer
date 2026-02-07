/// @file ImageFrequencyCalculatorDialog.h
/// @brief Image frequency calculator (definition)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 31, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#ifndef IMAGEFREQUENCYCALCULATORDIALOG_H
#define IMAGEFREQUENCYCALCULATORDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QLabel>
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QTableWidget>
#include "Misc/general.h"

/// @class ImageFrequencyCalculatorDialog
/// @brief A dialog for calculating the image frequency in superheterodyne receivers
///  This calculator determines the image frequency based on the RF frequency, IF frequency,
///  and local oscillator (LO) frequency. It supports both low-side and high-side injection modes.
///
/// @details The image frequency is calculated as:
///  - Low-side injection: f_IM = f_RF - 2*f_IF
///  - High-side injection: f_IM = f_RF + 2*f_IF
class ImageFrequencyCalculatorDialog : public QDialog
{
    Q_OBJECT

public:
    /// @brief Constructor
    /// @param parent Parent widget
    explicit ImageFrequencyCalculatorDialog(QWidget *parent = nullptr);

    /// @brief Destructor
    ~ImageFrequencyCalculatorDialog() {}

private slots:
    /// @brief Recalculates the LO frequency when RF, IF, or mode changes
    /// @details Maintains consistency by computing:
    /// - Low-side: f_LO = f_RF - f_IF
    /// - High-side: f_LO = f_RF + f_IF
    void recalculateLO();

    /// @brief Recalculates the RF frequency when LO changes
    /// @details Maintains consistency by computing:
    /// - Low-side: f_RF = f_LO + f_IF
    /// - High-side: f_RF = f_LO - f_IF
    void recalculateRF();

    /// @brief Handles injection mode changes
    /// @param index The new mode index (0 = low-side, 1 = high-side)
    void onModeChanged(int index);

private:
    /// @brief Sets up the user interface
    void setupUI();

    /// @brief Calculates the image frequency and updates the display
    void calculate();

    /// @brief Shows the documentation for the image frequency calculation
    void showDocumentation() {
        QString path = QString("/Calculators/ImageFrequency/index.html");
        showHTMLDocs(path);
    }

    /// @brief Sets frequency input with automatic unit selection
    /// @param spinBox Pointer to the spin box to update
    /// @param comboBox Pointer to the unit combo box to update
    /// @param val Frequency value in Hz
    void setFreqInputWithUnits(QDoubleSpinBox* spinBox, QComboBox* comboBox, double val);

    /// @brief Gets frequency value in Hz from spin box and unit combo box
    /// @param spinBox Pointer to the spin box containing the value
    /// @param comboBox Pointer to the unit combo box
    /// @return Frequency in Hz
    double getFrequencyInHz(QDoubleSpinBox* spinBox, QComboBox* comboBox);

    /// @brief Formats frequency value with appropriate units
    /// @param freqHz Frequency value in Hz
    /// @return Formatted string with value and unit (e.g., "1.50 GHz")
    QString formatFrequency(double freqHz);

    // UI Elements
    QComboBox* modeComboBox;         ///< Combo box for selecting injection mode

    QDoubleSpinBox* fRFSpinBox;      ///< Spin box for RF frequency value
    QComboBox* fRFScaleComboBox;     ///< Combo box for RF frequency unit

    QDoubleSpinBox* fIFSpinBox;      ///< Spin box for IF frequency value
    QComboBox* fIFScaleComboBox;     ///< Combo box for IF frequency unit

    QDoubleSpinBox* fLOSpinBox;      ///< Spin box for LO frequency value
    QComboBox* fLOScaleComboBox;     ///< Combo box for LO frequency unit

    QLabel* fIMResultLabel;          ///< Label displaying the calculated image frequency

    QPushButton* docsButton;         ///< Button to access documentation
    
    // Constants

    /// @enum InjectionMode
    /// @brief Local oscillator injection modes
    enum InjectionMode {
        LowSide = 0,
        HighSide = 1
    };
    
    /// @enum FrequencyScale
    /// @brief Frequency unit scales
    enum FrequencyScale {
        Hz = 0,
        kHz = 1,
        MHz = 2,
        GHz = 3
    };
};

#endif // IMAGEFREQUENCYCALCULATORDIALOG_H
