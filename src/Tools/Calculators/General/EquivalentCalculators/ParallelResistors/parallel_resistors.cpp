/// @file parallel_resistors.cpp
/// @brief Calculator: Equivalent resistance of parallel resistors
/// (implementation)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 30, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "parallel_resistors.h"

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

ParallelResistorsDialog::ParallelResistorsDialog(QWidget *parent)
    : QDialog(parent) {
  setWindowTitle(tr("Equivalent Resistance of Parallel Resistors"));

  // ========== Settings Group ==========
  QGroupBox *settingsGroup = new QGroupBox(QString("Settings"), this);
  settingsGroup->setStyleSheet("QGroupBox { font-weight: bold; }");

  spinDeltaV = new CustomDoubleSpinBox(this);
  spinDeltaV->setRange(0.0, 1000.0);
  spinDeltaV->setDecimals(1);
  spinDeltaV->setSingleStep(0.1);
  spinDeltaV->setValue(5.0);
  spinDeltaV->setSuffix(" V");

  spinPmax = new CustomDoubleSpinBox(this);
  spinPmax->setRange(0.0, 10000.0);
  spinPmax->setDecimals(1);
  spinPmax->setSingleStep(1.0);
  spinPmax->setValue(50.0); // 50 mW
  spinPmax->setSuffix(" mW");

  QFormLayout *settingsLayout = new QFormLayout;
  settingsLayout->addRow(QString("<b>ΔV (Voltage):</b>"), spinDeltaV);
  settingsLayout->addRow(
      QString("<b>P<sub>max</sub> (Max Power/Resistor):</b>"), spinPmax);
  settingsLayout->setLabelAlignment(Qt::AlignRight);
  settingsLayout->setSpacing(12);
  settingsGroup->setLayout(settingsLayout);

  // ========== Resistors Group ==========
  QGroupBox *resistorsGroup = new QGroupBox(QString("Resistor Values"), this);
  resistorsGroup->setStyleSheet("QGroupBox { font-weight: bold; }");

  tableResistors = new QTableWidget(2, 2, this);
  tableResistors->setHorizontalHeaderLabels(QStringList()
                                            << "Resistor" << "Value");
  tableResistors->verticalHeader()->setVisible(false);
  tableResistors->setMaximumHeight(200);

  // Add first two rows
  for (int i = 0; i < 2; ++i) {
    QLabel *label = new QLabel(QString("R<sub>%1</sub>").arg(i + 1));
    label->setAlignment(Qt::AlignCenter);
    label->setTextFormat(Qt::RichText);
    tableResistors->setCellWidget(i, 0, label);

    QLineEdit *edit = new QLineEdit("1k", this);
    edit->setAlignment(Qt::AlignCenter);
    tableResistors->setCellWidget(i, 1, edit);
    connect(edit, SIGNAL(textChanged(QString)), this, SLOT(computeResults()));
  }

  tableResistors->horizontalHeader()->setSectionResizeMode(
      0, QHeaderView::Stretch);
  tableResistors->horizontalHeader()->setSectionResizeMode(
      1, QHeaderView::Stretch);

  QPushButton *btnAdd = new QPushButton("+", this);
  QPushButton *btnRemove = new QPushButton("-", this);
  btnAdd->setMaximumWidth(40);
  btnRemove->setMaximumWidth(40);
  connect(btnAdd, SIGNAL(clicked()), this, SLOT(addResistor()));
  connect(btnRemove, SIGNAL(clicked()), this, SLOT(removeResistor()));

  QHBoxLayout *buttonLayout = new QHBoxLayout;
  buttonLayout->addStretch();
  buttonLayout->addWidget(btnRemove);
  buttonLayout->addWidget(btnAdd);

  QVBoxLayout *resistorsLayout = new QVBoxLayout;
  resistorsLayout->addWidget(tableResistors);
  resistorsLayout->addLayout(buttonLayout);
  resistorsGroup->setLayout(resistorsLayout);

  // ========== Equivalent Resistance Display ==========
  QGroupBox *reqGroup = new QGroupBox(QString("Result"), this);
  reqGroup->setStyleSheet("QGroupBox { font-weight: bold; }");

  labelReq = new QLabel("-", this);
  labelReq->setAlignment(Qt::AlignCenter);
  labelReq->setStyleSheet("QLabel { "
                          "  font-size: 18px; "
                          "  font-weight: bold; "
                          "  padding: 15px; "
                          "  border: 2px solid #c0c0c0; "
                          "  border-radius: 4px; "
                          "  background-color: white; "
                          "  min-height: 40px; "
                          "}");

  QVBoxLayout *reqLayout = new QVBoxLayout;
  reqLayout->addWidget(labelReq);
  reqGroup->setLayout(reqLayout);

  // ========== Results Table ==========
  QGroupBox *resultsGroup =
      new QGroupBox(QString("Current and Power Dissipation"), this);
  resultsGroup->setStyleSheet("QGroupBox { font-weight: bold; }");

  resultsTable = new QTableWidget(0, 3, this);
  resultsTable->setHorizontalHeaderLabels(
      QStringList() << "Resistor" << "Current" << "Power Dissipation");
  resultsTable->verticalHeader()->setVisible(false);
  resultsTable->setMinimumHeight(200);

  // Table settings
  resultsTable->setAlternatingRowColors(true);
  resultsTable->horizontalHeader()->setSectionResizeMode(0,
                                                         QHeaderView::Stretch);
  resultsTable->horizontalHeader()->setSectionResizeMode(1,
                                                         QHeaderView::Stretch);
  resultsTable->horizontalHeader()->setSectionResizeMode(2,
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

  // ========== Documentation Button ==========
  QPushButton *btnDocs = new QPushButton("See Docs", this);
  connect(btnDocs, &QPushButton::clicked, this,
          &ParallelResistorsDialog::showDocumentation);

  QVBoxLayout *resultsLayout = new QVBoxLayout;
  resultsLayout->addWidget(resultsTable);
  resultsGroup->setLayout(resultsLayout);

  // ========== Main Layout ==========
  // Left side - Inputs
  QVBoxLayout *leftLayout = new QVBoxLayout;
  leftLayout->addWidget(settingsGroup);
  leftLayout->addSpacing(10);
  leftLayout->addWidget(resistorsGroup);
  leftLayout->addStretch();

  // Right side - Outputs
  QVBoxLayout *rightLayout = new QVBoxLayout;
  rightLayout->addWidget(reqGroup);
  rightLayout->addSpacing(10);
  rightLayout->addWidget(resultsGroup);

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
  main->addSpacing(10);
  main->addWidget(btnDocs);

  setLayout(main);
  setMinimumWidth(800);
  setMinimumHeight(500);

  // ========== Connect Signals ==========
  connect(spinDeltaV, SIGNAL(valueChanged(double)), this,
          SLOT(computeResults()));
  connect(spinDeltaV, SIGNAL(editingFinished()), this, SLOT(computeResults()));
  connect(spinPmax, SIGNAL(valueChanged(double)), this, SLOT(computeResults()));
  connect(spinPmax, SIGNAL(editingFinished()), this, SLOT(computeResults()));

  // Compute initial values
  computeResults();
}

double ParallelResistorsDialog::parseResistance(const QString &valueStr) const {
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

QString ParallelResistorsDialog::formatResistance(double value) const {
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

QString ParallelResistorsDialog::formatCurrent(double value) const {
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

QString ParallelResistorsDialog::formatPower(double value) const {
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

QVector<double> ParallelResistorsDialog::getResistors() const {
  QVector<double> resistors;
  for (int i = 0; i < tableResistors->rowCount(); ++i) {
    QLineEdit *edit =
        qobject_cast<QLineEdit *>(tableResistors->cellWidget(i, 1));
    if (edit) {
      double value = parseResistance(edit->text());
      if (value > 0) {
        resistors.append(value);
      }
    }
  }
  return resistors;
}

double ParallelResistorsDialog::calculateParallelResistance(
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

void ParallelResistorsDialog::addResistor() {
  int row = tableResistors->rowCount();
  tableResistors->insertRow(row);

  QLabel *label = new QLabel(QString("R<sub>%1</sub>").arg(row + 1));
  label->setAlignment(Qt::AlignCenter);
  label->setTextFormat(Qt::RichText);
  tableResistors->setCellWidget(row, 0, label);

  QLineEdit *edit = new QLineEdit("1k", this);
  edit->setAlignment(Qt::AlignCenter);
  tableResistors->setCellWidget(row, 1, edit);
  connect(edit, SIGNAL(textChanged(QString)), this, SLOT(computeResults()));

  computeResults();
}

void ParallelResistorsDialog::removeResistor() {
  if (tableResistors->rowCount() > 1) {
    tableResistors->removeRow(tableResistors->rowCount() - 1);
    computeResults();
  }
}

void ParallelResistorsDialog::computeResults() {
  double deltaV = spinDeltaV->value();
  double pmax = spinPmax->value() / 1000.0; // Convert mW to W

  QVector<double> resistors = getResistors();

  if (resistors.isEmpty()) {
    labelReq->setText("Error: No valid resistors");
    return;
  }

  // Calculate equivalent resistance
  double req = calculateParallelResistance(resistors);

  if (req <= 0) {
    labelReq->setText("Error: Invalid resistors");
    return;
  }

  // Display equivalent resistance
  labelReq->setText(
      QString("<b>R<sub>eq</sub> = %1</b>").arg(formatResistance(req)));

  // Clear results table
  resultsTable->setRowCount(0);

  double totalCurrent = 0.0;
  double totalPower = 0.0;

  // Calculate current and power for each resistor
  for (int i = 0; i < resistors.size(); ++i) {
    double r = resistors[i];
    double current = deltaV / r;
    double power = current * current * r;

    int row = resultsTable->rowCount();
    resultsTable->insertRow(row);

    QTableWidgetItem *itemName =
        new QTableWidgetItem(QString("R%1").arg(i + 1));
    QTableWidgetItem *itemCurrent =
        new QTableWidgetItem(formatCurrent(current));
    QTableWidgetItem *itemPower = new QTableWidgetItem(formatPower(power));

    itemName->setTextAlignment(Qt::AlignCenter);
    itemCurrent->setTextAlignment(Qt::AlignCenter);
    itemPower->setTextAlignment(Qt::AlignCenter);

    // Highlight if exceeds max power
    if (power > pmax) {
      itemPower->setBackground(QBrush(QColor(255, 255, 0))); // Yellow
      itemPower->setForeground(QBrush(QColor(255, 0, 0)));   // Red text
    }

    resultsTable->setItem(row, 0, itemName);
    resultsTable->setItem(row, 1, itemCurrent);
    resultsTable->setItem(row, 2, itemPower);

    totalCurrent += current;
    totalPower += power;
  }

  // Add total row
  int row = resultsTable->rowCount();
  resultsTable->insertRow(row);

  QTableWidgetItem *itemName = new QTableWidgetItem("Total");
  QTableWidgetItem *itemCurrent =
      new QTableWidgetItem(formatCurrent(totalCurrent));
  QTableWidgetItem *itemPower = new QTableWidgetItem(formatPower(totalPower));

  QFont boldFont;
  boldFont.setBold(true);
  itemName->setFont(boldFont);
  itemCurrent->setFont(boldFont);
  itemPower->setFont(boldFont);

  itemName->setTextAlignment(Qt::AlignCenter);
  itemCurrent->setTextAlignment(Qt::AlignCenter);
  itemPower->setTextAlignment(Qt::AlignCenter);

  resultsTable->setItem(row, 0, itemName);
  resultsTable->setItem(row, 1, itemCurrent);
  resultsTable->setItem(row, 2, itemPower);
}

void ParallelResistorsDialog::on_inputChanged() { computeResults(); }
