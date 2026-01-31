/// @file SecondaryImageCalculatorDialog.cpp
/// @brief Secondary image frequency calculator (implementation)
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 31, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later


#include "SecondaryImageCalculatorDialog.h"
#include <QHeaderView>


SecondaryImageCalculatorDialog::SecondaryImageCalculatorDialog(QWidget *parent)
    : QDialog(parent),
      f_LO1(0.0),
      f_LO2(0.0),
      f_IM1(0.0),
      f_IM2(0.0)
{
    setupUI();
    calculate();
}

void SecondaryImageCalculatorDialog::setupUI()
{
    setWindowTitle("Secondary Image Calculator");
    setMinimumWidth(600);
    setMinimumHeight(400);
    
    QVBoxLayout* mainLayout = new QVBoxLayout(this);
    
    // Title
    QLabel* titleLabel = new QLabel("Secondary Image Calculator");
    QFont titleFont = titleLabel->font();
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    mainLayout->addWidget(titleLabel);
    
    // Input Group
    QGroupBox* inputGroup = new QGroupBox("Parameters");
    QGridLayout* inputLayout = new QGridLayout(inputGroup);
    
    // f_IF1 input
    inputLayout->addWidget(new QLabel("1<sup>st</sup> IF (MHz):"), 0, 0);
    fIF1SpinBox = new QDoubleSpinBox();
    fIF1SpinBox->setDecimals(2);
    fIF1SpinBox->setMinimum(0);
    fIF1SpinBox->setMaximum(999999);
    fIF1SpinBox->setValue(200.0);
    fIF1SpinBox->setSingleStep(1.0);
    inputLayout->addWidget(fIF1SpinBox, 0, 1);
    
    // f_IF2 input
    inputLayout->addWidget(new QLabel("2<sup>nd</sup> IF (MHz):"), 1, 0);
    fIF2SpinBox = new QDoubleSpinBox();
    fIF2SpinBox->setDecimals(2);
    fIF2SpinBox->setMinimum(0);
    fIF2SpinBox->setMaximum(999999);
    fIF2SpinBox->setValue(10.0);
    fIF2SpinBox->setSingleStep(1.0);
    inputLayout->addWidget(fIF2SpinBox, 1, 1);
    
    // f_RF input
    inputLayout->addWidget(new QLabel("RF (MHz):"), 2, 0);
    fRFSpinBox = new QDoubleSpinBox();
    fRFSpinBox->setDecimals(2);
    fRFSpinBox->setMinimum(0);
    fRFSpinBox->setMaximum(999999);
    fRFSpinBox->setValue(800.0);
    fRFSpinBox->setSingleStep(1.0);
    inputLayout->addWidget(fRFSpinBox, 2, 1);
    
    mainLayout->addWidget(inputGroup);
    
    // Results Group
    QGroupBox* resultsGroup = new QGroupBox("Results");
    QVBoxLayout* resultsLayout = new QVBoxLayout(resultsGroup);
    
    // Create results table
    resultsTable = new QTableWidget(2, 4);
    resultsTable->setHorizontalHeaderLabels(QStringList() << "Step" << "Downconversion" << "LO" << "Image");
    resultsTable->verticalHeader()->setVisible(false);
    
    // Set column widths
    resultsTable->setColumnWidth(0, 60);
    resultsTable->setColumnWidth(1, 200);
    resultsTable->setColumnWidth(2, 100);
    resultsTable->setColumnWidth(3, 100);
    
    // Make table read-only
    resultsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    // Center align all cells
    for (int row = 0; row < 2; ++row) {
        for (int col = 0; col < 4; ++col) {
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setTextAlignment(Qt::AlignCenter);
            resultsTable->setItem(row, col, item);
        }
    }
    
    // Set step labels
    resultsTable->item(0, 0)->setText("1st");
    resultsTable->item(1, 0)->setText("2nd");
    
    resultsLayout->addWidget(resultsTable);
    mainLayout->addWidget(resultsGroup);
    
    // Buttons
    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch();
    
    docsButton = new QPushButton("See docs");
    connect(docsButton, &QPushButton::clicked,
            this, &SecondaryImageCalculatorDialog::showDocumentation);
    buttonLayout->addWidget(docsButton);
    
    mainLayout->addLayout(buttonLayout);
    mainLayout->addStretch();
    
    // Connect signals
    connect(fIF1SpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), 
            this, &SecondaryImageCalculatorDialog::calculate);
    connect(fIF2SpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), 
            this, &SecondaryImageCalculatorDialog::calculate);
    connect(fRFSpinBox, QOverload<double>::of(&QDoubleSpinBox::valueChanged), 
            this, &SecondaryImageCalculatorDialog::calculate);
}

void SecondaryImageCalculatorDialog::calculate()
{
    // Get input values
    double f_IF1 = fIF1SpinBox->value();
    double f_IF2 = fIF2SpinBox->value();
    double f_RF = fRFSpinBox->value();
    
    // Calculate LOs
    double f_LO1 = f_RF - f_IF1;
    double f_LO2 = f_IF1 - f_IF2;

    // Calculate image frequencies
    double f_IM1 = f_LO1 - f_IF1;
    double f_IM2 = f_LO2 - f_IF2;
    
    // Update table - First stage
    resultsTable->item(0, 1)->setText(QString("%1 ⇊ %2 MHz")
        .arg(formatFrequency(f_RF), formatFrequency(f_IF1)));
    resultsTable->item(0, 2)->setText(formatFrequency(f_LO1) + " MHz");
    resultsTable->item(0, 3)->setText(formatFrequency(f_IM1) + " MHz");
    
    // Update table - Second stage
    resultsTable->item(1, 1)->setText(QString("%1 ⇊ %2 MHz")
        .arg(formatFrequency(f_IF1), formatFrequency(f_IF2)));
    resultsTable->item(1, 2)->setText(formatFrequency(f_LO2) + " MHz");
    resultsTable->item(1, 3)->setText(formatFrequency(f_IM2) + " MHz");
}

