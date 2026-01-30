/// @file series_capacitors.h
/// @brief Calculator: Equivalent capacitance of series capacitors (definition)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 29, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#ifndef SERIES_CAPACITORS_H
#define SERIES_CAPACITORS_H

#include <QDialog>
#include <QVector>
#include "./../../../../../UI/CustomWidgets/CustomDoubleSpinBox.h"

class CustomDoubleSpinBox;
class QLabel;
class QPushButton;
class QGroupBox;
class QTableWidget;
class QLineEdit;

/// @class SeriesCapacitorsDialog
/// @brief Dialog for calculating equivalent capacitance of series capacitors
///
/// @details Calculates:
/// - Equivalent capacitance: 1/Ceq = 1/C1 + 1/C2 + ... + 1/Cn
class SeriesCapacitorsDialog : public QDialog {
    Q_OBJECT
public:
    /// @brief Calculator constructor
    /// @param parent Pointer to parent widget
    explicit SeriesCapacitorsDialog(QWidget *parent = nullptr);

private slots:
    /// @brief Compute series capacitance
    void computeResults();

    /// @brief Add a capacitor to the list
    void addCapacitor();

    /// @brief Remove a capacitor from the list
    void removeCapacitor();

    /// @brief Slot triggered when any input value changes
    void on_inputChanged();

private:
    // ========== Input Widgets ==========

    /// @brief Table for capacitor values
    QTableWidget *tableCapacitors;

    // ========== Output Display ==========

    /// @brief Label displaying equivalent capacitance
    QLabel *labelCeq;

    // ========== Helper Functions ==========

    /// @brief Parse capacitance value with unit prefix (e.g., "1p", "4.7n")
    /// @param valueStr String containing value and optional unit
    /// @return Capacitance in farads
    double parseCapacitance(const QString &valueStr) const;

    /// @brief Format capacitance with appropriate unit prefix
    /// @param value Capacitance in farads
    /// @return Formatted string
    QString formatCapacitance(double value) const;

    /// @brief Get all capacitor values from table
    /// @return Vector of capacitance values in farads
    QVector<double> getCapacitors() const;

    /// @brief Calculate equivalent series capacitance
    /// @param capacitors Vector of capacitor values
    /// @return Equivalent capacitance
    double calculateSeriesCapacitance(const QVector<double> &capacitors) const;
};

#endif // SERIES_CAPACITORS_H
