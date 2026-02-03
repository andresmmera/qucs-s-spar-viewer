/// @file parallel_resistors.h
/// @brief Calculator: Equivalent resistance of parallel resistors (definition)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 30, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#ifndef PARALLEL_RESISTORS_H
#define PARALLEL_RESISTORS_H

#include <QDialog>
#include <QVector>
#include "UI/CustomWidgets/CustomDoubleSpinBox.h"
#include "Misc/general.h"

class CustomDoubleSpinBox;
class QLabel;
class QPushButton;
class QGroupBox;
class QTableWidget;
class QLineEdit;

/// @class ParallelResistorsDialog
/// @brief Dialog for calculating equivalent resistance of parallel resistors
///
/// @details Calculates:
/// - Equivalent resistance: 1/Req = 1/R1 + 1/R2 + ... + 1/Rn
/// - Current through each resistor: I = ΔV / R
/// - Power dissipation in each resistor: P = I² × R
/// - Highlights resistors exceeding maximum power rating
class ParallelResistorsDialog : public QDialog {
    Q_OBJECT
public:
    /// @brief Calculator constructor
    /// @param parent Pointer to parent widget
    explicit ParallelResistorsDialog(QWidget *parent = nullptr);

private slots:
    /// @brief Compute parallel resistance and power dissipation
    void computeResults();

    /// @brief Add a resistor to the list
    void addResistor();

    /// @brief Remove a resistor from the list
    void removeResistor();

    /// @brief Slot triggered when any input value changes
    void on_inputChanged();

    void showDocumentation() {
        QString path = QString("/Calculators/ParallelSeriesEquivalents/ParallelResistors/index.html");
        showHTMLDocs(path);
    }

private:
    // ========== Input Widgets ==========

    /// @brief Voltage across resistors (ΔV)
    CustomDoubleSpinBox *spinDeltaV;

    /// @brief Maximum power dissipation per resistor
    CustomDoubleSpinBox *spinPmax;

    /// @brief Table for resistor values
    QTableWidget *tableResistors;

    // ========== Output Display ==========

    /// @brief Label displaying equivalent resistance
    QLabel *labelReq;

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

    /// @brief Get all resistor values from table
    /// @return Vector of resistance values in ohms
    QVector<double> getResistors() const;

    /// @brief Calculate equivalent parallel resistance
    /// @param resistors Vector of resistor values
    /// @return Equivalent resistance
    double calculateParallelResistance(const QVector<double> &resistors) const;
};

#endif // PARALLEL_RESISTORS_H
