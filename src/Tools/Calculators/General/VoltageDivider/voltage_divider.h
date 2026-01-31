/// @file voltage_divider.h
/// @brief Calculator: Voltage divider design with power dissipation analysis (definition)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 29, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#ifndef VOLTAGE_DIVIDER_H
#define VOLTAGE_DIVIDER_H

#include <QDialog>
#include <QVector>
#include "UI/CustomWidgets/CustomDoubleSpinBox.h"

class CustomDoubleSpinBox;
class QLabel;
class QPushButton;
class QComboBox;
class QGroupBox;
class QTableWidget;
class QLineEdit;

/// @class VoltageDividerDialog
/// @brief Dialog for designing voltage dividers with multiple parallel resistors
///
/// @details Calculates:
/// - Output voltage: Vout = Vdc × Req_lower / (Req_upper + Req_lower)
/// - Current through each resistor
/// - Power dissipation in each resistor
/// - Highlights resistors exceeding maximum power rating
/// @todo Export voltage divider schematic to Qucs-S
class VoltageDividerDialog : public QDialog {
    Q_OBJECT
public:
    /// @brief Calculator constructor
    /// @param parent Pointer to parent widget
    explicit VoltageDividerDialog(QWidget *parent = nullptr);

private slots:
    /// @brief Compute voltage divider results
    void computeResults();

    /// @brief Add a resistor to the upper branch
    void addUpperResistor();

    /// @brief Remove a resistor from the upper branch
    void removeUpperResistor();

    /// @brief Add a resistor to the lower branch
    void addLowerResistor();

    /// @brief Remove a resistor from the lower branch
    void removeLowerResistor();

    /// @brief Slot triggered when any input value changes
    void on_inputChanged();

private:
    // ========== Input Widgets ==========

    /// @brief Input voltage (Vdc)
    CustomDoubleSpinBox *spinVdc;

    /// @brief Maximum power dissipation per resistor
    CustomDoubleSpinBox *spinPmax;

    /// @brief Table for upper branch resistors
    QTableWidget *tableUpper;

    /// @brief Table for lower branch resistors
    QTableWidget *tableLower;

    // ========== Output Display ==========

    /// @brief Label displaying output voltage
    QLabel *labelVout;

    /// @brief Table widget displaying calculated results
    QTableWidget *resultsTable;

    // ========== Helper Functions ==========

    /// @brief Parse resistance value with unit prefix (e.g., "1k", "4.7M")
    /// @param valueStr String containing value and optional unit
    /// @return Resistance in ohms
    double parseResistance(const QString &valueStr) const;

    /// @brief Format resistance with appropriate unit prefix
    /// @param value Resistance in ohms
    /// @return Formatted string
    QString formatResistance(double value) const;

    /// @brief Format current with appropriate unit prefix
    /// @param value Current in amperes
    /// @return Formatted string
    QString formatCurrent(double value) const;

    /// @brief Format power with appropriate unit prefix
    /// @param value Power in watts
    /// @return Formatted string
    QString formatPower(double value) const;

    /// @brief Get all resistor values from upper branch
    /// @return Vector of resistance values in ohms
    QVector<double> getUpperResistors() const;

    /// @brief Get all resistor values from lower branch
    /// @return Vector of resistance values in ohms
    QVector<double> getLowerResistors() const;

    /// @brief Calculate equivalent parallel resistance
    /// @param resistors Vector of resistor values
    /// @return Equivalent resistance
    double calculateParallelResistance(const QVector<double> &resistors) const;

    /// @brief Update the results table with calculations
    void updateResultsTable();
};

#endif // VOLTAGE_DIVIDER_H
