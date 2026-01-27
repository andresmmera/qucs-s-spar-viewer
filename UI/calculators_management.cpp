/// @file calculators_management.cpp
/// @brief Implementation of the slots to call the dialog calculators
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 27, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "./../Tools/Calculators/ReflectionCalculators/gamma_calculator.h"
#include "qucs-s-spar-viewer.h"

QMenu *Qucs_S_SPAR_Viewer::CreateCalculatorsMenu() {
  QMenu *calculatorsMenu = new QMenu(tr("Calculators"), this);

  // ========== RF Calculators ==========
  QMenu *rfMenu = new QMenu(tr("RF"), this);

  // Reflection Coefficient submenu
  QMenu *reflectionMenu = new QMenu(tr("Reflection Coefficient"), this);

  // Gamma → Impedance / SWR / S11 calculator
  QAction *gammaToolAction = new QAction("Gamma → Z / SWR / S11 (dB)", this);
  reflectionMenu->addAction(gammaToolAction);
  connect(gammaToolAction, &QAction::triggered, this,
          &Qucs_S_SPAR_Viewer::slotGammaCalculator);

  // Build RF menu hierarchy
  rfMenu->addMenu(reflectionMenu);

  // Add RF menu to Calculators
  calculatorsMenu->addMenu(rfMenu);

  return calculatorsMenu;
}

// Gamma → Z / SWR / S11 (dB)
void Qucs_S_SPAR_Viewer::slotGammaCalculator() {
  // Show modal dialog with fields: mag(gamma), angle(gamma) [deg], Z0 [ohm]
  GammaCalculatorDialog dlg(this);
  dlg.exec();
}
