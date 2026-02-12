/// @file swr_s11_calculator.h
/// @brief Calculator: Conversion between SWR, S11 and |Γ| (definition)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 28, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "swr_s11_calculator.h"

#include <QComboBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <cmath>

SwrS11CalculatorDialog::SwrS11CalculatorDialog(QWidget *parent)
    : QDialog(parent) {
  setWindowTitle("VSWR ↔ S11 ↔ |Γ| Calculator");

  // Create mode selector combo box
  comboMode = new QComboBox(this);
  comboMode->addItem("VSWR → |Γ| and S11 (dB)");
  comboMode->addItem("S11 (dB) → |Γ| and VSWR");
  comboMode->addItem("|Γ| → S11 (dB) and VSWR");
  comboMode->setCurrentIndex(FROM_VSWR);

  // Initialize input spinboxes
  spinVSWR = new CustomDoubleSpinBox(this);
  spinVSWR->setRange(1.0, 1000.0);
  spinVSWR->setDecimals(2);
  spinVSWR->setSingleStep(0.1);
  spinVSWR->setValue(1.3);

  spinS11dB = new CustomDoubleSpinBox(this);
  spinS11dB->setRange(-100.0, 0.0);
  spinS11dB->setDecimals(1);
  spinS11dB->setSingleStep(0.1);
  spinS11dB->setValue(-17.69);

  spinGammaMag = new CustomDoubleSpinBox(this);
  spinGammaMag->setRange(0.0, 1.0);
  spinGammaMag->setDecimals(2);
  spinGammaMag->setSingleStep(0.01);
  spinGammaMag->setValue(0.3);

  // Create input label (will change based on mode)
  labelInput = new QLabel(this);

  // Create input group box
  inputGroup = new QGroupBox("Input", this);
  inputGroup->setStyleSheet(
      "QGroupBox { font-weight: bold; }"); // Make the title bold
  inputForm = new QFormLayout;
  inputForm->addRow(QString("<b>Calculation Mode:</b>"), comboMode);
  inputForm->addRow(labelInput, spinVSWR); // Will be updated dynamically
  inputForm->setLabelAlignment(Qt::AlignRight);
  inputForm->setSpacing(12);
  inputGroup->setLayout(inputForm);

  // Create results table
  QGroupBox *resultsGroup = new QGroupBox(QString("Results"), this);
  resultsGroup->setStyleSheet(
      "QGroupBox { font-weight: bold; }"); // Make the title bold
  resultsTable = new QTableWidget(2, 2, this);

  // Set up table headers
  resultsTable->setHorizontalHeaderLabels(QStringList()
                                          << "Parameter" << "Value");
  resultsTable->verticalHeader()->setVisible(false);

  // Initialize table items (labels will be updated based on mode)
  for (int i = 0; i < 2; ++i) {
    resultsTable->setItem(i, 0, new QTableWidgetItem("-"));
    QTableWidgetItem *item = new QTableWidgetItem("-");
    item->setTextAlignment(Qt::AlignCenter);
    resultsTable->setItem(i, 1, item);
    resultsTable->item(i, 0)->setFlags(resultsTable->item(i, 0)->flags() &
                                       ~Qt::ItemIsEditable);
    resultsTable->item(i, 1)->setFlags(resultsTable->item(i, 1)->flags() &
                                       ~Qt::ItemIsEditable);
  }

  // Style the table
  resultsTable->setAlternatingRowColors(true);
  resultsTable->horizontalHeader()->setStretchLastSection(true);
  resultsTable->horizontalHeader()->setSectionResizeMode(
      0, QHeaderView::ResizeToContents);
  resultsTable->setSelectionMode(QAbstractItemView::SingleSelection);
  resultsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
  resultsTable->setMinimumHeight(100);

  // ========== Documentation Button ==========
  QPushButton *btnDocs = new QPushButton("See Docs", this);
  connect(btnDocs, &QPushButton::clicked, this,
          &SwrS11CalculatorDialog::showDocumentation);

  QVBoxLayout *resultsLayout = new QVBoxLayout;
  resultsLayout->addWidget(resultsTable);
  resultsGroup->setLayout(resultsLayout);

  // Main layout
  QVBoxLayout *main = new QVBoxLayout;
  main->addWidget(inputGroup);
  main->addSpacing(10);
  main->addWidget(resultsGroup);
  main->setSpacing(8);
  main->setContentsMargins(15, 15, 15, 15);
  main->addSpacing(10);
  main->addWidget(btnDocs);

  setLayout(main);
  setMinimumWidth(400);
  setMinimumHeight(325);

  // Connect mode change
  connect(comboMode, QOverload<int>::of(&QComboBox::currentIndexChanged), this,
          &SwrS11CalculatorDialog::on_modeChanged);

  // Live updates when inputs change
  connect(spinVSWR, QOverload<double>::of(&CustomDoubleSpinBox::valueChanged),
          this, &SwrS11CalculatorDialog::on_inputChanged);
  connect(spinS11dB, QOverload<double>::of(&CustomDoubleSpinBox::valueChanged),
          this, &SwrS11CalculatorDialog::on_inputChanged);
  connect(spinGammaMag,
          QOverload<double>::of(&CustomDoubleSpinBox::valueChanged), this,
          &SwrS11CalculatorDialog::on_inputChanged);

  // Initialize UI for default mode
  updateUIForMode();

  // Compute initial values
  computeResults();
}

