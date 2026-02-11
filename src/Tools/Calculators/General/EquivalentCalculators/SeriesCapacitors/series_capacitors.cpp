/// @file series_capacitors.cpp
/// @brief Calculator: Equivalent capacitance of series capacitors
/// (implementation)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 29, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "series_capacitors.h"

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

SeriesCapacitorsDialog::SeriesCapacitorsDialog(QWidget *parent)
    : QDialog(parent) {
  setWindowTitle(tr("Equivalent Capacitance of Series Capacitors"));

  // ========== Capacitors Group ==========
  QGroupBox *capacitorsGroup =
      new QGroupBox(QString("Capacitance Values"), this);
  capacitorsGroup->setStyleSheet("QGroupBox { font-weight: bold; }");

  tableCapacitors = new QTableWidget(2, 2, this);
  tableCapacitors->setHorizontalHeaderLabels(QStringList()
                                             << "Capacitor" << "Value");
  tableCapacitors->verticalHeader()->setVisible(false);
  tableCapacitors->setMaximumHeight(300);

  // Add first two rows
  for (int i = 0; i < 2; ++i) {
    QLabel *label = new QLabel(QString("C<sub>%1</sub>").arg(i + 1));
    label->setAlignment(Qt::AlignCenter);
    label->setTextFormat(Qt::RichText);
    tableCapacitors->setCellWidget(i, 0, label);

    QLineEdit *edit = new QLineEdit("1pF", this);
    edit->setAlignment(Qt::AlignCenter);
    tableCapacitors->setCellWidget(i, 1, edit);
    connect(edit, SIGNAL(textChanged(QString)), this, SLOT(computeResults()));
  }

  tableCapacitors->horizontalHeader()->setSectionResizeMode(
      0, QHeaderView::Stretch);
  tableCapacitors->horizontalHeader()->setSectionResizeMode(
      1, QHeaderView::Stretch);

  QPushButton *btnAdd = new QPushButton("+", this);
  QPushButton *btnRemove = new QPushButton("-", this);
  btnAdd->setMaximumWidth(40);
  btnRemove->setMaximumWidth(40);
  connect(btnAdd, SIGNAL(clicked()), this, SLOT(addCapacitor()));
  connect(btnRemove, SIGNAL(clicked()), this, SLOT(removeCapacitor()));

  QHBoxLayout *buttonLayout = new QHBoxLayout;
  buttonLayout->addStretch();
  buttonLayout->addWidget(btnRemove);
  buttonLayout->addWidget(btnAdd);

  QVBoxLayout *capacitorsLayout = new QVBoxLayout;
  capacitorsLayout->addWidget(tableCapacitors);
  capacitorsLayout->addLayout(buttonLayout);
  capacitorsGroup->setLayout(capacitorsLayout);

  // ========== Equivalent Capacitance Display ==========
  QGroupBox *ceqGroup = new QGroupBox(QString("Result"), this);
  ceqGroup->setStyleSheet("QGroupBox { font-weight: bold; }");

  labelCeq = new QLabel("-", this);
  labelCeq->setAlignment(Qt::AlignCenter);

  QVBoxLayout *ceqLayout = new QVBoxLayout;
  ceqLayout->addWidget(labelCeq);
  ceqGroup->setLayout(ceqLayout);

  // ========== Documentation Button ==========
  QPushButton *btnDocs = new QPushButton("See Docs", this);
  connect(btnDocs, &QPushButton::clicked, this,
          &SeriesCapacitorsDialog::showDocumentation);

  // ========== Main Layout ==========
  // Left side - Inputs
  QVBoxLayout *leftLayout = new QVBoxLayout;
  leftLayout->addWidget(capacitorsGroup);
  leftLayout->addStretch();

  // Right side - Outputs
  QVBoxLayout *rightLayout = new QVBoxLayout;
  rightLayout->addWidget(ceqGroup);
  rightLayout->addStretch();

  // Combine left and right
  QHBoxLayout *contentLayout = new QHBoxLayout;
  contentLayout->addLayout(leftLayout);
  contentLayout->addSpacing(15);
  contentLayout->addLayout(rightLayout);
  contentLayout->setStretch(0, 1); // Left side
  contentLayout->setStretch(2, 1); // Right side

  QVBoxLayout *main = new QVBoxLayout;
  main->addLayout(contentLayout);
  main->setSpacing(8);
  main->setContentsMargins(15, 15, 15, 15);
  main->addSpacing(10);
  main->addWidget(btnDocs);

  setLayout(main);
  setMinimumWidth(600);
  setMinimumHeight(400);

  // Compute initial values
  computeResults();
}

