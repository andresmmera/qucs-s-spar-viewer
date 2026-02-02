/// @file freq_wavelength_converter.cpp
/// @brief Calculator: Convert between frequency and wavelength (implementation)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 29, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "freq_wavelength_converter.h"

#include <QButtonGroup>
#include <QComboBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QRadioButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <cmath>

// Speed of light in vacuum (m/s)
constexpr double SPEED_OF_LIGHT = 299792458.0;

FreqWavelengthConverterDialog::FreqWavelengthConverterDialog(QWidget *parent)
    : QDialog(parent) {
  setWindowTitle(tr("Frequency ↔ Wavelength Converter"));

  // ========== Mode Selection ==========
  QGroupBox *modeGroup = new QGroupBox(QString("Conversion Mode"), this);
  modeGroup->setStyleSheet("QGroupBox { font-weight: bold; }");

  radioFreqToWavelength = new QRadioButton(tr("Frequency → Wavelength"), this);
  radioWavelengthToFreq = new QRadioButton(tr("Wavelength → Frequency"), this);
  radioFreqToWavelength->setChecked(true);

  QButtonGroup *modeButtonGroup = new QButtonGroup(this);
  modeButtonGroup->addButton(radioFreqToWavelength);
  modeButtonGroup->addButton(radioWavelengthToFreq);

  QVBoxLayout *modeLayout = new QVBoxLayout;
  modeLayout->addWidget(radioFreqToWavelength);
  modeLayout->addWidget(radioWavelengthToFreq);
  modeGroup->setLayout(modeLayout);

  // ========== Frequency Input Group ==========
  freqInputGroup = new QGroupBox(QString("Frequency Input"), this);
  freqInputGroup->setStyleSheet("QGroupBox { font-weight: bold; }");

  spinFrequency = new CustomDoubleSpinBox(this);
  spinFrequency->setRange(0.0, 1e15);
  spinFrequency->setDecimals(0);
  spinFrequency->setSingleStep(1.0);
  spinFrequency->setValue(1000);

  comboFreqUnits = new QComboBox(this);
  comboFreqUnits->addItem("Hz", "Hz");
  comboFreqUnits->addItem("kHz", "kHz");
  comboFreqUnits->addItem("MHz", "MHz");
  comboFreqUnits->addItem("GHz", "GHz");
  comboFreqUnits->addItem("THz", "THz");
  comboFreqUnits->setCurrentIndex(2); // Default: MHz

  QFormLayout *freqInputLayout = new QFormLayout;
  freqInputLayout->addRow(QString("<b>Frequency:</b>"), spinFrequency);
  freqInputLayout->addRow(QString("<b>Units:</b>"), comboFreqUnits);
  freqInputLayout->setLabelAlignment(Qt::AlignRight);
  freqInputLayout->setSpacing(12);
  freqInputGroup->setLayout(freqInputLayout);

  // ========== Wavelength Input Group ==========
  wavelengthInputGroup = new QGroupBox(QString("Wavelength Input"), this);
  wavelengthInputGroup->setStyleSheet("QGroupBox { font-weight: bold; }");

  spinWavelength = new CustomDoubleSpinBox(this);
  spinWavelength->setRange(0.0, 1e15);
  spinWavelength->setDecimals(1);
  spinWavelength->setSingleStep(1.0);
  spinWavelength->setValue(30);

  comboWavelengthUnits = new QComboBox(this);
  comboWavelengthUnits->addItem("m", "m");
  comboWavelengthUnits->addItem("cm", "cm");
  comboWavelengthUnits->addItem("mm", "mm");
  comboWavelengthUnits->addItem("μm", "um");
  comboWavelengthUnits->addItem("nm", "nm");
  comboWavelengthUnits->addItem("inch", "inch");
  comboWavelengthUnits->addItem("mil", "mil");
  comboWavelengthUnits->setCurrentIndex(1); // Default: cm

  QFormLayout *wavelengthInputLayout = new QFormLayout;
  wavelengthInputLayout->addRow(QString("<b>Wavelength:</b>"), spinWavelength);
  wavelengthInputLayout->addRow(QString("<b>Units:</b>"), comboWavelengthUnits);
  wavelengthInputLayout->setLabelAlignment(Qt::AlignRight);
  wavelengthInputLayout->setSpacing(12);
  wavelengthInputGroup->setLayout(wavelengthInputLayout);

  // Initially hide wavelength input
  wavelengthInputGroup->setVisible(false);

  // ========== Permittivity Input ==========
  QGroupBox *permittivityGroup = new QGroupBox(QString("Medium"), this);
  permittivityGroup->setStyleSheet("QGroupBox { font-weight: bold; }");

  spinPermittivity = new CustomDoubleSpinBox(this);
  spinPermittivity->setRange(1.0, 100.0);
  spinPermittivity->setDecimals(1);
  spinPermittivity->setSingleStep(0.1);
  spinPermittivity->setValue(4.7); // Default: FR4

  QFormLayout *permittivityLayout = new QFormLayout;
  permittivityLayout->addRow(
      QString("<b>ε<sub>r</sub> (Relative Permittivity):</b>"),
      spinPermittivity);
  permittivityLayout->setLabelAlignment(Qt::AlignRight);
  permittivityLayout->setSpacing(12);
  permittivityGroup->setLayout(permittivityLayout);

  // ========== Results Table ==========
  QGroupBox *resultsGroup = new QGroupBox(QString("Results"), this);
  resultsGroup->setStyleSheet("QGroupBox { font-weight: bold; }");

  resultsTable = new QTableWidget(4, 2, this);
  resultsTable->setHorizontalHeaderLabels(QStringList()
                                          << "Parameter" << "Value");
  resultsTable->verticalHeader()->setVisible(false);

  // Set row labels using QLabel widgets for HTML support
  QLabel *label0 = new QLabel("Frequency (f)");
  label0->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  resultsTable->setCellWidget(0, 0, label0);

  QLabel *label1 = new QLabel("λ (Wavelength)");
  label1->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  resultsTable->setCellWidget(1, 0, label1);

  QLabel *label2 = new QLabel("λ/2");
  label2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  resultsTable->setCellWidget(2, 0, label2);

  QLabel *label3 = new QLabel("λ/4");
  label3->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  resultsTable->setCellWidget(3, 0, label3);

  // Initialize value cells
  for (int i = 0; i < 4; ++i) {
    QTableWidgetItem *item = new QTableWidgetItem("-");
    item->setTextAlignment(Qt::AlignCenter);
    item->setFlags(item->flags() & ~Qt::ItemIsEditable);
    resultsTable->setItem(i, 1, item);
  }

  // Table settings
  resultsTable->setAlternatingRowColors(true);
  resultsTable->horizontalHeader()->setSectionResizeMode(0,
                                                         QHeaderView::Stretch);
  resultsTable->horizontalHeader()->setSectionResizeMode(1,
                                                         QHeaderView::Stretch);
  resultsTable->setSelectionMode(QAbstractItemView::SingleSelection);
  resultsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
  resultsTable->setMinimumHeight(150);

  // Table stylesheet
  QString tableStyle =
      "QTableWidget { "
      "  gridline-color: #d0d0d0; "
      "  border: 1px solid #c0c0c0; "
      "  border-radius: 4px; "
      "  background-color: white; "
      "}"
      "QTableWidget::item { "
      "  padding: 8px; "
      "}"
      "QHeaderView::section { "
      "  background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
      "                                     stop:0 #f0f0f0, stop:1 #e0e0e0); "
      "  padding: 6px; "
      "  border: none; "
      "  border-right: 1px solid #c0c0c0; "
      "  border-bottom: 1px solid #c0c0c0; "
      "  font-weight: bold; "
      "}";
  resultsTable->setStyleSheet(tableStyle);

  QVBoxLayout *resultsLayout = new QVBoxLayout;
  resultsLayout->addWidget(resultsTable);
  resultsGroup->setLayout(resultsLayout);

  // ========== Main Layout ==========
  QVBoxLayout *mainLayout = new QVBoxLayout;
  mainLayout->addWidget(modeGroup);
  mainLayout->addSpacing(10);
  mainLayout->addWidget(freqInputGroup);
  mainLayout->addWidget(wavelengthInputGroup);
  mainLayout->addSpacing(10);
  mainLayout->addWidget(permittivityGroup);
  mainLayout->addSpacing(10);
  mainLayout->addWidget(resultsGroup);
  mainLayout->setSpacing(8);
  mainLayout->setContentsMargins(15, 15, 15, 15);

  // Docs button
  QHBoxLayout *buttonLayout = new QHBoxLayout();
  buttonLayout->addStretch();

  docsButton = new QPushButton("See docs");
  connect(docsButton, &QPushButton::clicked, this,
          &FreqWavelengthConverterDialog::showDocumentation);
  buttonLayout->addWidget(docsButton);
  mainLayout->addLayout(buttonLayout);
  mainLayout->addStretch();

  setLayout(mainLayout);
  setMinimumWidth(500);
  setMinimumHeight(600);

  // ========== Connect Signals ==========
  connect(radioFreqToWavelength, SIGNAL(toggled(bool)), this,
          SLOT(on_modeChanged()));
  connect(radioWavelengthToFreq, SIGNAL(toggled(bool)), this,
          SLOT(on_modeChanged()));

  connect(spinFrequency, SIGNAL(valueChanged(double)), this,
          SLOT(computeConversion()));
  connect(spinFrequency, SIGNAL(editingFinished()), this,
          SLOT(computeConversion()));
  connect(comboFreqUnits, SIGNAL(currentIndexChanged(int)), this,
          SLOT(computeConversion()));

  connect(spinWavelength, SIGNAL(valueChanged(double)), this,
          SLOT(computeConversion()));
  connect(spinWavelength, SIGNAL(editingFinished()), this,
          SLOT(computeConversion()));
  connect(comboWavelengthUnits, SIGNAL(currentIndexChanged(int)), this,
          SLOT(computeConversion()));

  connect(spinPermittivity, SIGNAL(valueChanged(double)), this,
          SLOT(computeConversion()));
  connect(spinPermittivity, SIGNAL(editingFinished()), this,
          SLOT(computeConversion()));

  // Compute initial values
  computeConversion();
}

