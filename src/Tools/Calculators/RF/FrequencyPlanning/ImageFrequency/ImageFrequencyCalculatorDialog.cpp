/// @file ImageFrequencyCalculatorDialog.cpp
/// @brief Image frequency calculator (implementation)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 31, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "ImageFrequencyCalculatorDialog.h"
#include <QHeaderView>
#include <cmath>

ImageFrequencyCalculatorDialog::ImageFrequencyCalculatorDialog(QWidget *parent)
    : QDialog(parent) {
  setupUI();
  recalculateLO();
}

void ImageFrequencyCalculatorDialog::setupUI() {
  setWindowTitle("Image Frequency Calculator");
  setMinimumWidth(500);

  QVBoxLayout *mainLayout = new QVBoxLayout(this);

  // Title
  QLabel *titleLabel = new QLabel("Image Frequency Calculator");
  QFont titleFont = titleLabel->font();
  titleFont.setPointSize(14);
  titleFont.setBold(true);
  titleLabel->setFont(titleFont);
  mainLayout->addWidget(titleLabel);

  // Input Group
  QGroupBox *inputGroup = new QGroupBox("Input Parameters");
  inputGroup->setStyleSheet("QGroupBox { font-weight: bold; }");
  QGridLayout *inputLayout = new QGridLayout(inputGroup);

  // Mode selection
  inputLayout->addWidget(new QLabel("Injection Mode:"), 0, 0);
  modeComboBox = new QComboBox();
  modeComboBox->addItem("Low-side injection");
  modeComboBox->addItem("High-side injection");
  inputLayout->addWidget(modeComboBox, 0, 1, 1, 2);

  // f_RF input
  inputLayout->addWidget(new QLabel("f<sub>RF</sub>:"), 1, 0);
  fRFSpinBox = new QDoubleSpinBox();
  fRFSpinBox->setDecimals(2);
  fRFSpinBox->setMinimum(0);
  fRFSpinBox->setMaximum(999999);
  fRFSpinBox->setValue(1000);
  fRFSpinBox->setSingleStep(1);
  inputLayout->addWidget(fRFSpinBox, 1, 1);

  fRFScaleComboBox = new QComboBox();
  fRFScaleComboBox->addItem("Hz");
  fRFScaleComboBox->addItem("kHz");
  fRFScaleComboBox->addItem("MHz");
  fRFScaleComboBox->addItem("GHz");
  fRFScaleComboBox->setCurrentIndex(FrequencyScale::MHz);
  inputLayout->addWidget(fRFScaleComboBox, 1, 2);

  // f_IF input
  inputLayout->addWidget(new QLabel("f<sub>IF</sub>:"), 2, 0);
  fIFSpinBox = new QDoubleSpinBox();
  fIFSpinBox->setDecimals(2);
  fIFSpinBox->setMinimum(0);
  fIFSpinBox->setMaximum(999999);
  fIFSpinBox->setValue(200);
  fIFSpinBox->setSingleStep(1);
  inputLayout->addWidget(fIFSpinBox, 2, 1);

  fIFScaleComboBox = new QComboBox();
  fIFScaleComboBox->addItem("Hz");
  fIFScaleComboBox->addItem("kHz");
  fIFScaleComboBox->addItem("MHz");
  fIFScaleComboBox->addItem("GHz");
  fIFScaleComboBox->setCurrentIndex(FrequencyScale::MHz);
  inputLayout->addWidget(fIFScaleComboBox, 2, 2);

  // f_LO input
  inputLayout->addWidget(new QLabel("f<sub>LO</sub>:"), 3, 0);
  fLOSpinBox = new QDoubleSpinBox();
  fLOSpinBox->setDecimals(2);
  fLOSpinBox->setMinimum(0);
  fLOSpinBox->setMaximum(999999);
  fLOSpinBox->setValue(200);
  fLOSpinBox->setSingleStep(1);
  inputLayout->addWidget(fLOSpinBox, 3, 1);

  fLOScaleComboBox = new QComboBox();
  fLOScaleComboBox->addItem("Hz");
  fLOScaleComboBox->addItem("kHz");
  fLOScaleComboBox->addItem("MHz");
  fLOScaleComboBox->addItem("GHz");
  fLOScaleComboBox->setCurrentIndex(FrequencyScale::MHz);
  inputLayout->addWidget(fLOScaleComboBox, 3, 2);

  mainLayout->addWidget(inputGroup);

  // Results Group
  QGroupBox *resultsGroup = new QGroupBox("Results");
  resultsGroup->setStyleSheet("QGroupBox { font-weight: bold; }");
  QGridLayout *resultsLayout = new QGridLayout(resultsGroup);

  resultsLayout->addWidget(new QLabel("f<sub>IM</sub>:"), 0, 0);
  fIMResultLabel = new QLabel("0 Hz");
  QFont resultFont = fIMResultLabel->font();
  resultFont.setBold(true);
  fIMResultLabel->setFont(resultFont);
  fIMResultLabel->setAlignment(Qt::AlignCenter);
  fIMResultLabel->setStyleSheet("QLabel { background-color: #f0f0f0; padding: "
                                "5px; border: 1px solid #ccc; }");
  resultsLayout->addWidget(fIMResultLabel, 0, 1);

  mainLayout->addWidget(resultsGroup);

  // Button
  QHBoxLayout *buttonLayout = new QHBoxLayout();
  buttonLayout->addStretch();

  docsButton = new QPushButton("See docs");
  connect(docsButton, &QPushButton::clicked, this,
          &ImageFrequencyCalculatorDialog::showDocumentation);
  buttonLayout->addWidget(docsButton);

  mainLayout->addLayout(buttonLayout);
  mainLayout->addStretch();

  // Connect signals
  connect(modeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
          this, &ImageFrequencyCalculatorDialog::onModeChanged);

  connect(fRFSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &ImageFrequencyCalculatorDialog::recalculateLO);
  connect(fRFScaleComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
          this, &ImageFrequencyCalculatorDialog::recalculateLO);

  connect(fIFSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &ImageFrequencyCalculatorDialog::recalculateLO);
  connect(fIFScaleComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
          this, &ImageFrequencyCalculatorDialog::recalculateLO);

  connect(fLOSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged),
          this, &ImageFrequencyCalculatorDialog::recalculateRF);
  connect(fLOScaleComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
          this, &ImageFrequencyCalculatorDialog::recalculateRF);
}

