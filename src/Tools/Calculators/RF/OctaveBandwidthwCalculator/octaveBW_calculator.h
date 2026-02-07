/// @file octaveBW_calculator.cpp
/// @brief Calculator: Calculate the number of octaves and decades in a band given the corner frequencies (definition)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 28, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#ifndef OCTAVEBW_CALCULATOR_H
#define OCTAVEBW_CALCULATOR_H

#include <QDialog>
#include "UI/CustomWidgets/CustomDoubleSpinBox.h"
#include "Misc/general.h"

class CustomDoubleSpinBox;
class QLabel;
class QPushButton;
class QTableWidget;
class QGroupBox;

/// @class OctaveBWCalculatorDialog
/// @brief Dialog for calculating the number of octaves, decades, and Q from the band corner frequencies
///
/// @details Formula:
/// - Noctaves = log2(fhigh / flow)
/// - Ndecades = log10(fhigh / flow)
/// - Q = fc / BW, where fc = sqrt(flow * fhigh) and BW = fhigh - flow
class OctaveBWCalculatorDialog : public QDialog {
    Q_OBJECT
public:
    /// @brief Calculator constructor
    /// @param parent Pointer to parent widget
    explicit OctaveBWCalculatorDialog(QWidget *parent = nullptr);

private slots:
    /// @brief Compute the output parameters from the input data
    void computeResults();

    /// @brief Slot triggered when any input value changes
    void on_inputChanged();

    /// @brief Slot to show the HTML octave/decades help
    void showDocumentation() {
        QString path = QString("/Calculators/OctaveBW/index.html");
        showHTMLDocs(path);
    }


private:
    // ========== Input Widgets ==========

    /// @brief Spin box for lower corner frequency f_low
    CustomDoubleSpinBox *spinFLow;

    /// @brief Spin box for upper corner frequency f_high
    CustomDoubleSpinBox *spinFHigh;

    // Output
    /// @brief Table widget displaying calculated results
    /// @details Output rows:
    /// - Row 0: f_c - Center frequency (arithmetic mean)
    /// - Row 1: f_c - Center frequency (geometric mean)
    /// - Row 2: BW - Bandwidth (f_high - f_low)
    /// - Row 3: N_octaves - Number of octaves
    /// - Row 4: N_decades - Number of decades
    /// - Row 5: Q - Quality factor
    QTableWidget *resultsTable;

    /// @brief Calculate center frequency (geometric mean)
    /// @return Center frequency f_c = sqrt(f_low * f_high)
    double calculateCenterFrequency() const;

    /// @brief Calculate bandwidth
    /// @return Bandwidth BW = f_high - f_low
    double calculateBandwidth() const;
};

#endif // OCTAVEBW_CALCULATOR_H
