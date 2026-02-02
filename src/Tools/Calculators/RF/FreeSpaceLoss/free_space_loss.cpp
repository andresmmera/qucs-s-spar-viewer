/// @file free_space_attenuation.cpp
/// @brief Calculator: Calculate free space path loss (implementation)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 29, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "free_space_loss.h"

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

// Speed of light in vacuum (m/s)
constexpr double SPEED_OF_LIGHT = 299792458.0;

FreeSpaceAttenuationDialog::FreeSpaceAttenuationDialog(QWidget *parent)
    : QDialog(parent) {
  setWindowTitle(tr("Free Space Path Loss Calculator"));

  // ========== Frequency Input ==========
  QGroupBox *freqGroup = new QGroupBox(QString("Frequency"), this);
  freqGroup->setStyleSheet("QGroupBox { font-weight: bold; }");

  spinFrequency = new CustomDoubleSpinBox(this);
  spinFrequency->setRange(0.0, 1e15);
  spinFrequency->setDecimals(1);
  spinFrequency->setSingleStep(1.0);
  spinFrequency->setValue(1000);

  comboFreqUnits = new QComboBox(this);
  comboFreqUnits->addItem("Hz", "Hz");
  comboFreqUnits->addItem("kHz", "kHz");
  comboFreqUnits->addItem("MHz", "MHz");
  comboFreqUnits->addItem("GHz", "GHz");
  comboFreqUnits->addItem("THz", "THz");
  comboFreqUnits->setCurrentIndex(2); // Default: MHz

  QFormLayout *freqLayout = new QFormLayout;
  freqLayout->addRow(QString("<b>Frequency:</b>"), spinFrequency);
  freqLayout->addRow(QString("<b>Units:</b>"), comboFreqUnits);
  freqLayout->setLabelAlignment(Qt::AlignRight);
  freqLayout->setSpacing(12);
  freqGroup->setLayout(freqLayout);

  // ========== Distance Input ==========
  QGroupBox *distanceGroup = new QGroupBox(QString("Distance"), this);
  distanceGroup->setStyleSheet("QGroupBox { font-weight: bold; }");

  spinDistance = new CustomDoubleSpinBox(this);
  spinDistance->setRange(0.0, 1e15);
  spinDistance->setDecimals(2);
  spinDistance->setSingleStep(1.0);
  spinDistance->setValue(1.0);

  comboDistanceUnits = new QComboBox(this);
  comboDistanceUnits->addItem("m", "m");
  comboDistanceUnits->addItem("km", "km");
  comboDistanceUnits->addItem("cm", "cm");
  comboDistanceUnits->addItem("mm", "mm");
  comboDistanceUnits->addItem("ft", "ft");
  comboDistanceUnits->addItem("mi", "mi");
  comboDistanceUnits->addItem("nmi", "nmi"); // nautical miles
  comboDistanceUnits->setCurrentIndex(1);    // Default: km

  QFormLayout *distanceLayout = new QFormLayout;
  distanceLayout->addRow(QString("<b>Distance:</b>"), spinDistance);
  distanceLayout->addRow(QString("<b>Units:</b>"), comboDistanceUnits);
  distanceLayout->setLabelAlignment(Qt::AlignRight);
  distanceLayout->setSpacing(12);
  distanceGroup->setLayout(distanceLayout);

  // ========== Antenna Gains ==========
  QGroupBox *gainsGroup = new QGroupBox(QString("Antenna Gains"), this);
  gainsGroup->setStyleSheet("QGroupBox { font-weight: bold; }");

  spinGainTX = new CustomDoubleSpinBox(this);
  spinGainTX->setRange(-50.0, 100.0);
  spinGainTX->setDecimals(1);
  spinGainTX->setSingleStep(1);
  spinGainTX->setValue(0.0); // Default: 0 dBi (isotropic)
  spinGainTX->setSuffix(" dB");

  spinGainRX = new CustomDoubleSpinBox(this);
  spinGainRX->setRange(-50.0, 100.0);
  spinGainRX->setDecimals(1);
  spinGainRX->setSingleStep(1);
  spinGainRX->setValue(0.0); // Default: 0 dBi (isotropic)
  spinGainRX->setSuffix(" dB");

  QFormLayout *gainsLayout = new QFormLayout;
  gainsLayout->addRow(QString("<b>G<sub>TX</sub> (Transmitter):</b>"),
                      spinGainTX);
  gainsLayout->addRow(QString("<b>G<sub>RX</sub> (Receiver):</b>"), spinGainRX);
  gainsLayout->setLabelAlignment(Qt::AlignRight);
  gainsLayout->setSpacing(12);
  gainsGroup->setLayout(gainsLayout);

  // ========== Results Table ==========
  QGroupBox *resultsGroup =
      new QGroupBox(QString("Free Space Path Loss"), this);
  resultsGroup->setStyleSheet("QGroupBox { font-weight: bold; }");

  resultsTable = new QTableWidget(5, 2, this);
  resultsTable->setHorizontalHeaderLabels(QStringList()
                                          << "Distance" << "Path Loss (dB)");
  resultsTable->verticalHeader()->setVisible(false);

  // Set row labels using QLabel widgets
  label_d_4 = new QLabel("d/4");
  label_d_4->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  resultsTable->setCellWidget(0, 0, label_d_4);

  label_d_2 = new QLabel("d/2");
  label_d_2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  resultsTable->setCellWidget(1, 0, label_d_2);

  label_d = new QLabel("<b>d (Specified)</b>");
  label_d->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  label_d->setTextFormat(Qt::RichText);
  resultsTable->setCellWidget(2, 0, label_d);

  label_dx2 = new QLabel("2×d");
  label_dx2->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  resultsTable->setCellWidget(3, 0, label_dx2);

  label_dx4 = new QLabel("4×d");
  label_dx4->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  resultsTable->setCellWidget(4, 0, label_dx4);

  // Initialize value cells
  for (int i = 0; i < 5; ++i) {
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
  resultsTable->setMinimumHeight(200);

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
  mainLayout->addWidget(freqGroup);
  mainLayout->addSpacing(10);
  mainLayout->addWidget(distanceGroup);
  mainLayout->addSpacing(10);
  mainLayout->addWidget(gainsGroup);
  mainLayout->addSpacing(10);
  mainLayout->addWidget(resultsGroup);
  mainLayout->setSpacing(8);
  mainLayout->setContentsMargins(15, 15, 15, 15);

  // Docs button
  QHBoxLayout *buttonLayout = new QHBoxLayout();
  buttonLayout->addStretch();

  docsButton = new QPushButton("See docs");
  connect(docsButton, &QPushButton::clicked, this,
          &FreeSpaceAttenuationDialog::showDocumentation);
  buttonLayout->addWidget(docsButton);
  mainLayout->addLayout(buttonLayout);
  mainLayout->addStretch();

  setLayout(mainLayout);
  setMinimumWidth(500);
  setMinimumHeight(650);

  // ========== Connect Signals ==========
  connect(spinFrequency, SIGNAL(valueChanged(double)), this,
          SLOT(computePathLoss()));
  connect(spinFrequency, SIGNAL(editingFinished()), this,
          SLOT(computePathLoss()));
  connect(comboFreqUnits, SIGNAL(currentIndexChanged(int)), this,
          SLOT(computePathLoss()));

  connect(spinDistance, SIGNAL(valueChanged(double)), this,
          SLOT(computePathLoss()));
  connect(spinDistance, SIGNAL(editingFinished()), this,
          SLOT(computePathLoss()));
  connect(comboDistanceUnits, SIGNAL(currentIndexChanged(int)), this,
          SLOT(computePathLoss()));

  connect(spinGainTX, SIGNAL(valueChanged(double)), this,
          SLOT(computePathLoss()));
  connect(spinGainTX, SIGNAL(editingFinished()), this, SLOT(computePathLoss()));

  connect(spinGainRX, SIGNAL(valueChanged(double)), this,
          SLOT(computePathLoss()));
  connect(spinGainRX, SIGNAL(editingFinished()), this, SLOT(computePathLoss()));

  // Compute initial values
  computePathLoss();
}

double
FreeSpaceAttenuationDialog::convertFrequencyToHz(double freq,
                                                 const QString &units) const {
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

double FreeSpaceAttenuationDialog::convertDistanceToMeters(
    double distance, const QString &units) const {
  if (units == "m")
    return distance;
  if (units == "km")
    return distance * 1e3;
  if (units == "cm")
    return distance * 1e-2;
  if (units == "mm")
    return distance * 1e-3;
  if (units == "ft")
    return distance * 0.3048;
  if (units == "mi")
    return distance * 1609.344;
  if (units == "nmi")
    return distance * 1852.0; // nautical mile
  return distance;
}

double FreeSpaceAttenuationDialog::calculateFSPL(double freqHz,
                                                 double distanceM,
                                                 double gainTX,
                                                 double gainRX) const {
  // Free Space Path Loss formula:
  // FSPL (dB) = 20×log₁₀(d) + 20×log₁₀(f) + 20×log₁₀(4π/c) - G_TX - G_RX
  //
  // Simplified form:
  // FSPL (dB) = 20×log₁₀(4π/c) + 20×log₁₀(f) + 20×log₁₀(d) - G_TX - G_RX
  //           = -147.55 + 20×log₁₀(f) + 20×log₁₀(d) - G_TX - G_RX

  const double constantTerm = 20.0 * std::log10(4.0 * M_PI / SPEED_OF_LIGHT);

  double fspl = constantTerm + 20.0 * std::log10(freqHz) +
                20.0 * std::log10(distanceM) - gainTX - gainRX;

  return fspl;
}

QString FreeSpaceAttenuationDialog::formatDistance(double distanceM) const {
  if (distanceM >= 1e6) {
    return QString::number(distanceM / 1e6, 'g', 6) + " Mm";
  } else if (distanceM >= 1e3) {
    return QString::number(distanceM / 1e3, 'g', 6) + " km";
  } else if (distanceM >= 1.0) {
    return QString::number(distanceM, 'g', 6) + " m";
  } else if (distanceM >= 1e-2) {
    return QString::number(distanceM / 1e-2, 'g', 6) + " cm";
  } else {
    return QString::number(distanceM / 1e-3, 'g', 6) + " mm";
  }
}

void FreeSpaceAttenuationDialog::computePathLoss() {
  const double eps = 1e-12;

  // Get input values
  double freq = spinFrequency->value();
  QString freqUnits = comboFreqUnits->currentData().toString();

  double distance = spinDistance->value();
  QString distanceUnits = comboDistanceUnits->currentData().toString();

  double gainTX = spinGainTX->value();
  double gainRX = spinGainRX->value();

  // Validate inputs
  if (freq <= eps || distance <= eps) {
    for (int i = 0; i < 5; ++i) {
      resultsTable->item(i, 1)->setText("Error");
      resultsTable->item(i, 1)->setForeground(QBrush(QColor(180, 0, 0)));
      resultsTable->item(i, 1)->setBackground(QBrush(QColor(255, 255, 255)));
      resultsTable->item(i, 1)->setFont(QFont());
    }
    return;
  }

  // Convert to base units
  double freqHz = convertFrequencyToHz(freq, freqUnits);
  double distanceM = convertDistanceToMeters(distance, distanceUnits);

  // Calculate path loss at different distances
  double distances[5] = {distanceM / 4.0, distanceM / 2.0, distanceM,
                         distanceM * 2.0, distanceM * 4.0};

  // Reset colors and fonts to normal
  for (int i = 0; i < 5; ++i) {
    resultsTable->item(i, 1)->setForeground(QBrush(QColor(0, 0, 0)));
    resultsTable->item(i, 1)->setBackground(QBrush(QColor(255, 255, 255)));
    QFont font;
    font.setBold(false);
    resultsTable->item(i, 1)->setFont(font);
  }

  // Update distances
  label_d_4->setText(formatDistance(distances[0])); // distance/4
  label_d_2->setText(formatDistance(distances[1])); // distance/2
  label_d->setText(formatDistance(distances[2]));   // distance
  label_dx2->setText(formatDistance(distances[3])); // distance x2
  label_dx4->setText(formatDistance(distances[4])); // distance x4

  // Calculate and display results
  for (int i = 0; i < 5; ++i) {
    double fspl = calculateFSPL(freqHz, distances[i], gainTX, gainRX);

    // Format: "123.45 dB @ 10 km"
    QString resultText = QString::number(fspl, 'f', 2);
    resultsTable->item(i, 1)->setText(resultText);

    // Highlight the specified distance (row 2)
    if (i == 2) {
      QFont boldFont;
      boldFont.setBold(true);
      resultsTable->item(i, 1)->setFont(boldFont);
      resultsTable->item(i, 1)->setBackground(
          QBrush(QColor(255, 255, 200))); // Light yellow
    }
  }
}

void FreeSpaceAttenuationDialog::on_inputChanged() { computePathLoss(); }