void SwrS11CalculatorDialog::on_modeChanged(int index) {
  Q_UNUSED(index);
  updateUIForMode();
  computeResults();
}

void SwrS11CalculatorDialog::updateUIForMode() {
  CalculationMode mode =
      static_cast<CalculationMode>(comboMode->currentIndex());

  // Hide all input widgets first
  spinVSWR->setVisible(false);
  spinS11dB->setVisible(false);
  spinGammaMag->setVisible(false);

  // Remove the input row if it exists (but this will be re-added)
  if (inputForm->rowCount() > 1) {
    // Get the widgets before removing
    QLayoutItem *fieldItem = inputForm->itemAt(1, QFormLayout::FieldRole);

    if (fieldItem) {
      inputForm->removeItem(fieldItem);
    }
  }

  switch (mode) {
  case FROM_VSWR:
    labelInput->setText(tr("<b>VSWR:</b>"));
    if (inputForm->rowCount() > 1) {
      inputForm->setWidget(1, QFormLayout::FieldRole, spinVSWR);
    } else {
      inputForm->addRow(labelInput, spinVSWR);
    }
    spinVSWR->setVisible(true);

    // Update table labels
    resultsTable->item(0, 0)->setText(tr("|Γ|"));
    resultsTable->item(1, 0)->setText(tr("S₁₁ (dB)"));
    break;

  case FROM_S11_DB:
    labelInput->setText(tr("<b>S₁₁ (dB):</b>"));
    if (inputForm->rowCount() > 1) {
      inputForm->setWidget(1, QFormLayout::FieldRole, spinS11dB);
    } else {
      inputForm->addRow(labelInput, spinS11dB);
    }
    spinS11dB->setVisible(true);

    // Update table labels
    resultsTable->item(0, 0)->setText(tr("|Γ|"));
    resultsTable->item(1, 0)->setText(tr("VSWR"));
    break;

  case FROM_GAMMA:
    labelInput->setText(tr("<b>|Γ|:</b>"));
    if (inputForm->rowCount() > 1) {
      inputForm->setWidget(1, QFormLayout::FieldRole, spinGammaMag);
    } else {
      inputForm->addRow(labelInput, spinGammaMag);
    }
    spinGammaMag->setVisible(true);

    // Update table labels
    resultsTable->item(0, 0)->setText(tr("S₁₁ (dB)"));
    resultsTable->item(1, 0)->setText(tr("VSWR"));
    break;
  }
}

double SwrS11CalculatorDialog::gammaFromVSWR(double vswr) const {
  if (vswr < 1.0)
    return 0.0; // Invalid VSWR
  return (vswr - 1.0) / (vswr + 1.0);
}

double SwrS11CalculatorDialog::vswrFromGamma(double gamma) const {
  const double eps = 1e-12;
  if (gamma >= 1.0 - eps)
    return INFINITY; // Total reflection
  if (gamma < 0.0)
    return 1.0; // Invalid gamma
  return (1.0 + gamma) / (1.0 - gamma);
}

double SwrS11CalculatorDialog::s11dBFromGamma(double gamma) const {
  const double eps = 1e-12;
  if (gamma <= eps)
    return -INFINITY; // Perfect match
  return 20.0 * std::log10(gamma);
}

