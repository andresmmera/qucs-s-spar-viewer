/// @file voltage_divider.cpp
/// @brief Calculator: Voltage divider design with power dissipation analysis
/// (implementation)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 29, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "voltage_divider.h"

#include <QComboBox>
#include <QFormLayout>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRegularExpression>
#include <QTableWidget>
#include <QVBoxLayout>
#include <cmath>

VoltageDividerDialog::VoltageDividerDialog(QWidget *parent) : QDialog(parent) {
  setWindowTitle(tr("Voltage Divider Design"));

  // ========== Settings Group ==========
  QGroupBox *settingsGroup = new QGroupBox(QString("Settings"), this);
  settingsGroup->setStyleSheet("QGroupBox { font-weight: bold; }");

  spinVdc = new CustomDoubleSpinBox(this);
  spinVdc->setRange(0.0, 1000.0);
  spinVdc->setDecimals(2);
  spinVdc->setSingleStep(0.1);
  spinVdc->setValue(5.0);
  spinVdc->setSuffix(" V");

  spinPmax = new CustomDoubleSpinBox(this);
  spinPmax->setRange(0.0, 10000.0);
  spinPmax->setDecimals(2);
  spinPmax->setSingleStep(1.0);
  spinPmax->setValue(50.0); // 50 mW
  spinPmax->setSuffix(" mW");

  QFormLayout *settingsLayout = new QFormLayout;
  settingsLayout->addRow(QString("<b>V<sub>DC</sub> (Voltage):</b>"), spinVdc);
  settingsLayout->addRow(
      QString("<b>P<sub>max</sub> (Max Power/Resistor):</b>"), spinPmax);
  settingsLayout->setLabelAlignment(Qt::AlignRight);
  settingsLayout->setSpacing(12);
  settingsGroup->setLayout(settingsLayout);

  // ========== Image Display ==========
  QLabel *imageLabel = new QLabel(this);
  imageLabel->setAlignment(Qt::AlignCenter);
  imageLabel->setMaximumSize(200, 230);
  imageLabel->setScaledContents(true);
  imageLabel->setStyleSheet("QLabel { "
                            "  border: 2px solid #c0c0c0; "
                            "  border-radius: 4px; "
                            "  background-color: white; "
                            "  padding: 10px; "
                            "}");

  // Try to load the image - adjust the path as needed
  QPixmap pixmap(
      ":/Tools/Calculators/General/VoltageDivider/VoltageDivider.png");
  if (pixmap.isNull()) {
    // If image not found, show placeholder text
    imageLabel->setWordWrap(true);
  } else {
    imageLabel->setPixmap(pixmap);
  }

  // ========== Upper Resistors Group ==========
  QGroupBox *upperGroup =
      new QGroupBox(QString("Upper Resistors (Parallel)"), this);
  upperGroup->setStyleSheet("QGroupBox { font-weight: bold; }");

  tableUpper = new QTableWidget(1, 2, this);
  tableUpper->setHorizontalHeaderLabels(QStringList() << "Resistor" << "Value");
  tableUpper->verticalHeader()->setVisible(false);
  tableUpper->setMaximumHeight(150);

  // Add first row
  QLabel *labelUpper1 = new QLabel("R<sub>Upper 1</sub>");
  labelUpper1->setAlignment(Qt::AlignCenter);
  labelUpper1->setTextFormat(Qt::RichText);
  tableUpper->setCellWidget(0, 0, labelUpper1);

  QLineEdit *editUpper1 = new QLineEdit("1k", this);
  editUpper1->setAlignment(Qt::AlignCenter);
  tableUpper->setCellWidget(0, 1, editUpper1);
  connect(editUpper1, SIGNAL(textChanged(QString)), this,
          SLOT(computeResults()));

  tableUpper->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
  tableUpper->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

  QPushButton *btnAddUpper = new QPushButton("+", this);
  QPushButton *btnRemoveUpper = new QPushButton("-", this);
  btnAddUpper->setMaximumWidth(40);
  btnRemoveUpper->setMaximumWidth(40);
  connect(btnAddUpper, SIGNAL(clicked()), this, SLOT(addUpperResistor()));
  connect(btnRemoveUpper, SIGNAL(clicked()), this, SLOT(removeUpperResistor()));

  QHBoxLayout *upperButtonLayout = new QHBoxLayout;
  upperButtonLayout->addStretch();
  upperButtonLayout->addWidget(btnRemoveUpper);
  upperButtonLayout->addWidget(btnAddUpper);

  QVBoxLayout *upperLayout = new QVBoxLayout;
  upperLayout->addWidget(tableUpper);
  upperLayout->addLayout(upperButtonLayout);
  upperGroup->setLayout(upperLayout);

  // ========== Lower Resistors Group ==========
  QGroupBox *lowerGroup =
      new QGroupBox(QString("Lower Resistors (Parallel)"), this);
  lowerGroup->setStyleSheet("QGroupBox { font-weight: bold; }");

  tableLower = new QTableWidget(1, 2, this);
  tableLower->setHorizontalHeaderLabels(QStringList() << "Resistor" << "Value");
  tableLower->verticalHeader()->setVisible(false);
  tableLower->setMaximumHeight(150);

  // Add first row
  QLabel *labelLower1 = new QLabel("R<sub>Lower 1</sub>");
  labelLower1->setAlignment(Qt::AlignCenter);
  labelLower1->setTextFormat(Qt::RichText);
  tableLower->setCellWidget(0, 0, labelLower1);

  QLineEdit *editLower1 = new QLineEdit("1k", this);
  editLower1->setAlignment(Qt::AlignCenter);
  tableLower->setCellWidget(0, 1, editLower1);
  connect(editLower1, SIGNAL(textChanged(QString)), this,
          SLOT(computeResults()));

  tableLower->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
  tableLower->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

  QPushButton *btnAddLower = new QPushButton("+", this);
  QPushButton *btnRemoveLower = new QPushButton("-", this);
  btnAddLower->setMaximumWidth(40);
  btnRemoveLower->setMaximumWidth(40);
  connect(btnAddLower, SIGNAL(clicked()), this, SLOT(addLowerResistor()));
  connect(btnRemoveLower, SIGNAL(clicked()), this, SLOT(removeLowerResistor()));

  QHBoxLayout *lowerButtonLayout = new QHBoxLayout;
  lowerButtonLayout->addStretch();
  lowerButtonLayout->addWidget(btnRemoveLower);
  lowerButtonLayout->addWidget(btnAddLower);

  QVBoxLayout *lowerLayout = new QVBoxLayout;
  lowerLayout->addWidget(tableLower);
  lowerLayout->addLayout(lowerButtonLayout);
  lowerGroup->setLayout(lowerLayout);

  // ========== Output Voltage Display ==========
  QGroupBox *voutGroup = new QGroupBox(QString("Output Voltage"), this);
  voutGroup->setStyleSheet("QGroupBox { font-weight: bold; }");

  labelVout = new QLabel("-", this);
  labelVout->setAlignment(Qt::AlignCenter);
  labelVout->setStyleSheet("QLabel { "
                           "  font-size: 18px; "
                           "  font-weight: bold; "
                           "  padding: 15px; "
                           "  border: 2px solid #c0c0c0; "
                           "  border-radius: 4px; "
                           "  background-color: white; "
                           "  min-height: 40px; "
                           "}");

  QVBoxLayout *voutLayout = new QVBoxLayout;
  voutLayout->addWidget(labelVout);
  voutGroup->setLayout(voutLayout);

  // ========== Results Table ==========
  QGroupBox *resultsGroup =
      new QGroupBox(QString("Current and Power Dissipation"), this);
  resultsGroup->setStyleSheet("QGroupBox { font-weight: bold; }");

  resultsTable = new QTableWidget(0, 4, this);
  resultsTable->setHorizontalHeaderLabels(
      QStringList() << "Resistor" << "Value" << "Current" << "Dissipation");
  resultsTable->verticalHeader()->setVisible(false);
  resultsTable->setMinimumHeight(250);

  // Table settings
  resultsTable->setAlternatingRowColors(true);
  resultsTable->horizontalHeader()->setSectionResizeMode(0,
                                                         QHeaderView::Stretch);
  resultsTable->horizontalHeader()->setSectionResizeMode(1,
                                                         QHeaderView::Stretch);
  resultsTable->horizontalHeader()->setSectionResizeMode(2,
                                                         QHeaderView::Stretch);
  resultsTable->horizontalHeader()->setSectionResizeMode(3,
                                                         QHeaderView::Stretch);
  resultsTable->setSelectionMode(QAbstractItemView::SingleSelection);
  resultsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

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

  // ========== Documentation Button ==========
  QPushButton *btnDocs = new QPushButton("See Docs", this);
  connect(btnDocs, &QPushButton::clicked, this,
          &VoltageDividerDialog::showDocumentation);

  // ========== Main Layout ==========
  // Left side - Inputs
  QVBoxLayout *leftLayout = new QVBoxLayout;
  leftLayout->addWidget(settingsGroup);
  leftLayout->addSpacing(10);
  leftLayout->addWidget(upperGroup);
  leftLayout->addSpacing(10);
  leftLayout->addWidget(lowerGroup);
  leftLayout->addStretch();

  // Right side - Image and Outputs
  QVBoxLayout *rightLayout = new QVBoxLayout;
  rightLayout->addWidget(imageLabel);
  rightLayout->addSpacing(10);
  rightLayout->addWidget(voutGroup);
  rightLayout->addSpacing(10);
  rightLayout->addWidget(resultsGroup);
  rightLayout->addSpacing(10);
  rightLayout->addWidget(btnDocs);

  // Combine left and right
  QHBoxLayout *contentLayout = new QHBoxLayout;
  contentLayout->addLayout(leftLayout);
  contentLayout->addSpacing(15);
  contentLayout->addLayout(rightLayout);
  contentLayout->setStretch(0, 1); // Left side
  contentLayout->setStretch(2, 2); // Right side gets more space

  QVBoxLayout *main = new QVBoxLayout;
  main->addLayout(contentLayout);
  main->setSpacing(8);
  main->setContentsMargins(15, 15, 15, 15);

  setLayout(main);
  setMinimumWidth(900);
  setMinimumHeight(650);

  // ========== Connect Signals ==========
  connect(spinVdc, SIGNAL(valueChanged(double)), this, SLOT(computeResults()));
  connect(spinVdc, SIGNAL(editingFinished()), this, SLOT(computeResults()));
  connect(spinPmax, SIGNAL(valueChanged(double)), this, SLOT(computeResults()));
  connect(spinPmax, SIGNAL(editingFinished()), this, SLOT(computeResults()));

  // Compute initial values
  computeResults();
}

