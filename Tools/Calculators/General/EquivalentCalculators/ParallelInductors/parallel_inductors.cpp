/// @file parallel_inductors.cpp
/// @brief Calculator: Equivalent inductance of parallel inductors (implementation)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 29, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "parallel_inductors.h"

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

ParallelInductorsDialog::ParallelInductorsDialog(QWidget *parent)
    : QDialog(parent) {
  setWindowTitle(tr("Equivalent Inductance of Parallel Inductors"));

  // ========== Inductors Group ==========
  QGroupBox *inductorsGroup = new QGroupBox(QString("Inductance Values"), this);
  inductorsGroup->setStyleSheet("QGroupBox { font-weight: bold; }");

  tableInductors = new QTableWidget(2, 2, this);
  tableInductors->setHorizontalHeaderLabels(QStringList() << "Inductor" << "Value");
  tableInductors->verticalHeader()->setVisible(false);
  tableInductors->setMaximumHeight(300);

  // Add first two rows
  for (int i = 0; i < 2; ++i) {
    QLabel *label = new QLabel(QString("L<sub>%1</sub>").arg(i + 1));
    label->setAlignment(Qt::AlignCenter);
    label->setTextFormat(Qt::RichText);
    tableInductors->setCellWidget(i, 0, label);

    QLineEdit *edit = new QLineEdit("10nH", this);
    edit->setAlignment(Qt::AlignCenter);
    tableInductors->setCellWidget(i, 1, edit);
    connect(edit, SIGNAL(textChanged(QString)), this, SLOT(computeResults()));
  }

  tableInductors->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
  tableInductors->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

  QPushButton *btnAdd = new QPushButton("+", this);
  QPushButton *btnRemove = new QPushButton("-", this);
  btnAdd->setMaximumWidth(40);
  btnRemove->setMaximumWidth(40);
  connect(btnAdd, SIGNAL(clicked()), this, SLOT(addInductor()));
  connect(btnRemove, SIGNAL(clicked()), this, SLOT(removeInductor()));

  QHBoxLayout *buttonLayout = new QHBoxLayout;
  buttonLayout->addStretch();
  buttonLayout->addWidget(btnRemove);
  buttonLayout->addWidget(btnAdd);

  QVBoxLayout *inductorsLayout = new QVBoxLayout;
  inductorsLayout->addWidget(tableInductors);
  inductorsLayout->addLayout(buttonLayout);
  inductorsGroup->setLayout(inductorsLayout);

  // ========== Equivalent Inductance Display ==========
  QGroupBox *leqGroup = new QGroupBox(QString("Result"), this);
  leqGroup->setStyleSheet("QGroupBox { font-weight: bold; }");

  labelLeq = new QLabel("-", this);
  labelLeq->setAlignment(Qt::AlignCenter);
  labelLeq->setStyleSheet(
      "QLabel { "
      "  font-size: 18px; "
      "  font-weight: bold; "
      "  padding: 15px; "
      "  border: 2px solid #c0c0c0; "
      "  border-radius: 4px; "
      "  background-color: white; "
      "  min-height: 40px; "
      "}");

  QVBoxLayout *leqLayout = new QVBoxLayout;
  leqLayout->addWidget(labelLeq);
  leqGroup->setLayout(leqLayout);

  // ========== Main Layout ==========
  // Left side - Inputs
  QVBoxLayout *leftLayout = new QVBoxLayout;
  leftLayout->addWidget(inductorsGroup);
  leftLayout->addStretch();

  // Right side - Outputs
  QVBoxLayout *rightLayout = new QVBoxLayout;
  rightLayout->addWidget(leqGroup);
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

  setLayout(main);
  setMinimumWidth(600);
  setMinimumHeight(400);

  // Compute initial values
  computeResults();
}

