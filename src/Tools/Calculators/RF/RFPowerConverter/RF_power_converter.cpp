/// @file RF_power_converter.cpp
/// @brief Calculator: Convert RF power between different units (implementation)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 28, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "RF_power_converter.h"

#include <QComboBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <cmath>

static double applySIPrefix(double value, QString &prefix) {
    prefix = "";
    if (value <= 0.0) return value;
    if (value >= 1e-3)      { prefix = "m"; return value * 1e3;  }
    else if (value >= 1e-6) { prefix = "μ"; return value * 1e6;  }
    else if (value >= 1e-9) { prefix = "n"; return value * 1e9;  }
    else                    { prefix = "p"; return value * 1e12; }
}

RFPowerConverterDialog::RFPowerConverterDialog(QWidget *parent)
    : QDialog(parent) {
  setWindowTitle(tr("RF Power Converter"));

  // Initialize input spinbox for power
  spinPower = new CustomDoubleSpinBox(this);
  spinPower->setRange(-200.0, 200.0); // Wide range for dB units
  spinPower->setDecimals(2);
  spinPower->setSingleStep(1.0);
  spinPower->setValue(0.0); // Default: 0 dBm

  // Initialize combo box for input units
  comboOldUnits = new QComboBox(this);
  comboOldUnits->addItem("W", "W");
  comboOldUnits->addItem("mW", "mW");
  comboOldUnits->addItem("dBm", "dBm");
  comboOldUnits->addItem(QString("dBμV (Z₀ = 75 Ω)"), "dBuV_75");
  comboOldUnits->addItem(QString("dBmV (Z₀ = 75 Ω)"), "dBmV_75");
  comboOldUnits->addItem(QString("dBμV (Z₀ = 50 Ω)"), "dBuV_50");
  comboOldUnits->addItem(QString("dBmV (Z₀ = 50 Ω)"), "dBmV_50");
  comboOldUnits->addItem(QString("V"), "V");
  comboOldUnits->setCurrentIndex(2); // Default: dBm

  // Initialize the input reference impedance spinbox
  spinZ0old = new CustomDoubleSpinBox(this);
  spinZ0old->setRange(0.1, 1e6);
  spinZ0old->setDecimals(2);
  spinZ0old->setSingleStep(1.0);
  spinZ0old->setValue(50.0);
  spinZ0old->setSuffix(" Ω");
  spinZ0old->setVisible(false);

  // Initialize combo box for output units
  comboNewUnits = new QComboBox(this);
  comboNewUnits->addItem("W", "W");
  comboNewUnits->addItem("mW", "mW");
  comboNewUnits->addItem("dBm", "dBm");
  comboNewUnits->addItem(QString("dBμV (Z₀ = 75 Ω)"), "dBuV_75");
  comboNewUnits->addItem(QString("dBmV (Z₀ = 75 Ω)"), "dBmV_75");
  comboNewUnits->addItem(QString("dBμV (Z₀ = 50 Ω)"), "dBuV_50");
  comboNewUnits->addItem(QString("dBmV (Z₀ = 50 Ω)"), "dBmV_50");
  comboNewUnits->addItem(QString("V"), "V");
  comboNewUnits->setCurrentIndex(3); // Default: dBμV (75Ω)

  // Initialize the output reference impedance spinbox
  spinZ0new = new CustomDoubleSpinBox(this);
  spinZ0new->setRange(0.1, 1e6);
  spinZ0new->setDecimals(2);
  spinZ0new->setSingleStep(1.0);
  spinZ0new->setValue(50.0);
  spinZ0new->setSuffix(" Ω");
  spinZ0new->setVisible(false);

  // Create input group box
  QGroupBox *inputGroup = new QGroupBox(QString("Input Parameters"), this);
  inputGroup->setStyleSheet("QGroupBox { font-weight: bold; }");

  auto *labelPower    = new QLabel("<b>Power:</b>",    this);
  auto *labelUnits    = new QLabel("<b>Units:</b>",    this);
  labelZ0old     = new QLabel("<b>Z₀ (in):</b>", this);
  auto *labelNewUnits = new QLabel("<b>New Units:</b>",this);
  labelZ0new    = new QLabel("<b>Z₀ (out):</b>",this);

  auto *rowPower    = new QHBoxLayout;
  rowPower->addWidget(labelPower);
  rowPower->addWidget(spinPower);

  auto *rowUnits    = new QHBoxLayout;
  rowUnits->addWidget(labelUnits);
  rowUnits->addWidget(comboOldUnits);

  auto *rowZ0in     = new QHBoxLayout;
  labelZ0old->setVisible(false);
  rowZ0in->addWidget(labelZ0old);
  rowZ0in->addWidget(spinZ0old);

  auto *rowNewUnits = new QHBoxLayout;
  rowNewUnits->addWidget(labelNewUnits);
  rowNewUnits->addWidget(comboNewUnits);

  auto *rowZ0out    = new QHBoxLayout;
  labelZ0new->setVisible(false);
  rowZ0out->addWidget(labelZ0new);
  rowZ0out->addWidget(spinZ0new);

  auto *inputLayout = new QVBoxLayout;
  inputLayout->addLayout(rowPower);
  inputLayout->addLayout(rowUnits);
  inputLayout->addLayout(rowZ0in);
  inputLayout->addLayout(rowNewUnits);
  inputLayout->addLayout(rowZ0out);
  inputLayout->setSpacing(12);
  inputGroup->setLayout(inputLayout);

  // Create result display
  QGroupBox *resultGroup = new QGroupBox(QString("Result"), this);
  resultGroup->setStyleSheet("QGroupBox { font-weight: bold; }");

  labelResult = new QLabel("-", this);
  labelResult->setAlignment(Qt::AlignCenter);

  // ========== Documentation Button ==========
  QPushButton *btnDocs = new QPushButton("See Docs", this);
  connect(btnDocs, &QPushButton::clicked, this,
          &RFPowerConverterDialog::showDocumentation);

  QVBoxLayout *resultLayout = new QVBoxLayout;
  resultLayout->addWidget(labelResult);
  resultGroup->setLayout(resultLayout);

  // Main layout
  QVBoxLayout *main = new QVBoxLayout;
  main->addWidget(inputGroup);
  main->addSpacing(10);
  main->addWidget(resultGroup);
  main->setSpacing(8);
  main->setContentsMargins(15, 15, 15, 15);
  main->addSpacing(10);
  main->addWidget(btnDocs);

  setLayout(main);
  setMinimumWidth(450);
  setMinimumHeight(350);

  // Connect signals for live updates
  connect(spinPower, SIGNAL(valueChanged(double)), this,
          SLOT(computeConversion()));
  connect(spinPower, SIGNAL(editingFinished()), this,
          SLOT(computeConversion()));
  connect(comboOldUnits, SIGNAL(currentIndexChanged(int)), this,
          SLOT(onInputUnitChanged()));
  connect(comboNewUnits, SIGNAL(currentIndexChanged(int)), this,
          SLOT(onOutputUnitChanged()));
  connect(spinZ0old,   SIGNAL(valueChanged(double)), this, SLOT(computeConversion()));
  connect(spinZ0new,  SIGNAL(valueChanged(double)), this, SLOT(computeConversion()));

  // Compute initial values
  computeConversion();
}