double SwrS11CalculatorDialog::gammaFromS11dB(double s11db) const {
  if (s11db > 0.0)
    return 1.0; // Invalid S11 (should be ≤ 0)
  return std::pow(10.0, s11db / 20.0);
}

void SwrS11CalculatorDialog::computeResults() {
  CalculationMode mode =
      static_cast<CalculationMode>(comboMode->currentIndex());

  switch (mode) {
  case FROM_VSWR: {
    // Input: VSWR
    // Output: |Γ| and S11 (dB)
    double vswr = spinVSWR->value();

    if (vswr < 1.0) {
      resultsTable->item(0, 1)->setText(tr("Invalid"));
      resultsTable->item(1, 1)->setText(tr("Invalid"));
      resultsTable->item(0, 1)->setForeground(QBrush(QColor(180, 0, 0)));
      resultsTable->item(1, 1)->setForeground(QBrush(QColor(180, 0, 0)));
      return;
    }

    double gamma = gammaFromVSWR(vswr);
    double s11db = s11dBFromGamma(gamma);

    resultsTable->item(0, 1)->setText(QString::number(gamma, 'f', 6));
    resultsTable->item(0, 1)->setForeground(QBrush(QColor(0, 0, 0)));

    if (std::isinf(s11db)) {
      resultsTable->item(1, 1)->setText("-∞");
    } else {
      resultsTable->item(1, 1)->setText(QString::number(s11db, 'f', 4));
    }
    resultsTable->item(1, 1)->setForeground(QBrush(QColor(0, 0, 0)));
    break;
  }

  case FROM_S11_DB: {
    // Input: S11 (dB)
    // Output: |Γ| and VSWR
    double s11db = spinS11dB->value();

    if (s11db > 0.0) {
      resultsTable->item(0, 1)->setText(tr("Invalid"));
      resultsTable->item(1, 1)->setText(tr("Invalid"));
      resultsTable->item(0, 1)->setForeground(QBrush(QColor(180, 0, 0)));
      resultsTable->item(1, 1)->setForeground(QBrush(QColor(180, 0, 0)));
      return;
    }

    double gamma = gammaFromS11dB(s11db);
    double vswr = vswrFromGamma(gamma);

    resultsTable->item(0, 1)->setText(QString::number(gamma, 'f', 6));
    resultsTable->item(0, 1)->setForeground(QBrush(QColor(0, 0, 0)));

    if (std::isinf(vswr)) {
      resultsTable->item(1, 1)->setText("∞");
      resultsTable->item(1, 1)->setForeground(QBrush(QColor(180, 0, 0)));
    } else {
      resultsTable->item(1, 1)->setText(QString::number(vswr, 'f', 6));
      resultsTable->item(1, 1)->setForeground(QBrush(QColor(0, 0, 0)));
    }
    break;
  }

  case FROM_GAMMA: {
    // Input: |Γ|
    // Output: S11 (dB) and VSWR
    double gamma = spinGammaMag->value();

    if (gamma < 0.0 || gamma > 1.0) {
      resultsTable->item(0, 1)->setText(tr("Invalid"));
      resultsTable->item(1, 1)->setText(tr("Invalid"));
      resultsTable->item(0, 1)->setForeground(QBrush(QColor(180, 0, 0)));
      resultsTable->item(1, 1)->setForeground(QBrush(QColor(180, 0, 0)));
      return;
    }

    double s11db = s11dBFromGamma(gamma);
    double vswr = vswrFromGamma(gamma);

    if (std::isinf(s11db)) {
      resultsTable->item(0, 1)->setText("-∞");
    } else {
      resultsTable->item(0, 1)->setText(QString::number(s11db, 'f', 4));
    }
    resultsTable->item(0, 1)->setForeground(QBrush(QColor(0, 0, 0)));

    if (std::isinf(vswr)) {
      resultsTable->item(1, 1)->setText("∞");
      resultsTable->item(1, 1)->setForeground(QBrush(QColor(180, 0, 0)));
    } else {
      resultsTable->item(1, 1)->setText(QString::number(vswr, 'f', 6));
      resultsTable->item(1, 1)->setForeground(QBrush(QColor(0, 0, 0)));
    }
    break;
  }
  }
}

void SwrS11CalculatorDialog::on_inputChanged() {
  // Provide live feedback; do not pop errors — just compute
  computeResults();
}