double VoltageDividerDialog::parseResistance(const QString &valueStr) const {
  QString str = valueStr.trimmed().toLower();

  if (str.isEmpty())
    return 0.0;

  // Remove spaces
  str.remove(' ');

  double multiplier = 1.0;
  int unitIndex = -1;
  QString prefix = "";
  QString suffix = "";

  // Check for unit prefixes and split around them
  if (str.contains('k')) {
    unitIndex = str.indexOf('k');
    multiplier = 1e3;
    prefix = str.left(unitIndex);
    suffix = str.mid(unitIndex + 1);
  } else if (str.contains("meg")) {
    unitIndex = str.indexOf("meg");
    multiplier = 1e6;
    prefix = str.left(unitIndex);
    suffix = str.mid(unitIndex + 3);
  } else if (str.contains('m') && !str.contains("meg")) {
    unitIndex = str.indexOf('m');
    multiplier = 1e-3;
    prefix = str.left(unitIndex);
    suffix = str.mid(unitIndex + 1);
  } else if (str.contains('g')) {
    unitIndex = str.indexOf('g');
    multiplier = 1e9;
    prefix = str.left(unitIndex);
    suffix = str.mid(unitIndex + 1);
  }

  // Remove any non-numeric characters except decimal point
  prefix.remove(QRegularExpression("[^0-9.]"));
  suffix.remove(QRegularExpression("[^0-9.]"));

  if (unitIndex >= 0) {
    // Format like "2k2" or "0k5" - combine prefix and suffix with multiplier
    bool okPrefix, okSuffix;
    double prefixValue = prefix.isEmpty() ? 0.0 : prefix.toDouble(&okPrefix);
    double suffixValue = 0.0;

    if (!suffix.isEmpty()) {
      suffixValue = suffix.toDouble(&okSuffix);
      if (!okSuffix)
        return 0.0;

      // Calculate the decimal places for suffix
      // "2k2" -> 2000 + 200 = 2200
      // "0k5" -> 0 + 500 = 500
      int suffixDigits = suffix.length();
      double suffixMultiplier = multiplier / std::pow(10.0, suffixDigits);
      return prefixValue * multiplier + suffixValue * suffixMultiplier;
    } else {
      // Format like "22k" - just multiply
      if (prefix.isEmpty() || !okPrefix)
        return 0.0;
      return prefixValue * multiplier;
    }
  } else {
    // No unit prefix, just a plain number
    str.remove(QRegularExpression("[^0-9.]"));
    bool ok;
    double value = str.toDouble(&ok);
    if (!ok)
      return 0.0;
    return value;
  }
}

