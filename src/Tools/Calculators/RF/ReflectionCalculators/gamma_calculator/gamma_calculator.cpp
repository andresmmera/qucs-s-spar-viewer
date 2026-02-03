/// @file gamma_calculator.cpp
/// @brief Calculator: Reflection coefficient (Γ) to Z, VSWR and S11
/// (implementation)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 27, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "gamma_calculator.h"

#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <cmath>

GammaCalculatorDialog::GammaCalculatorDialog(QWidget *parent)
    : QDialog(parent) {
  setWindowTitle(tr("Γ → Z / SWR / S11 Calculator"));

  // Initialize input spinboxes
  spinMag = new CustomDoubleSpinBox(this);
  spinMag->setRange(0.0, 10.0);
  spinMag->setDecimals(2);
  spinMag->setSingleStep(0.01);
  spinMag->setValue(0.2);

  spinAngle = new CustomDoubleSpinBox(this);
  spinAngle->setRange(-360.0, 360.0);
  spinAngle->setDecimals(2);
  spinAngle->setSingleStep(1.0);
  spinAngle->setValue(0.0);

  spinZ0 = new CustomDoubleSpinBox(this);
  spinZ0->setRange(0.1, 1e6);
  spinZ0->setDecimals(1);
  spinZ0->setSingleStep(1.0);
  spinZ0->setValue(50.0);

  // Create input group box
  QGroupBox *inputGroup = new QGroupBox(QString("Input Parameters"), this);
  inputGroup->setStyleSheet(
      "QGroupBox { font-weight: bold; }"); // Make the title bold
  QFormLayout *inputForm = new QFormLayout;
  inputForm->addRow(QString("<b>|Γ|</b> (Magnitude):"), spinMag);
  inputForm->addRow(QString("<b>∠Γ</b> (Degrees):"), spinAngle);
  inputForm->addRow(QString("<b>Z₀</b> (Ω):"), spinZ0);
  inputForm->setLabelAlignment(Qt::AlignRight);
  inputForm->setSpacing(12);
  inputGroup->setLayout(inputForm);

  // Create results table
  QGroupBox *resultsGroup = new QGroupBox(QString("Results"), this);
  resultsGroup->setStyleSheet(
      "QGroupBox { font-weight: bold; }"); // Make the title bold
  resultsTable = new QTableWidget(4, 2, this);

  // Set up table headers
  resultsTable->setHorizontalHeaderLabels(QStringList()
                                          << "Parameter" << "Value");
  resultsTable->verticalHeader()->setVisible(false);

  // Set row labels
  resultsTable->setItem(0, 0, new QTableWidgetItem("Re{Z} (Ω)"));
  resultsTable->setItem(1, 0, new QTableWidgetItem("Im{Z} (Ω)"));
  resultsTable->setItem(2, 0, new QTableWidgetItem("VSWR"));
  resultsTable->setItem(3, 0, new QTableWidgetItem("S₁₁ (dB)"));

  // Initialize value cells
  for (int i = 0; i < 4; ++i) {
    QTableWidgetItem *item = new QTableWidgetItem("-");
    item->setTextAlignment(Qt::AlignCenter);
    resultsTable->setItem(i, 1, item);
    resultsTable->item(i, 0)->setFlags(resultsTable->item(i, 0)->flags() &
                                       ~Qt::ItemIsEditable);
    resultsTable->item(i, 1)->setFlags(resultsTable->item(i, 1)->flags() &
                                       ~Qt::ItemIsEditable);
  }

  // Table settings
  resultsTable->setAlternatingRowColors(true);
  resultsTable->horizontalHeader()->setStretchLastSection(true);
  resultsTable->horizontalHeader()->setSectionResizeMode(
      0, QHeaderView::ResizeToContents);
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

  // ========== Documentation Button ==========
  QPushButton *btnDocs = new QPushButton("See Docs", this);
  connect(btnDocs, &QPushButton::clicked, this,
          &GammaCalculatorDialog::showDocumentation);

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
  setMinimumHeight(500);

  // Live updates when inputs change
  connect(spinMag, QOverload<double>::of(&CustomDoubleSpinBox::valueChanged),
          this, &GammaCalculatorDialog::on_inputChanged);
  connect(spinAngle, QOverload<double>::of(&CustomDoubleSpinBox::valueChanged),
          this, &GammaCalculatorDialog::on_inputChanged);
  connect(spinZ0, QOverload<double>::of(&CustomDoubleSpinBox::valueChanged),
          this, &GammaCalculatorDialog::on_inputChanged);

  // Compute initial values
  computeResults();
}

std::complex<double> GammaCalculatorDialog::gammaFromInputs() const {
  double mag = spinMag->value();
  double angle_deg = spinAngle->value();
  double angle_rad = angle_deg * M_PI / 180.0;
  return std::complex<double>(mag * std::cos(angle_rad),
                              mag * std::sin(angle_rad));
}

void GammaCalculatorDialog::computeResults() {
  const double eps = 1e-12;
  std::complex<double> gamma = gammaFromInputs();
  double mag = std::abs(gamma);

  // S11 in dB: 20*log10(|gamma|)
  if (mag <= eps) {
    resultsTable->item(3, 1)->setText("-∞");
  } else {
    double s11db = 20.0 * std::log10(mag);
    resultsTable->item(3, 1)->setText(QString::number(s11db, 'f', 1));
  }

  // VSWR: (1+|gamma|)/(1-|gamma|) (if |gamma| < 1)
  if (mag >= 1.0 - 1e-12) {
    resultsTable->item(2, 1)->setText(tr("∞"));
    // Add visual warning for invalid VSWR
    resultsTable->item(2, 1)->setForeground(QBrush(QColor(180, 0, 0)));
  } else {
    double vswr = (1.0 + mag) / (1.0 - mag);
    resultsTable->item(2, 1)->setText(QString::number(vswr, 'f', 2));
    resultsTable->item(2, 1)->setForeground(QBrush(QColor(0, 0, 0)));
  }

  // Impedance: Z = Z0 * (1 + gamma) / (1 - gamma)
  double Z0 = spinZ0->value();
  std::complex<double> denom = std::complex<double>(1.0, 0.0) - gamma;
  if (std::abs(denom) < 1e-15) {
    resultsTable->item(0, 1)->setText(tr("NaN"));
    resultsTable->item(1, 1)->setText(tr("NaN"));
    resultsTable->item(0, 1)->setForeground(QBrush(QColor(180, 0, 0)));
    resultsTable->item(1, 1)->setForeground(QBrush(QColor(180, 0, 0)));
  } else {
    std::complex<double> Z = std::complex<double>(Z0) *
                             (std::complex<double>(1.0, 0.0) + gamma) / denom;
    resultsTable->item(0, 1)->setText(QString::number(Z.real(), 'f', 1));
    resultsTable->item(1, 1)->setText(QString::number(Z.imag(), 'f', 1));
    resultsTable->item(0, 1)->setForeground(QBrush(QColor(0, 0, 0)));
    resultsTable->item(1, 1)->setForeground(QBrush(QColor(0, 0, 0)));
  }
}

void GammaCalculatorDialog::on_inputChanged() {
  // Provide live feedback; do not pop errors — just compute
  computeResults();
}