double FreqWavelengthConverterDialog::convertFrequencyToHz(
    double freq, const QString &units) const {
  if (units == "Hz")
    return freq;
  if (units == "kHz")
    return freq * 1e3;
  if (units == "MHz")
    return freq * 1e6;
  if (units == "GHz")
    return freq * 1e9;
  if (units == "THz")
    return freq * 1e12;
  return freq;
}

double FreqWavelengthConverterDialog::convertFrequencyFromHz(
    double freqHz, const QString &units) const {
  if (units == "Hz")
    return freqHz;
  if (units == "kHz")
    return freqHz / 1e3;
  if (units == "MHz")
    return freqHz / 1e6;
  if (units == "GHz")
    return freqHz / 1e9;
  if (units == "THz")
    return freqHz / 1e12;
  return freqHz;
}

double FreqWavelengthConverterDialog::convertWavelengthToMeters(
    double wavelength, const QString &units) const {
  if (units == "m")
    return wavelength;
  if (units == "cm")
    return wavelength * 1e-2;
  if (units == "mm")
    return wavelength * 1e-3;
  if (units == "um")
    return wavelength * 1e-6;
  if (units == "nm")
    return wavelength * 1e-9;
  if (units == "inch")
    return wavelength * 0.0254;
  if (units == "mil")
    return wavelength * 0.0254 / 1000.0;
  return wavelength;
}

