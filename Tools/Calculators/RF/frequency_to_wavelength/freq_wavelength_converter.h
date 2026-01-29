/// @file freq_wavelength_converter.h
/// @brief Calculator: Convert between frequency and wavelength (definition)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 29, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#ifndef FREQ_WAVELENGTH_CONVERTER_H
#define FREQ_WAVELENGTH_CONVERTER_H

#include <QDialog>
#include "./../../../../UI/CustomWidgets/CustomDoubleSpinBox.h"

class CustomDoubleSpinBox;
class QLabel;
class QPushButton;
class QComboBox;
class QGroupBox;
class QRadioButton;
class QTableWidget;

/// @class FreqWavelengthConverterDialog
/// @brief Dialog for converting between frequency and wavelength
///
/// @details Formulas:
/// - λ = c / (f × √εᵣ)
/// - f = c / (λ × √εᵣ)
/// where c = 299792458 m/s (speed of light in vacuum)
class FreqWavelengthConverterDialog : public QDialog {
    Q_OBJECT
public:
    /// @brief Calculator constructor
    /// @param parent Pointer to parent widget
    explicit FreqWavelengthConverterDialog(QWidget *parent = nullptr);

private slots:
    /// @brief Compute the conversion
    void computeConversion();

    /// @brief Slot triggered when conversion mode changes
    void on_modeChanged();

    /// @brief Slot triggered when any input value changes
    void on_inputChanged();

private:
    // ========== Mode Selection ==========
    
    /// @brief Radio button for frequency to wavelength mode
    QRadioButton *radioFreqToWavelength;

    /// @brief Radio button for wavelength to frequency mode
    QRadioButton *radioWavelengthToFreq;

    // ========== Input Widgets ==========

    /// @brief Spin box for frequency value
    CustomDoubleSpinBox *spinFrequency;

    /// @brief Combo box for frequency units
    QComboBox *comboFreqUnits;

    /// @brief Spin box for wavelength value
    CustomDoubleSpinBox *spinWavelength;

    /// @brief Combo box for wavelength units
    QComboBox *comboWavelengthUnits;

    /// @brief Spin box for relative permittivity (εᵣ)
    CustomDoubleSpinBox *spinPermittivity;

    // ========== Output Display ==========

    /// @brief Table widget displaying calculated results
    QTableWidget *resultsTable;

    /// @brief Group box containing frequency input
    QGroupBox *freqInputGroup;

    /// @brief Group box containing wavelength input
    QGroupBox *wavelengthInputGroup;

    // ========== Helper Functions ==========

    /// @brief Convert frequency to Hz
    /// @param freq Frequency value
    /// @param units Unit string
    /// @return Frequency in Hz
    double convertFrequencyToHz(double freq, const QString &units) const;

    /// @brief Convert frequency from Hz to specified units
    /// @param freqHz Frequency in Hz
    /// @param units Unit string
    /// @return Frequency in specified units
    double convertFrequencyFromHz(double freqHz, const QString &units) const;

    /// @brief Convert wavelength to meters
    /// @param wavelength Wavelength value
    /// @param units Unit string
    /// @return Wavelength in meters
    double convertWavelengthToMeters(double wavelength, const QString &units) const;

    /// @brief Convert wavelength from meters to specified units
    /// @param wavelengthM Wavelength in meters
    /// @param units Unit string
    /// @return Wavelength in specified units
    double convertWavelengthFromMeters(double wavelengthM, const QString &units) const;

    /// @brief Format frequency with appropriate unit
    /// @param freqHz Frequency in Hz
    /// @return Formatted string
    QString formatFrequency(double freqHz) const;

    /// @brief Format wavelength with appropriate unit
    /// @param wavelengthM Wavelength in meters
    /// @return Formatted string
    QString formatWavelength(double wavelengthM) const;
};

#endif // FREQ_WAVELENGTH_CONVERTER_H