QString VoltageDividerDialog::formatResistance(double value) const {
  if (value >= 1e9) {
    return QString::number(value / 1e9, 'g', 4) + " GΩ";
  } else if (value >= 1e6) {
    return QString::number(value / 1e6, 'g', 4) + " MΩ";
  } else if (value >= 1e3) {
    return QString::number(value / 1e3, 'g', 4) + " kΩ";
  } else {
    return QString::number(value, 'g', 4) + " Ω";
  }
}

QString VoltageDividerDialog::formatCurrent(double value) const {
  if (value >= 1.0) {
    return QString::number(value, 'g', 4) + " A";
  } else if (value >= 1e-3) {
    return QString::number(value * 1e3, 'g', 4) + " mA";
  } else if (value >= 1e-6) {
    return QString::number(value * 1e6, 'g', 4) + " μA";
  } else if (value >= 1e-9) {
    return QString::number(value * 1e9, 'g', 4) + " nA";
  } else {
    return QString::number(value * 1e12, 'g', 4) + " pA";
  }
}

QString VoltageDividerDialog::formatPower(double value) const {
  if (value >= 1.0) {
    return QString::number(value, 'g', 4) + " W";
  } else if (value >= 1e-3) {
    return QString::number(value * 1e3, 'g', 4) + " mW";
  } else if (value >= 1e-6) {
    return QString::number(value * 1e6, 'g', 4) + " μW";
  } else if (value >= 1e-9) {
    return QString::number(value * 1e9, 'g', 4) + " nW";
  } else {
    return QString::number(value * 1e12, 'g', 4) + " pW";
  }
}

