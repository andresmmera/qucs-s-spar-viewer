/// @file CustomDoubleSpinBox.cpp
/// @brief Custom QDoubleSpinBox. It includes a context menu (right-click) for
/// setting the minimum, maximum and step values (implementation)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 24, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "CustomDoubleSpinBox.h"

void CustomDoubleSpinBox::contextMenuEvent(QContextMenuEvent *event) {
  QMenu menu(this);

  QAction *configAction = menu.addAction("Configure Range && Step...");

  QAction *selectedAction = menu.exec(event->globalPos());

  if (selectedAction == configAction) {
    openConfigDialog();
  }
}

void CustomDoubleSpinBox::openConfigDialog() {
  QDialog dialog(this);
  dialog.setWindowTitle("Configure SpinBox");

  QVBoxLayout *mainLayout = new QVBoxLayout(&dialog);
  QFormLayout *formLayout = new QFormLayout();

  // Create spinboxes for configuration
  QDoubleSpinBox *minSpinBox = new QDoubleSpinBox(&dialog);
  minSpinBox->setRange(-1e9, 1e9);
  minSpinBox->setDecimals(decimals());
  minSpinBox->setValue(minimum());

  QDoubleSpinBox *maxSpinBox = new QDoubleSpinBox(&dialog);
  maxSpinBox->setRange(-1e9, 1e9);
  maxSpinBox->setDecimals(decimals());
  maxSpinBox->setValue(maximum());

  QDoubleSpinBox *stepSpinBox = new QDoubleSpinBox(&dialog);
  stepSpinBox->setRange(0.0001, 1000.0);
  stepSpinBox->setDecimals(4);
  stepSpinBox->setValue(singleStep());

  formLayout->addRow("Minimum:", minSpinBox);
  formLayout->addRow("Maximum:", maxSpinBox);
  formLayout->addRow("Step:", stepSpinBox);

  mainLayout->addLayout(formLayout);

  // Add OK/Cancel buttons
  QDialogButtonBox *buttonBox = new QDialogButtonBox(
      QDialogButtonBox::Ok | QDialogButtonBox::Cancel, &dialog);

  connect(buttonBox, &QDialogButtonBox::accepted, &dialog, &QDialog::accept);
  connect(buttonBox, &QDialogButtonBox::rejected, &dialog, &QDialog::reject);

  mainLayout->addWidget(buttonBox);

  // Set minimum dialog size and adjust to content
  dialog.setMinimumWidth(300);
  dialog.adjustSize();

  // Execute dialog and apply changes if accepted
  if (dialog.exec() == QDialog::Accepted) {
    double newMin = minSpinBox->value();
    double newMax = maxSpinBox->value();
    double newStep = stepSpinBox->value();

    // Validate that min < max
    if (newMin < newMax) {
      setRange(newMin, newMax);
      setSingleStep(newStep);
    }
  }
}