double FreqWavelengthConverterDialog::convertWavelengthFromMeters(
    double wavelengthM, const QString &units) const {
  if (units == "m")
    return wavelengthM;
  if (units == "cm")
    return wavelengthM / 1e-2;
  if (units == "mm")
    return wavelengthM / 1e-3;
  if (units == "um")
    return wavelengthM / 1e-6;
  if (units == "nm")
    return wavelengthM / 1e-9;
  if (units == "inch")
    return wavelengthM / 0.0254;
  if (units == "mil")
    return wavelengthM / (0.0254 / 1000.0);
  return wavelengthM;
}

QString FreqWavelengthConverterDialog::formatFrequency(double freqHz) const {
  if (freqHz >= 1e12) {
    return QString::number(freqHz / 1e12, 'g', 6) + " THz";
  } else if (freqHz >= 1e9) {
    return QString::number(freqHz / 1e9, 'g', 6) + " GHz";
  } else if (freqHz >= 1e6) {
    return QString::number(freqHz / 1e6, 'g', 6) + " MHz";
  } else if (freqHz >= 1e3) {
    return QString::number(freqHz / 1e3, 'g', 6) + " kHz";
  } else {
    return QString::number(freqHz, 'g', 6) + " Hz";
  }
}

QString
FreqWavelengthConverterDialog::formatWavelength(double wavelengthM) const {
  if (wavelengthM >= 1.0) {
    return QString::number(wavelengthM, 'g', 6) + " m";
  } else if (wavelengthM >= 1e-2) {
    return QString::number(wavelengthM / 1e-2, 'g', 2) + " cm";
  } else if (wavelengthM >= 1e-3) {
    return QString::number(wavelengthM / 1e-3, 'g', 2) + " mm";
  } else if (wavelengthM >= 1e-6) {
    return QString::number(wavelengthM / 1e-6, 'g', 2) + " μm";
  } else {
    return QString::number(wavelengthM / 1e-9, 'g', 2) + " nm";
  }
}