double RFPowerConverterDialog::convertToWatts(double power,
                                              const QString &units, double Z0) const {
  double powerW = 0.0;

  if (units == "W") {
    powerW = power;
  } else if (units == "mW") {
    powerW = 1e-3 * power;
  } else if (units == "dBm") {
    powerW = std::pow(10.0, 0.1 * (power - 30.0));
  } else if (units == "dBuV_75") {
    powerW = std::pow(10.0, 0.1 * (power - 138.75));
  } else if (units == "dBmV_75") {
    powerW = std::pow(10.0, 0.1 * (power - 78.75));
  } else if (units == "V") {
    powerW = power * power / Z0;
  } else if (units == "dBuV_50") {
    powerW = std::pow(10.0, 0.1 * (power - 136.99));
  } else if (units == "dBmV_50") {
    powerW = std::pow(10.0, 0.1 * (power - 76.99));
  } else {
    powerW = power;
  }

  return powerW;
}

double RFPowerConverterDialog::convertFromWatts(double powerW,
                                                const QString &units, double Z0) const {
  double result = 0.0;

  if (units == "W") {
    result = powerW;
  } else if (units == "mW") {
    result = 1e3 * powerW;
  } else if (units == "dBm") {
    result = 10.0 * std::log10(powerW) + 30.0;
  } else if (units == "dBuV_75") {
    result = 10.0 * std::log10(powerW) + 138.75;
  } else if (units == "dBmV_75") {
    result = 10.0 * std::log10(powerW) + 78.75;
  } else if (units == "V") {
    result = std::sqrt(powerW * Z0);
  } else if (units == "dBuV_50") {
    result = 10.0 * std::log10(powerW) + 136.99;
  } else if (units == "dBmV_50") {
    result = 10.0 * std::log10(powerW) + 76.99;
  } else {
    result = powerW;
  }

  return result;
}