double ParallelInductorsDialog::parseInductance(const QString &valueStr) const {
  QString str = valueStr.trimmed().toLower();
  
  if (str.isEmpty()) return 0.0;

  // Remove spaces
  str.remove(' ');

  double multiplier = 1.0;
  int unitIndex = -1;
  QString prefix = "";
  QString suffix = "";

  // Check for unit prefixes and split around them
  if (str.contains('n')) {
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
  } else if (str.contains("meg")) {
    unitIndex = str.indexOf("meg");
    multiplier = 1e6;
    prefix = str.left(unitIndex);
    suffix = str.mid(unitIndex + 3);
  } else if (str.contains('h')) {
    // Just 'h' or 'H' - remove 'h' and treat as plain number
    unitIndex = str.indexOf('h');
    prefix = str.left(unitIndex);
    suffix = str.mid(unitIndex + 1);
  }

  // Remove 'h' from suffix (for 'uH', 'mH', etc.)
  suffix.remove('h');
  suffix.remove('H');

  // Remove any non-numeric characters except decimal point
  prefix.remove(QRegularExpression("[^0-9.]"));
  suffix.remove(QRegularExpression("[^0-9.]"));

  if (unitIndex >= 0 && multiplier != 1.0) {
    // Format like "2u2" or "0u5" - combine prefix and suffix with multiplier
    bool okPrefix, okSuffix;
    double prefixValue = prefix.isEmpty() ? 0.0 : prefix.toDouble(&okPrefix);
    double suffixValue = 0.0;
    
    if (!suffix.isEmpty()) {
      suffixValue = suffix.toDouble(&okSuffix);
      if (!okSuffix) return 0.0;
      
      // Calculate the decimal places for suffix
      // "2u2" -> 2e-6 + 2e-7 = 2.2e-6
      // "0u5" -> 0 + 5e-7 = 0.5e-6
      int suffixDigits = suffix.length();
      double suffixMultiplier = multiplier / std::pow(10.0, suffixDigits);
      return prefixValue * multiplier + suffixValue * suffixMultiplier;
    } else {
      // Format like "22u" - just multiply
      if (prefix.isEmpty() || !okPrefix) return 0.0;
      return prefixValue * multiplier;
    }
  } else {
    // No unit prefix, just a plain number (treat as henries)
    str.remove(QRegularExpression("[^0-9.]"));
    bool ok;
    double value = str.toDouble(&ok);
    if (!ok) return 0.0;
    return value;
  }
}

QString ParallelInductorsDialog::formatInductance(double value) const {
  if (value >= 1.0) {
    return QString::number(value, 'g', 4) + " H";
  } else if (value >= 1e-3) {
    return QString::number(value * 1e3, 'g', 4) + " mH";
  } else if (value >= 1e-6) {
    return QString::number(value * 1e6, 'g', 4) + " μH";
  } else if (value >= 1e-9) {
    return QString::number(value * 1e9, 'g', 4) + " nH";
  } else {
    return QString::number(value * 1e12, 'g', 4) + " pH";
  }
}

QVector<double> ParallelInductorsDialog::getInductors() const {
  QVector<double> inductors;
  for (int i = 0; i < tableInductors->rowCount(); ++i) {
    QLineEdit *edit = qobject_cast<QLineEdit*>(tableInductors->cellWidget(i, 1));
    if (edit) {
      double value = parseInductance(edit->text());
      if (value > 0) {
        inductors.append(value);
      }
    }
  }
  return inductors;
}

double ParallelInductorsDialog::calculateParallelInductance(const QVector<double> &inductors) const {
  if (inductors.isEmpty()) return 0.0;
  
  double invSum = 0.0;
  for (double l : inductors) {
    if (l > 0) {
      invSum += 1.0 / l;
    }
  }
  
  if (invSum > 0) {
    return 1.0 / invSum;
  }
  return 0.0;
}

void ParallelInductorsDialog::addInductor() {
  int row = tableInductors->rowCount();
  tableInductors->insertRow(row);

  QLabel *label = new QLabel(QString("L<sub>%1</sub>").arg(row + 1));
  label->setAlignment(Qt::AlignCenter);
  label->setTextFormat(Qt::RichText);
  tableInductors->setCellWidget(row, 0, label);

  QLineEdit *edit = new QLineEdit("1uH", this);
  edit->setAlignment(Qt::AlignCenter);
  tableInductors->setCellWidget(row, 1, edit);
  connect(edit, SIGNAL(textChanged(QString)), this, SLOT(computeResults()));

  computeResults();
}

void ParallelInductorsDialog::removeInductor() {
  if (tableInductors->rowCount() > 1) {
    tableInductors->removeRow(tableInductors->rowCount() - 1);
    computeResults();
  }
}

void ParallelInductorsDialog::computeResults() {
  QVector<double> inductors = getInductors();

  if (inductors.isEmpty()) {
    labelLeq->setText("Error: No valid inductors");
    return;
  }

  // Calculate equivalent inductance
  double leq = calculateParallelInductance(inductors);

  if (leq <= 0) {
    labelLeq->setText("Error: Invalid inductors");
    return;
  }

  // Display equivalent inductance
  labelLeq->setText(QString("<b>L<sub>eq</sub> = %1</b>").arg(formatInductance(leq)));
}

void ParallelInductorsDialog::on_inputChanged() {
  computeResults();
}
