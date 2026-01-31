/// @file calculators_management.cpp
/// @brief Implementation of the slots to call the dialog calculators
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 27, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "./Tools/Calculators/General/EquivalentCalculators/ParallelInductors/parallel_inductors.h"
#include "./Tools/Calculators/General/EquivalentCalculators/ParallelResistors/parallel_resistors.h"
#include "./Tools/Calculators/General/EquivalentCalculators/SeriesCapacitors/series_capacitors.h"
#include "./Tools/Calculators/General/VoltageDivider/voltage_divider.h"
#include "./Tools/Calculators/RF/ReflectionCalculators/SWR_S11_calculator/swr_s11_calculator.h"
#include "./Tools/Calculators/RF/ReflectionCalculators/gamma_calculator/gamma_calculator.h"
#include "./Tools/Calculators/RF/ReflectionCalculators/impedance_calculator/impedance_calculator.h"
#include "./Tools/Calculators/RF/FreeSpaceLoss/free_space_loss.h"
#include "./Tools/Calculators/RF/FrequencyToWavelength/freq_wavelength_converter.h"
#include "./Tools/Calculators/RF/OctaveBandwidthwCalculator/octaveBW_calculator.h"
#include "./Tools/Calculators/RF/RFPowerConverter/RF_power_converter.h"

#include "qucs-s-spar-viewer.h"

QMenu *Qucs_S_SPAR_Viewer::CreateCalculatorsMenu() {
  QMenu *calculatorsMenu = new QMenu(tr("Calculators"), this);

  // 1) RF Calculators
  QMenu *rfMenu = new QMenu(tr("RF"), this);

  // 1.1) Reflection Coefficient submenu
  QMenu *reflectionMenu = new QMenu(tr("Reflection Coefficient"), this);

  // 1.1.1) Gamma → Impedance / SWR / S11 calculator
  QAction *gammaToolAction = new QAction("Γ → Z / SWR / S11 (dB)", this);
  reflectionMenu->addAction(gammaToolAction);
  connect(gammaToolAction, &QAction::triggered, this,
          &Qucs_S_SPAR_Viewer::slotGammaCalculator);

  // 1.1.2) Impedance → Gamma / SWR / S11 calculator
  QAction *impedanceToolAction = new QAction("Z → Γ / SWR / S11 (dB)", this);
  reflectionMenu->addAction(impedanceToolAction);
  connect(impedanceToolAction, &QAction::triggered, this,
          &Qucs_S_SPAR_Viewer::slotImpedanceCalculator);

  // 1.1.3) VSWR ↔ S11 ↔ |Γ| bidirectional calculator
  QAction *swrS11ToolAction = new QAction("VSWR ↔ S11 ↔ |Γ|", this);
  reflectionMenu->addAction(swrS11ToolAction);
  connect(swrS11ToolAction, &QAction::triggered, this,
          &Qucs_S_SPAR_Viewer::slotSwrS11Calculator);

  // Add reflection tools to RF calculator menu
  rfMenu->addMenu(reflectionMenu);

  // 1.2) Octaves and decades from corner frequencies
  QAction *OctaveBWAction = new QAction("Octaves and decades from BW", this);
  rfMenu->addAction(OctaveBWAction);
  connect(OctaveBWAction, &QAction::triggered, this,
          &Qucs_S_SPAR_Viewer::slotOctaveBWCalculator);

  // 1.3) RF power unit converter
  QAction *RFPowerUnitConverterAction =
      new QAction("RF power unit converter", this);
  rfMenu->addAction(RFPowerUnitConverterAction);
  connect(RFPowerUnitConverterAction, &QAction::triggered, this,
          &Qucs_S_SPAR_Viewer::slotRFPowerUnitCalculator);

  // 1.4) Frequency to wavelength converter
  QAction *FreqtoLambdaConverterAction = new QAction("Frequency ↔ λ", this);
  rfMenu->addAction(FreqtoLambdaConverterAction);
  connect(FreqtoLambdaConverterAction, &QAction::triggered, this,
          &Qucs_S_SPAR_Viewer::slotFrequencyToWavelengthCalculator);

  // 1.5) Free space loss calculator
  QAction *FreeSpaceLossCalaculatorAction =
      new QAction("Free Space Loss", this);
  rfMenu->addAction(FreeSpaceLossCalaculatorAction);
  connect(FreeSpaceLossCalaculatorAction, &QAction::triggered, this,
          &Qucs_S_SPAR_Viewer::slotFreeSpaceLossCalculator);

  // Add RF menu to Calculators menu option
  calculatorsMenu->addMenu(rfMenu);

  // 2) General electronics
  QMenu *GeneralElectronicsMenu = new QMenu(tr("General"), this);

  // 2.1) Voltage divider
  QAction *VoltageDividerAction = new QAction("Voltage Divider", this);
  GeneralElectronicsMenu->addAction(VoltageDividerAction);
  connect(VoltageDividerAction, &QAction::triggered, this,
          &Qucs_S_SPAR_Viewer::slotVoltageDividerCalculator);

  // 2.2) Equivalent parallel R, L and series C
  QMenu *EquivalentCalculatorsMenu =
      new QMenu(tr("Equivalent Calculators"), this);
  // 2.2.1) Parallel resistors equivalent
  QAction *ParallelResistorsAction = new QAction("Parallel Resistors", this);
  EquivalentCalculatorsMenu->addAction(ParallelResistorsAction);
  connect(ParallelResistorsAction, &QAction::triggered, this,
          &Qucs_S_SPAR_Viewer::slotParallelResistorsCalculator);

  // 2.2.2) Parallel capacitors equivalent
  QAction *SeriesCapacitorsAction = new QAction("Series Capacitors", this);
  EquivalentCalculatorsMenu->addAction(SeriesCapacitorsAction);
  connect(SeriesCapacitorsAction, &QAction::triggered, this,
          &Qucs_S_SPAR_Viewer::slotSeriesCapacitorsCalculator);

  // 2.2.3) Parallel inductors equivalent
  QAction *ParallelInductorsAction = new QAction("Parallel Inductors", this);
  EquivalentCalculatorsMenu->addAction(ParallelInductorsAction);
  connect(ParallelInductorsAction, &QAction::triggered, this,
          &Qucs_S_SPAR_Viewer::slotParallelInductorsCalculator);

  // Add equivalent calculators to "General"
  GeneralElectronicsMenu->addMenu(EquivalentCalculatorsMenu);
  // Add "General" menu to Calculators menu option
  calculatorsMenu->addMenu(GeneralElectronicsMenu);

  return calculatorsMenu;
}

