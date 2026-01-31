/// @file RF_power_converter.h
/// @brief Calculator: Convert RF power between different units (definition)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 28, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#ifndef RF_POWER_CONVERTER_H
#define RF_POWER_CONVERTER_H

#include <QDialog>
#include "UI/CustomWidgets/CustomDoubleSpinBox.h"

class CustomDoubleSpinBox;
class QLabel;
class QPushButton;
class QComboBox;
class QGroupBox;

/// @class RFPowerConverterDialog
/// @brief Dialog for converting RF power between different units
///
/// @details Supported units:
/// - W (Watts)
/// - mW (Milliwatts)
/// - dBm (Decibels relative to 1 milliwatt)
/// - dBμV (Decibels relative to 1 microvolt) on a 50 Ω or 75 Ω load
/// - dBmV (Decibels relative to 1 millivolt) on a 50 Ω or 75 Ω load
/// - V (Volts) for 50 Ω and 75 Ω
class RFPowerConverterDialog : public QDialog {
    Q_OBJECT
public:
    /// @brief Calculator constructor
    /// @param parent Pointer to parent widget
    explicit RFPowerConverterDialog(QWidget *parent = nullptr);

private slots:
    /// @brief Compute the conversion from input to output units
    void computeConversion();

    /// @brief Slot triggered when any input value changes
    void on_inputChanged();

private:
    // ========== Input Widgets ==========

    /// @brief Spin box for power value
    CustomDoubleSpinBox *spinPower;

    /// @brief Combo box for input units selection
    QComboBox *comboOldUnits;

    /// @brief Combo box for output units selection
    QComboBox *comboNewUnits;

    /// @brief Label to display the result
    QLabel *labelResult;

    /// @brief Convert power from input units to Watts
    /// @param power Power value in input units
    /// @param units Unit type string
    /// @return Power in Watts
    double convertToWatts(double power, const QString &units) const;

    /// @brief Convert power from Watts to output units
    /// @param powerW Power value in Watts
    /// @param units Unit type string
    /// @return Power in output units
    double convertFromWatts(double powerW, const QString &units) const;

    /// @brief Format the result with appropriate scaling
    /// @param value The calculated value
    /// @param units The unit string
    /// @return Formatted result string
    QString formatResult(double value, const QString &units) const;
};

#endif // RF_POWER_CONVERTER_H