double SeriesCapacitorsDialog::parseCapacitance(const QString &valueStr) const {
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
  if (str.contains('p')) {
    unitIndex = str.indexOf('p');
    multiplier = 1e-12;
    prefix = str.left(unitIndex);
    suffix = str.mid(unitIndex + 1);
  } else if (str.contains('n')) {
    unitIndex = str.indexOf('n');
    multiplier = 1e-9;
    prefix = str.left(unitIndex);
    suffix = str.mid(unitIndex + 1);
  } else if (str.contains('u')) {
    unitIndex = str.indexOf('u');
    multiplier = 1e-6;
    prefix = str.left(unitIndex);
    suffix = str.mid(unitIndex + 1);
  } else if (str.contains('m') && !str.contains("meg")) {
    unitIndex = str.indexOf('m');
    multiplier = 1e-3;
    prefix = str.left(unitIndex);
    suffix = str.mid(unitIndex + 1);
  } else if (str.contains('f')) {
    // Just 'f' or 'fF' - remove 'f' and treat as plain number
    unitIndex = str.indexOf('f');
    prefix = str.left(unitIndex);
    suffix = str.mid(unitIndex + 1);
  }

  // Remove 'f' from suffix (for 'pF', 'nF', etc.)
  suffix.remove('f');
  suffix.remove('F');

  // Remove any non-numeric characters except decimal point
  prefix.remove(QRegularExpression("[^0-9.]"));
  suffix.remove(QRegularExpression("[^0-9.]"));

  if (unitIndex >= 0 && multiplier != 1.0) {
    // Format like "2p2" or "0p5" - combine prefix and suffix with multiplier
    bool okPrefix, okSuffix;
    double prefixValue = prefix.isEmpty() ? 0.0 : prefix.toDouble(&okPrefix);
    double suffixValue = 0.0;

    if (!suffix.isEmpty()) {
      suffixValue = suffix.toDouble(&okSuffix);
      if (!okSuffix)
        return 0.0;

      // Calculate the decimal places for suffix
      // "2p2" -> 2e-12 + 2e-13 = 2.2e-12
      // "0p5" -> 0 + 5e-13 = 0.5e-12
      int suffixDigits = suffix.length();
      double suffixMultiplier = multiplier / std::pow(10.0, suffixDigits);
      return prefixValue * multiplier + suffixValue * suffixMultiplier;
    } else {
      // Format like "22p" - just multiply
      if (prefix.isEmpty() || !okPrefix)
        return 0.0;
      return prefixValue * multiplier;
    }
  } else {
    // No unit prefix, just a plain number (treat as farads)
    str.remove(QRegularExpression("[^0-9.]"));
    bool ok;
    double value = str.toDouble(&ok);
    if (!ok)
      return 0.0;
    return value;
  }
}

QString SeriesCapacitorsDialog::formatCapacitance(double value) const {
  if (value >= 1.0) {
    return QString::number(value, 'g', 4) + " F";
  } else if (value >= 1e-3) {
    return QString::number(value * 1e3, 'g', 4) + " mF";
  } else if (value >= 1e-6) {
    return QString::number(value * 1e6, 'g', 4) + " μF";
  } else if (value >= 1e-9) {
    return QString::number(value * 1e9, 'g', 4) + " nF";
  } else if (value >= 1e-12) {
    return QString::number(value * 1e12, 'g', 4) + " pF";
  } else {
    return QString::number(value * 1e15, 'g', 4) + " fF";
  }
}

QVector<double> SeriesCapacitorsDialog::getCapacitors() const {
  QVector<double> capacitors;
  for (int i = 0; i < tableCapacitors->rowCount(); ++i) {
    QLineEdit *edit =
        qobject_cast<QLineEdit *>(tableCapacitors->cellWidget(i, 1));
    if (edit) {
      double value = parseCapacitance(edit->text());
      if (value > 0) {
        capacitors.append(value);
      }
    }
  }
  return capacitors;
}

double SeriesCapacitorsDialog::calculateSeriesCapacitance(
    const QVector<double> &capacitors) const {
  if (capacitors.isEmpty())
    return 0.0;

  double invSum = 0.0;
  for (double c : capacitors) {
    if (c > 0) {
      invSum += 1.0 / c;
    }
  }

  if (invSum > 0) {
    return 1.0 / invSum;
  }
  return 0.0;
}

void SeriesCapacitorsDialog::addCapacitor() {
  int row = tableCapacitors->rowCount();
  tableCapacitors->insertRow(row);

  QLabel *label = new QLabel(QString("C<sub>%1</sub>").arg(row + 1));
  label->setAlignment(Qt::AlignCenter);
  label->setTextFormat(Qt::RichText);
  tableCapacitors->setCellWidget(row, 0, label);

  QLineEdit *edit = new QLineEdit("1pF", this);
  edit->setAlignment(Qt::AlignCenter);
  tableCapacitors->setCellWidget(row, 1, edit);
  connect(edit, SIGNAL(textChanged(QString)), this, SLOT(computeResults()));

  computeResults();
}

void SeriesCapacitorsDialog::removeCapacitor() {
  if (tableCapacitors->rowCount() > 1) {
    tableCapacitors->removeRow(tableCapacitors->rowCount() - 1);
    computeResults();
  }
}

void SeriesCapacitorsDialog::computeResults() {
  QVector<double> capacitors = getCapacitors();

  if (capacitors.isEmpty()) {
    labelCeq->setText("Error: No valid capacitors");
    return;
  }

  // Calculate equivalent capacitance
  double ceq = calculateSeriesCapacitance(capacitors);

  if (ceq <= 0) {
    labelCeq->setText("Error: Invalid capacitors");
    return;
  }

  // Display equivalent capacitance
  labelCeq->setText(
      QString("<b>C<sub>eq</sub> = %1</b>").arg(formatCapacitance(ceq)));
}

void SeriesCapacitorsDialog::on_inputChanged() { computeResults(); }