QVector<double> VoltageDividerDialog::getUpperResistors() const {
  QVector<double> resistors;
  for (int i = 0; i < tableUpper->rowCount(); ++i) {
    QLineEdit *edit = qobject_cast<QLineEdit *>(tableUpper->cellWidget(i, 1));
    if (edit) {
      double value = parseResistance(edit->text());
      if (value > 0) {
        resistors.append(value);
      }
    }
  }
  return resistors;
}

QVector<double> VoltageDividerDialog::getLowerResistors() const {
  QVector<double> resistors;
  for (int i = 0; i < tableLower->rowCount(); ++i) {
    QLineEdit *edit = qobject_cast<QLineEdit *>(tableLower->cellWidget(i, 1));
    if (edit) {
      double value = parseResistance(edit->text());
      if (value > 0) {
        resistors.append(value);
      }
    }
  }
  return resistors;
}

double VoltageDividerDialog::calculateParallelResistance(
    const QVector<double> &resistors) const {
  if (resistors.isEmpty())
    return 0.0;

  double invSum = 0.0;
  for (double r : resistors) {
    if (r > 0) {
      invSum += 1.0 / r;
    }
  }

  if (invSum > 0) {
    return 1.0 / invSum;
  }
  return 0.0;
}

void VoltageDividerDialog::addUpperResistor() {
  int row = tableUpper->rowCount();
  tableUpper->insertRow(row);

  QLabel *label = new QLabel(QString("R<sub>Upper %1</sub>").arg(row + 1));
  label->setAlignment(Qt::AlignCenter);
  label->setTextFormat(Qt::RichText);
  tableUpper->setCellWidget(row, 0, label);

  QLineEdit *edit = new QLineEdit("1k", this);
  edit->setAlignment(Qt::AlignCenter);
  tableUpper->setCellWidget(row, 1, edit);
  connect(edit, SIGNAL(textChanged(QString)), this, SLOT(computeResults()));

  computeResults();
}