void ImageFrequencyCalculatorDialog::recalculateLO() {
  // If the RF or IF frequency or the injection mode change,
  // recalculate the LO to keep things consistent

  double fIF = getFrequencyInHz(fIFSpinBox, fIFScaleComboBox);
  double fRF = getFrequencyInHz(fRFSpinBox, fRFScaleComboBox);

  int mode = modeComboBox->currentIndex();
  double fLO;

  if (mode == InjectionMode::LowSide) {
    fLO = fRF - fIF;
  } else { // High-side injection
    fLO = fRF + fIF;
  }

  // Block signals to prevent recursive calls
  fLOSpinBox->blockSignals(true);
  fLOScaleComboBox->blockSignals(true);

  setFreqInputWithUnits(fLOSpinBox, fLOScaleComboBox, fLO);

  fLOSpinBox->blockSignals(false);
  fLOScaleComboBox->blockSignals(false);

  calculate();
}

void ImageFrequencyCalculatorDialog::recalculateRF() {
  // If the LO frequency changes, recalculate the RF to keep things consistent

  double fIF = getFrequencyInHz(fIFSpinBox, fIFScaleComboBox);
  double fLO = getFrequencyInHz(fLOSpinBox, fLOScaleComboBox);

  int mode = modeComboBox->currentIndex();
  double fRF;

  if (mode == InjectionMode::LowSide) {
    fRF = fLO + fIF;
  } else { // High-side injection
    fRF = fLO - fIF;
  }

  // Block signals to prevent recursive calls
  fRFSpinBox->blockSignals(true);
  fRFScaleComboBox->blockSignals(true);

  setFreqInputWithUnits(fRFSpinBox, fRFScaleComboBox, fRF);

  fRFSpinBox->blockSignals(false);
  fRFScaleComboBox->blockSignals(false);

  calculate();
}

void ImageFrequencyCalculatorDialog::onModeChanged(int index) {
  Q_UNUSED(index);
  recalculateLO();
}

void ImageFrequencyCalculatorDialog::calculate() {
  // Get data
  double fIF = getFrequencyInHz(fIFSpinBox, fIFScaleComboBox);
  double fRF = getFrequencyInHz(fRFSpinBox, fRFScaleComboBox);

  int mode = modeComboBox->currentIndex();
  double fIM;

  // Calculations
  if (mode == InjectionMode::LowSide) {
    fIM = fRF - 2 * fIF;
  } else {
    fIM = fRF + 2 * fIF;
  }

  // Display result
  fIMResultLabel->setText(formatFrequency(fIM));
}

void ImageFrequencyCalculatorDialog::setFreqInputWithUnits(
    QDoubleSpinBox *spinBox, QComboBox *comboBox, double val) {
  if (val >= 2e9) {
    // GHz
    val = val * 1e-9;
    spinBox->setValue(val);
    comboBox->setCurrentIndex(FrequencyScale::GHz);
  } else if (val >= 2e6) {
    // MHz
    val = val * 1e-6;
    spinBox->setValue(val);
    comboBox->setCurrentIndex(FrequencyScale::MHz);
  } else if (val >= 2e3) {
    // kHz
    val = val * 1e-3;
    spinBox->setValue(val);
    comboBox->setCurrentIndex(FrequencyScale::kHz);
  } else {
    // Hz
    spinBox->setValue(val);
    comboBox->setCurrentIndex(FrequencyScale::Hz);
  }
}

double ImageFrequencyCalculatorDialog::getFrequencyInHz(QDoubleSpinBox *spinBox,
                                                        QComboBox *comboBox) {
  double value = spinBox->value();
  int scale = comboBox->currentIndex();

  // Convert to Hz based on scale
  return value * std::pow(10.0, scale * 3);
}

QString ImageFrequencyCalculatorDialog::formatFrequency(double freqHz) {
  QString result;

  if (freqHz >= 2e9) {
    freqHz = freqHz * 1e-9;
    result = QString::number(freqHz, 'f', 2) + " GHz";
  } else if (freqHz >= 2e6) {
    freqHz = freqHz * 1e-6;
    result = QString::number(freqHz, 'f', 2) + " MHz";
  } else if (freqHz >= 2e3) {
    freqHz = freqHz * 1e-3;
    result = QString::number(freqHz, 'f', 2) + " kHz";
  } else {
    result = QString::number(freqHz, 'f', 2) + " Hz";
  }

  return result;
}