QString RFPowerConverterDialog::formatResult(double value, double powerW,
                                             const QString &units, double Z0) const {
    // ── Voltage output: show both RMS and peak ────────────────────────────
    if (units == "V") {
        const QString Z0label = QString("%1").arg(Z0);
        const double Vrms     = std::sqrt(powerW * Z0);
        const double Vpeak    = Vrms * std::sqrt(2.0);

        QString rmsPrefix;
        double rmsScaled  = (Vrms < 0.5 && Vrms > 0)
                               ? applySIPrefix(Vrms, rmsPrefix)
                               : (rmsPrefix = "", Vrms);
        double peakScaled = rmsPrefix.isEmpty() ? Vpeak : Vpeak * (rmsScaled / Vrms);

        return QString("%1 %2Vrms\n%3 %4Vpeak")
            .arg(QString::number(rmsScaled,  'f', 2), rmsPrefix, QString::number(peakScaled, 'f', 2), rmsPrefix);
    }

    // ── All other units ───────────────────────────────────────────────────
    QString scale = "";
    double scaledValue = value;

    if (units == "W" && value < 0.5 && value > 0) {
        scaledValue = applySIPrefix(value, scale);
    }

    QString unitText;
    int index = comboNewUnits->currentIndex();
    if (index >= 0) {
        unitText = comboNewUnits->itemText(index);
    }

    QString formattedValue = QString::number(scaledValue, 'f', 2);

    if (!scale.isEmpty() && units == "W") {
        return formattedValue + " " + scale + "W";
    }

    return formattedValue + " " + unitText;
}

void RFPowerConverterDialog::computeConversion() {
  double power = spinPower->value();
  QString oldUnits = comboOldUnits->currentData().toString();
  QString newUnits = comboNewUnits->currentData().toString();
  double Zold = spinZ0old->value();  ///< Impedance at which the old units are referred (if applicable)
  double Znew = spinZ0new->value();  ///< Impedance at which the new units are referred (if applicable)

  // Validate input for linear units (must be positive)
  if (power <= 0.0 && !oldUnits.contains("dB")) {
    labelResult->setText("Error: Power must be positive");
    labelResult->setStyleSheet("QLabel { "
                               "  font-size: 18px; "
                               "  font-weight: bold; "
                               "  padding: 20px; "
                               "  border: 2px solid #c0c0c0; "
                               "  border-radius: 4px; "
                               "  background-color: white; "
                               "  min-height: 50px; "
                               "  color: #b40000; "
                               "}");
    return;
  }

  // Reset style to normal
  labelResult->setStyleSheet("QLabel { "
                             "  font-size: 18px; "
                             "  font-weight: bold; "
                             "  padding: 20px; "
                             "  border: 2px solid #c0c0c0; "
                             "  border-radius: 4px; "
                             "  background-color: white; "
                             "  min-height: 50px; "
                             "}");

  // Convert to Watts first
  double powerW = convertToWatts(power, oldUnits, Zold);

  // Convert from Watts to new units
  double result = convertFromWatts(powerW, newUnits, Znew);

  // Format and display result
  QString resultText = formatResult(result, powerW, newUnits, Znew);
  labelResult->setText(resultText);
}

void RFPowerConverterDialog::onInputUnitChanged() {
    bool isVoltage = (comboOldUnits->currentText().toStdString() == "V");
    spinZ0old->setVisible(isVoltage);
    labelZ0old->setVisible(isVoltage);
    computeConversion();
}

void RFPowerConverterDialog::onOutputUnitChanged() {
    bool isVoltage = (comboNewUnits->currentText().toStdString() == "V");
    spinZ0new->setVisible(isVoltage);
    labelZ0new->setVisible(isVoltage);
    computeConversion();
}
