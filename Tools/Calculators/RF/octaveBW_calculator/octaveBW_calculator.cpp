/// @file octaveBW_calculator.cpp
/// @brief Calculator: Calculate the number of octaves and decades in a band
/// given the corner frequencies (implementation)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 28, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "octaveBW_calculator.h"

#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <cmath>

OctaveBWCalculatorDialog::OctaveBWCalculatorDialog(QWidget *parent)
    : QDialog(parent) {
  setWindowTitle(tr("Octave Bandwidth Calculator"));

  // Initialize input spinboxes
  spinFLow = new CustomDoubleSpinBox(this);
  spinFLow->setRange(1.0, 1e12); // 1 Hz to 1 THz
  spinFLow->setDecimals(1);
  spinFLow->setSingleStep(10);
  spinFLow->setValue(1000.0); // Default: 1 kHz

  spinFHigh = new CustomDoubleSpinBox(this);
  spinFHigh->setRange(1.0, 1e12); // 1 Hz to 1 THz
  spinFHigh->setDecimals(1);
  spinFHigh->setSingleStep(10);
  spinFHigh->setValue(2000.0); // Default: 2 kHz

  QString note = QString("<i><b>Note</b>: f<sub>low</sub> and f<sub>high</sub> "
                         "must have the same units (kHz, MHz, GHz)</i>");

  QLabel *label = new QLabel(note);

  // Create input group box
  QGroupBox *inputGroup = new QGroupBox(QString("Input Parameters"), this);
  inputGroup->setStyleSheet(
      "QGroupBox { font-weight: bold; }"); // Make the title bold
  QFormLayout *inputForm = new QFormLayout;
  inputForm->addRow(QString("<b>f<sub>low</sub></b>:"), spinFLow);
  inputForm->addRow(QString("<b>f<sub>high</sub></b>:"), spinFHigh);
  inputForm->addRow(label);
  inputForm->setLabelAlignment(Qt::AlignRight);
  inputForm->setSpacing(12);
  inputGroup->setLayout(inputForm);

  // Create results table
  QGroupBox *resultsGroup = new QGroupBox(QString("Results"), this);
  resultsGroup->setStyleSheet(
      "QGroupBox { font-weight: bold; }"); // Make the title bold
  resultsTable = new QTableWidget(6, 2, this);

  // Set up table headers
  resultsTable->setHorizontalHeaderLabels(QStringList()
                                          << "Parameter" << "Value");
  resultsTable->verticalHeader()->setVisible(false);

  // Set row labels
  resultsTable->setItem(0, 0,
                        new QTableWidgetItem("Central freq (Arithmetic mean)"));
  resultsTable->setItem(1, 0,
                        new QTableWidgetItem("Central freq (Geometric mean)"));
  resultsTable->setItem(2, 0, new QTableWidgetItem("BW"));
  resultsTable->setItem(3, 0, new QTableWidgetItem("# Octaves"));
  resultsTable->setItem(4, 0, new QTableWidgetItem("# Decades"));
  resultsTable->setItem(5, 0, new QTableWidgetItem("Q"));

  // Initialize value cells
  for (int i = 0; i < 6; ++i) {
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
  resultsTable->setMinimumHeight(180);

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

  // Main layout
  QVBoxLayout *main = new QVBoxLayout;
  main->addWidget(inputGroup);
  main->addSpacing(10);
  main->addWidget(resultsGroup);
  main->setSpacing(8);
  main->setContentsMargins(15, 15, 15, 15);

  setLayout(main);
  setMinimumWidth(400);
  setMinimumHeight(500);

  // Live updates when inputs change
  connect(spinFLow, QOverload<double>::of(&CustomDoubleSpinBox::valueChanged),
          this, &OctaveBWCalculatorDialog::on_inputChanged);
  connect(spinFHigh, QOverload<double>::of(&CustomDoubleSpinBox::valueChanged),
          this, &OctaveBWCalculatorDialog::on_inputChanged);

  // Compute initial values
  computeResults();
}

void OctaveBWCalculatorDialog::computeResults() {
  const double eps = 1e-12;

  // Get data from inputs
  double fLow = spinFLow->value();
  double fHigh = spinFHigh->value();

  // Validate input: fHigh must be greater than fLow
  if (fHigh <= fLow + eps) {
    // Display error state
    resultsTable->item(0, 1)->setText(tr("Error"));
    resultsTable->item(1, 1)->setText(tr("Error"));
    resultsTable->item(2, 1)->setText(tr("Error"));
    resultsTable->item(3, 1)->setText(tr("Error"));
    resultsTable->item(4, 1)->setText(tr("Error"));
    resultsTable->item(5, 1)->setText(tr("Error"));

    // Set error color
    for (int i = 0; i < 6; ++i) {
      resultsTable->item(i, 1)->setForeground(QBrush(QColor(180, 0, 0)));
    }
    return;
  }

  // Reset colors to normal
  for (int i = 0; i < 6; ++i) {
    resultsTable->item(i, 1)->setForeground(QBrush(QColor(0, 0, 0)));
  }

  // Calculate center frequency (arithmetic mean)
  double fc_arithmetic = (fHigh - fLow) / 2;
  resultsTable->item(0, 1)->setText(QString::number(fc_arithmetic, 'f', 1));

  // Calculate center frequency (geometric mean)
  double fc_geometric = std::sqrt(fLow * fHigh);
  resultsTable->item(1, 1)->setText(QString::number(fc_geometric, 'f', 1));

  // Calculate bandwidth
  double bw = fHigh - fLow;
  resultsTable->item(2, 1)->setText(QString::number(bw, 'f', 1));

  // Calculate number of octaves: log2(fHigh / fLow)
  double nOctaves = std::log2(fHigh / fLow);
  resultsTable->item(3, 1)->setText(QString::number(nOctaves, 'f', 1));

  // Calculate number of decades: log10(fHigh / fLow)
  double nDecades = std::log10(fHigh / fLow);
  resultsTable->item(4, 1)->setText(QString::number(nDecades, 'f', 1));

  // Calculate Q: fc / BW
  if (bw < eps) {
    resultsTable->item(5, 1)->setText(tr("∞"));
    resultsTable->item(5, 1)->setForeground(QBrush(QColor(180, 0, 0)));
  } else {
    double q = fc_arithmetic / bw;
    resultsTable->item(5, 1)->setText(QString::number(q, 'f', 1));
  }
}

void OctaveBWCalculatorDialog::on_inputChanged() {
  // Provide live feedback; do not pop errors — just compute
  computeResults();
}