void VoltageDividerDialog::removeUpperResistor() {
  if (tableUpper->rowCount() > 1) {
    tableUpper->removeRow(tableUpper->rowCount() - 1);
    computeResults();
  }
}

void VoltageDividerDialog::addLowerResistor() {
  int row = tableLower->rowCount();
  tableLower->insertRow(row);

  QLabel *label = new QLabel(QString("R<sub>Lower %1</sub>").arg(row + 1));
  label->setAlignment(Qt::AlignCenter);
  label->setTextFormat(Qt::RichText);
  tableLower->setCellWidget(row, 0, label);

  QLineEdit *edit = new QLineEdit("1k", this);
  edit->setAlignment(Qt::AlignCenter);
  tableLower->setCellWidget(row, 1, edit);
  connect(edit, SIGNAL(textChanged(QString)), this, SLOT(computeResults()));

  computeResults();
}

void VoltageDividerDialog::removeLowerResistor() {
  if (tableLower->rowCount() > 1) {
    tableLower->removeRow(tableLower->rowCount() - 1);
    computeResults();
  }
}

void VoltageDividerDialog::computeResults() {
  double vdc = spinVdc->value();
  double pmax = spinPmax->value() / 1000.0; // Convert mW to W

  QVector<double> upperResistors = getUpperResistors();
  QVector<double> lowerResistors = getLowerResistors();

  if (upperResistors.isEmpty() || lowerResistors.isEmpty()) {
    labelVout->setText("Error: Invalid resistors");
    return;
  }

  // Calculate equivalent resistances
  double reqUpper = calculateParallelResistance(upperResistors);
  double reqLower = calculateParallelResistance(lowerResistors);

  if (reqUpper <= 0 || reqLower <= 0) {
    labelVout->setText("Error: Invalid resistors");
    return;
  }

  // Calculate output voltage
  double vout = vdc * reqLower / (reqUpper + reqLower);
  labelVout->setText(
      QString("<b>V<sub>out</sub> = %1 V</b>").arg(vout, 0, 'f', 3));

  // Clear results table
  resultsTable->setRowCount(0);

  double totalCurrent = 0.0;
  double totalPower = 0.0;
  double upperPower = 0.0;

  // Calculate upper branch
  for (int i = 0; i < upperResistors.size(); ++i) {
    double r = upperResistors[i];
    double current = (vdc - vout) / r;
    double power = current * current * r;

    int row = resultsTable->rowCount();
    resultsTable->insertRow(row);

    QTableWidgetItem *itemName =
        new QTableWidgetItem(QString("R Upper %1").arg(i + 1));
    QTableWidgetItem *itemValue = new QTableWidgetItem(formatResistance(r));
    QTableWidgetItem *itemCurrent =
        new QTableWidgetItem(formatCurrent(current));
    QTableWidgetItem *itemPower = new QTableWidgetItem(formatPower(power));

    itemName->setTextAlignment(Qt::AlignCenter);
    itemValue->setTextAlignment(Qt::AlignCenter);
    itemCurrent->setTextAlignment(Qt::AlignCenter);
    itemPower->setTextAlignment(Qt::AlignCenter);

    // Highlight if exceeds max power
    if (power > pmax) {
      itemPower->setBackground(QBrush(QColor(255, 255, 0))); // Yellow
      itemPower->setForeground(QBrush(QColor(255, 0, 0)));   // Red text
    }

    resultsTable->setItem(row, 0, itemName);
    resultsTable->setItem(row, 1, itemValue);
    resultsTable->setItem(row, 2, itemCurrent);
    resultsTable->setItem(row, 3, itemPower);

    totalCurrent += current;
    upperPower += power;
    totalPower += power;
  }

  // Add upper branch total
  if (upperResistors.size() > 1) {
    int row = resultsTable->rowCount();
    resultsTable->insertRow(row);

    QTableWidgetItem *itemName = new QTableWidgetItem("Total Upper Branch");
    QTableWidgetItem *itemValue =
        new QTableWidgetItem(formatResistance(reqUpper));
    QTableWidgetItem *itemCurrent = new QTableWidgetItem("");
    QTableWidgetItem *itemPower = new QTableWidgetItem(formatPower(upperPower));

    QFont boldFont;
    boldFont.setBold(true);
    itemName->setFont(boldFont);
    itemValue->setFont(boldFont);
    itemPower->setFont(boldFont);

    itemName->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    itemValue->setTextAlignment(Qt::AlignCenter);
    itemPower->setTextAlignment(Qt::AlignCenter);

    resultsTable->setItem(row, 0, itemName);
    resultsTable->setItem(row, 1, itemValue);
    resultsTable->setItem(row, 2, itemCurrent);
    resultsTable->setItem(row, 3, itemPower);
  }

  double lowerPower = 0.0;

  // Calculate lower branch
  for (int i = 0; i < lowerResistors.size(); ++i) {
    double r = lowerResistors[i];
    double current = vout / r;
    double power = current * current * r;

    int row = resultsTable->rowCount();
    resultsTable->insertRow(row);

    QTableWidgetItem *itemName =
        new QTableWidgetItem(QString("R Lower %1").arg(i + 1));
    QTableWidgetItem *itemValue = new QTableWidgetItem(formatResistance(r));
    QTableWidgetItem *itemCurrent =
        new QTableWidgetItem(formatCurrent(current));
    QTableWidgetItem *itemPower = new QTableWidgetItem(formatPower(power));

    itemName->setTextAlignment(Qt::AlignCenter);
    itemValue->setTextAlignment(Qt::AlignCenter);
    itemCurrent->setTextAlignment(Qt::AlignCenter);
    itemPower->setTextAlignment(Qt::AlignCenter);

    // Highlight if exceeds max power
    if (power > pmax) {
      itemPower->setBackground(QBrush(QColor(255, 255, 0))); // Yellow
      itemPower->setForeground(QBrush(QColor(255, 0, 0)));   // Red text
    }

    resultsTable->setItem(row, 0, itemName);
    resultsTable->setItem(row, 1, itemValue);
    resultsTable->setItem(row, 2, itemCurrent);
    resultsTable->setItem(row, 3, itemPower);

    lowerPower += power;
    totalPower += power;
  }

  // Add lower branch total
  if (lowerResistors.size() > 1) {
    int row = resultsTable->rowCount();
    resultsTable->insertRow(row);

    QTableWidgetItem *itemName = new QTableWidgetItem("Total Lower Branch");
    QTableWidgetItem *itemValue =
        new QTableWidgetItem(formatResistance(reqLower));
    QTableWidgetItem *itemCurrent = new QTableWidgetItem("");
    QTableWidgetItem *itemPower = new QTableWidgetItem(formatPower(lowerPower));

    QFont boldFont;
    boldFont.setBold(true);
    itemName->setFont(boldFont);
    itemValue->setFont(boldFont);
    itemPower->setFont(boldFont);

    itemName->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    itemValue->setTextAlignment(Qt::AlignCenter);
    itemPower->setTextAlignment(Qt::AlignCenter);

    resultsTable->setItem(row, 0, itemName);
    resultsTable->setItem(row, 1, itemValue);
    resultsTable->setItem(row, 2, itemCurrent);
    resultsTable->setItem(row, 3, itemPower);
  }

  // Add grand total
  int row = resultsTable->rowCount();
  resultsTable->insertRow(row);

  QTableWidgetItem *itemName = new QTableWidgetItem("Total");
  QTableWidgetItem *itemValue = new QTableWidgetItem("");
  QTableWidgetItem *itemCurrent =
      new QTableWidgetItem(formatCurrent(totalCurrent));
  QTableWidgetItem *itemPower = new QTableWidgetItem(formatPower(totalPower));

  QFont boldFont;
  boldFont.setBold(true);
  itemName->setFont(boldFont);
  itemCurrent->setFont(boldFont);
  itemPower->setFont(boldFont);

  itemName->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
  itemCurrent->setTextAlignment(Qt::AlignCenter);
  itemPower->setTextAlignment(Qt::AlignCenter);

  resultsTable->setItem(row, 0, itemName);
  resultsTable->setItem(row, 1, itemValue);
  resultsTable->setItem(row, 2, itemCurrent);
  resultsTable->setItem(row, 3, itemPower);
}

void VoltageDividerDialog::on_inputChanged() { computeResults(); }