void FreqWavelengthConverterDialog::on_modeChanged() {
  if (radioFreqToWavelength->isChecked()) {
    freqInputGroup->setVisible(true);
    wavelengthInputGroup->setVisible(false);
  } else {
    freqInputGroup->setVisible(false);
    wavelengthInputGroup->setVisible(true);
  }
  computeConversion();
}

void FreqWavelengthConverterDialog::computeConversion() {
  const double eps = 1e-12;
  double er = spinPermittivity->value();

  if (er < 1.0) {
    er = 1.0;
    spinPermittivity->setValue(1.0);
  }

  double sqrtEr = std::sqrt(er);
  double freqHz = 0.0;
  double wavelengthM = 0.0;

  if (radioFreqToWavelength->isChecked()) {
    // Frequency to Wavelength conversion
    double freq = spinFrequency->value();
    QString freqUnits = comboFreqUnits->currentData().toString();

    if (freq <= eps) {
      // Invalid frequency
      for (int i = 0; i < 4; ++i) {
        resultsTable->item(i, 1)->setText("Error");
        resultsTable->item(i, 1)->setForeground(QBrush(QColor(180, 0, 0)));
      }
      return;
    }

    // Convert to Hz
    freqHz = convertFrequencyToHz(freq, freqUnits);

    // Calculate wavelength: λ = c / (f × √εᵣ)
    wavelengthM = SPEED_OF_LIGHT / (freqHz * sqrtEr);

  } else {
    // Wavelength to Frequency conversion
    double wavelength = spinWavelength->value();
    QString wavelengthUnits = comboWavelengthUnits->currentData().toString();

    if (wavelength <= eps) {
      // Invalid wavelength
      for (int i = 0; i < 4; ++i) {
        resultsTable->item(i, 1)->setText("Error");
        resultsTable->item(i, 1)->setForeground(QBrush(QColor(180, 0, 0)));
      }
      return;
    }

    // Convert to meters
    wavelengthM = convertWavelengthToMeters(wavelength, wavelengthUnits);

    // Calculate frequency: f = c / (λ × √εᵣ)
    freqHz = SPEED_OF_LIGHT / (wavelengthM * sqrtEr);
  }

  // Reset colors to normal
  for (int i = 0; i < 4; ++i) {
    resultsTable->item(i, 1)->setForeground(QBrush(QColor(0, 0, 0)));
  }

  // Display results
  resultsTable->item(0, 1)->setText(formatFrequency(freqHz));
  resultsTable->item(1, 1)->setText(formatWavelength(wavelengthM));
  resultsTable->item(2, 1)->setText(formatWavelength(wavelengthM / 2.0));
  resultsTable->item(3, 1)->setText(formatWavelength(wavelengthM / 4.0));
}

void FreqWavelengthConverterDialog::on_inputChanged() { computeConversion(); }
