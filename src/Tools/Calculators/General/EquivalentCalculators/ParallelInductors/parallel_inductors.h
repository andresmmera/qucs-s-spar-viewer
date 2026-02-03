/// @file parallel_inductors.h
/// @brief Calculator: Equivalent inductance of parallel inductors (definition)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 29, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#ifndef PARALLEL_INDUCTORS_H
#define PARALLEL_INDUCTORS_H

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

/// @class ParallelInductorsDialog
/// @brief Dialog for calculating equivalent inductance of parallel inductors
///
/// @details Calculates:
/// - Equivalent inductance: 1/Leq = 1/L1 + 1/L2 + ... + 1/Ln
class ParallelInductorsDialog : public QDialog {
    Q_OBJECT
public:
    /// @brief Calculator constructor
    /// @param parent Pointer to parent widget
    explicit ParallelInductorsDialog(QWidget *parent = nullptr);

private slots:
    /// @brief Compute parallel inductance
    void computeResults();

    /// @brief Add an inductor to the list
    void addInductor();

    /// @brief Remove an inductor from the list
    void removeInductor();

    /// @brief Slot triggered when any input value changes
    void on_inputChanged();

    /// @brief Slot to show the HTML parallel inductors help
    void showDocumentation() {
        QString path = QString("/Calculators/ParallelSeriesEquivalents/ParallelResistors/index.html");
        showHTMLDocs(path);
    }

private:
    // ========== Input Widgets ==========

    /// @brief Table for inductor values
    QTableWidget *tableInductors;

    // ========== Output Display ==========

    /// @brief Label displaying equivalent inductance
    QLabel *labelLeq;

    // ========== Helper Functions ==========

    /// @brief Parse inductance value with unit prefix (e.g., "1u", "4.7m")
    /// @param valueStr String containing value and optional unit
    /// @return Inductance in henries
    double parseInductance(const QString &valueStr) const;

    /// @brief Format inductance with appropriate unit prefix
    /// @param value Inductance in henries
    /// @return Formatted string
    QString formatInductance(double value) const;

    /// @brief Get all inductor values from table
    /// @return Vector of inductance values in henries
    QVector<double> getInductors() const;

    /// @brief Calculate equivalent parallel inductance
    /// @param inductors Vector of inductor values
    /// @return Equivalent inductance
    double calculateParallelInductance(const QVector<double> &inductors) const;
};

#endif // PARALLEL_INDUCTORS_H