// 1) RF calculators

// 1.1.1) Gamma → Z / SWR / S11 (dB)
void Qucs_S_SPAR_Viewer::slotGammaCalculator() {
  GammaCalculatorDialog dlg(this);
  dlg.exec();
}

// 1.1.2) Z → Γ / SWR / S11 (dB)
void Qucs_S_SPAR_Viewer::slotImpedanceCalculator() {
  ImpedanceCalculatorDialog dlg(this);
  dlg.exec();
}

// 1.1.3) VSWR ↔ S11 ↔ |Γ|
void Qucs_S_SPAR_Viewer::slotSwrS11Calculator() {
  SwrS11CalculatorDialog dlg(this);
  dlg.exec();
}

// 1.2) Octaves and decades from corner frequencies
void Qucs_S_SPAR_Viewer::slotOctaveBWCalculator() {
  OctaveBWCalculatorDialog dlg(this);
  dlg.exec();
}

// 1.3) RF power unit converter
void Qucs_S_SPAR_Viewer::slotRFPowerUnitCalculator() {
  RFPowerConverterDialog dlg(this);
  dlg.exec();
}

// 1.4) Frequency to wavelength converter
void Qucs_S_SPAR_Viewer::slotFrequencyToWavelengthCalculator() {
  FreqWavelengthConverterDialog dlg(this);
  dlg.exec();
}

// 1.5) Free space loss calculator
void Qucs_S_SPAR_Viewer::slotFreeSpaceLossCalculator() {
  FreeSpaceAttenuationDialog dlg(this);
  dlg.exec();
}

// 2) General electronics calculators
// 2.1) Free space loss calculator
void Qucs_S_SPAR_Viewer::slotVoltageDividerCalculator() {
  VoltageDividerDialog dlg(this);
  dlg.exec();
}

// 2.2) Equivalent calculators
// 2.2.1) Parallel resistors equivalent
void Qucs_S_SPAR_Viewer::slotParallelResistorsCalculator() {
  ParallelResistorsDialog dlg(this);
  dlg.exec();
}

// 2.2.2) Parallel capacitors equivalent
void Qucs_S_SPAR_Viewer::slotSeriesCapacitorsCalculator() {
  SeriesCapacitorsDialog dlg(this);
  dlg.exec();
}

// 2.2.3) Parallel inductors equivalent
void Qucs_S_SPAR_Viewer::slotParallelInductorsCalculator() {
    ParallelInductorsDialog dlg(this);
    dlg.exec();
}
