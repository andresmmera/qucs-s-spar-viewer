/// @file free_space_attenuation.h
/// @brief Calculator: Calculate free space path loss (definition)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 29, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#ifndef FREE_SPACE_ATTENUATION_H
#define FREE_SPACE_ATTENUATION_H

#include <QDialog>
#include "./UI/CustomWidgets/CustomDoubleSpinBox.h"

class CustomDoubleSpinBox;
class QLabel;
class QPushButton;
class QComboBox;
class QGroupBox;
class QTableWidget;

/// @class FreeSpaceAttenuationDialog
/// @brief Dialog for calculating free space path loss
///
/// @details Formulas:
/// - FSPL (dB) = 20×log₁₀(d) + 20×log₁₀(f) + 20×log₁₀(4π/c) - G_TX - G_RX
/// - Or simplified: FSPL (dB) = 32.45 + 20×log₁₀(f_MHz) + 20×log₁₀(d_km) - G_TX - G_RX
/// where:
///   - d = distance
///   - f = frequency
///   - c = speed of light (299,792,458 m/s)
///   - G_TX = transmitter antenna gain (dB)
///   - G_RX = receiver antenna gain (dB)
class FreeSpaceAttenuationDialog : public QDialog {
    Q_OBJECT
public:
    /// @brief Calculator constructor
    /// @param parent Pointer to parent widget
    explicit FreeSpaceAttenuationDialog(QWidget *parent = nullptr);

private slots:
    /// @brief Compute the free space path loss
    void computePathLoss();

    /// @brief Slot triggered when any input value changes
    void on_inputChanged();

private:
    // ========== Input Widgets ==========

    /// @brief Spin box for frequency value
    CustomDoubleSpinBox *spinFrequency;

    /// @brief Combo box for frequency units
    QComboBox *comboFreqUnits;

    /// @brief Spin box for distance value
    CustomDoubleSpinBox *spinDistance;

    /// @brief Combo box for distance units
    QComboBox *comboDistanceUnits;

    /// @brief Spin box for TX antenna gain (dB)
    CustomDoubleSpinBox *spinGainTX;

    /// @brief Spin box for RX antenna gain (dB)
    CustomDoubleSpinBox *spinGainRX;

    // Distance labels
    QLabel *label_d_4; ///< Distance/4
    QLabel *label_d_2; ///< Distance/2
    QLabel *label_d;   ///< Distance
    QLabel *label_dx2; ///< Distance x 2
    QLabel *label_dx4; ///< Distance x 4

    // ========== Output Display ==========

    /// @brief Table widget displaying calculated results at various distances
    QTableWidget *resultsTable;

    // ========== Helper Functions ==========

    /// @brief Convert frequency to Hz
    /// @param freq Frequency value
    /// @param units Unit string
    /// @return Frequency in Hz
    double convertFrequencyToHz(double freq, const QString &units) const;

    /// @brief Convert distance to meters
    /// @param distance Distance value
    /// @param units Unit string
    /// @return Distance in meters
    double convertDistanceToMeters(double distance, const QString &units) const;

    /// @brief Calculate free space path loss
    /// @param freqHz Frequency in Hz
    /// @param distanceM Distance in meters
    /// @param gainTX TX antenna gain in dB
    /// @param gainRX RX antenna gain in dB
    /// @return Path loss in dB
    double calculateFSPL(double freqHz, double distanceM, double gainTX, double gainRX) const;

    /// @brief Format distance with appropriate unit
    /// @param distanceM Distance in meters
    /// @return Formatted string
    QString formatDistance(double distanceM) const;
};

#endif // FREE_SPACE_ATTENUATION_H
