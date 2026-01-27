/// @file impedance_calculator.cpp
/// @brief Simple calculator: Impedance (Z) to Γ, VSWR and S11 (implementation)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 27, 2026
/// @copyright Copyright (C) 2019-2025 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "impedance_calculator.h"

#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <cmath>

ImpedanceCalculatorDialog::ImpedanceCalculatorDialog(QWidget *parent)
    : QDialog(parent) {
  setWindowTitle(tr("Z → Γ / SWR / S11 Calculator"));

  // Initialize input spinboxes
  spinReZ = new CustomDoubleSpinBox(this);
  spinReZ->setRange(-1e6, 1e6);
  spinReZ->setDecimals(1);
  spinReZ->setSingleStep(1.0);
  spinReZ->setValue(75);

  spinImZ = new CustomDoubleSpinBox(this);
  spinImZ->setRange(-1e6, 1e6);
  spinImZ->setDecimals(1);
  spinImZ->setSingleStep(1.0);
  spinImZ->setValue(0.0);

  spinZ0 = new CustomDoubleSpinBox(this);
  spinZ0->setRange(0.1, 1e6);
  spinZ0->setDecimals(1);
  spinZ0->setSingleStep(1.0);
  spinZ0->setValue(50.0);

  // Create input group box
  QGroupBox *inputGroup = new QGroupBox(tr("Input Parameters"), this);
  QFormLayout *inputForm = new QFormLayout;
  inputForm->addRow(tr("<b>Re{Z}</b> (Ω):"), spinReZ);
  inputForm->addRow(tr("<b>Im{Z}</b> (Ω):"), spinImZ);
  inputForm->addRow(tr("<b>Z₀</b> (Ω):"), spinZ0);
  inputForm->setLabelAlignment(Qt::AlignRight);
  inputForm->setSpacing(12);
  inputGroup->setLayout(inputForm);

  // Create results table
  QGroupBox *resultsGroup = new QGroupBox(tr("Calculated Results"), this);
  resultsTable = new QTableWidget(3, 2, this);

  // Set up table headers
  resultsTable->setHorizontalHeaderLabels(QStringList()
                                          << tr("Parameter") << tr("Value"));
  resultsTable->verticalHeader()->setVisible(false);

  // Set row labels
  resultsTable->setItem(0, 0, new QTableWidgetItem(tr("Γ (|Γ| ∠ deg)")));
  resultsTable->setItem(1, 0, new QTableWidgetItem(tr("VSWR")));
  resultsTable->setItem(2, 0, new QTableWidgetItem(tr("S₁₁ (dB)")));

  // Initialize value cells
  for (int i = 0; i < 3; ++i) {
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
  resultsTable->setMinimumHeight(120);

  // Apply modern styling to table
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

  // Main layout
  QVBoxLayout *main = new QVBoxLayout;
  main->addWidget(inputGroup);
  main->addSpacing(10);
  main->addWidget(resultsGroup);
  main->setSpacing(8);
  main->setContentsMargins(15, 15, 15, 15);

  setLayout(main);
  setMinimumWidth(400);
  setMinimumHeight(425);

  // Live updates when inputs change
  connect(spinReZ, QOverload<double>::of(&CustomDoubleSpinBox::valueChanged),
          this, &ImpedanceCalculatorDialog::on_inputChanged);
  connect(spinImZ, QOverload<double>::of(&CustomDoubleSpinBox::valueChanged),
          this, &ImpedanceCalculatorDialog::on_inputChanged);
  connect(spinZ0, QOverload<double>::of(&CustomDoubleSpinBox::valueChanged),
          this, &ImpedanceCalculatorDialog::on_inputChanged);

  // Compute initial values
  computeResults();
}

std::complex<double> ImpedanceCalculatorDialog::impedanceFromInputs() const {
  double re = spinReZ->value();
  double im = spinImZ->value();
  return std::complex<double>(re, im);
}

void ImpedanceCalculatorDialog::computeResults() {
  const double eps = 1e-12;

  // Get impedance and Z0
  std::complex<double> Z = impedanceFromInputs();
  double Z0 = spinZ0->value();

  // Calculate reflection coefficient: Γ = (Z - Z0) / (Z + Z0)
  std::complex<double> Z0_complex(Z0, 0.0);
  std::complex<double> numerator = Z - Z0_complex;
  std::complex<double> denominator = Z + Z0_complex;

  // Check for division issues
  if (std::abs(denominator) < eps) {
    resultsTable->item(0, 1)->setText(tr("Undefined"));
    resultsTable->item(1, 1)->setText(tr("∞"));
    resultsTable->item(2, 1)->setText(tr("Undefined"));
    resultsTable->item(0, 1)->setForeground(QBrush(QColor(180, 0, 0)));
    resultsTable->item(1, 1)->setForeground(QBrush(QColor(180, 0, 0)));
    resultsTable->item(2, 1)->setForeground(QBrush(QColor(180, 0, 0)));
    return;
  }

  std::complex<double> gamma = numerator / denominator;
  double mag = std::abs(gamma);
  double angle_rad = std::arg(gamma);
  double angle_deg = angle_rad * 180.0 / M_PI;

  // Display Γ in polar form: |Γ| ∠ angle°
  QString gammaStr =
      QString("%1 ∠ %2°").arg(mag, 0, 'f', 2).arg(angle_deg, 0, 'f', 1);
  resultsTable->item(0, 1)->setText(gammaStr);
  resultsTable->item(0, 1)->setForeground(QBrush(QColor(0, 0, 0)));

  // VSWR: (1+|gamma|)/(1-|gamma|) (if |gamma| < 1)
  if (mag >= 1.0 - eps) {
    resultsTable->item(1, 1)->setText(tr("∞"));
    resultsTable->item(1, 1)->setForeground(QBrush(QColor(180, 0, 0)));
  } else {
    double vswr = (1.0 + mag) / (1.0 - mag);
    resultsTable->item(1, 1)->setText(QString::number(vswr, 'f', 2));
    resultsTable->item(1, 1)->setForeground(QBrush(QColor(0, 0, 0)));
  }

  // S11 in dB: 20*log10(|gamma|)
  if (mag <= eps) {
    resultsTable->item(2, 1)->setText("-∞");
  } else {
    double s11db = 20.0 * std::log10(mag);
    resultsTable->item(2, 1)->setText(QString::number(s11db, 'f', 1));
  }
  resultsTable->item(2, 1)->setForeground(QBrush(QColor(0, 0, 0)));
}

void ImpedanceCalculatorDialog::on_inputChanged() {
  // Provide live feedback; do not pop errors — just compute
  computeResults();
}
