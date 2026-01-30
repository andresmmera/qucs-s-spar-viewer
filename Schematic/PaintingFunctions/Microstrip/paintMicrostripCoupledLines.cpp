/// @file paintMicrostripCoupledLines.cpp
/// @brief Coupled microstrip line painting method
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 3, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "Schematic/component.h"

/// @brief Microstrip coupled line painting method
/// \param painter Painter object
void Component::paintMicrostripCoupledLines(QPainter *painter) {

  if (Rotation != 0) {
    painter->rotate(Rotation);
  }

  int w = 15, shiftx = 10;

  // Fill left microstrip rectangle with dark orange
  QRect fillRectLeft(-shiftx - w / 2, -14, w, 30);
  painter->fillRect(fillRectLeft, QColor(255, 140, 0)); // dark orange

  // Fill right microstrip rectangle with dark orange
  QRect fillRectRight(shiftx - w / 2, -14, w, 30);
  painter->fillRect(fillRectRight, QColor(255, 140, 0)); // dark orange

  // Draw left microstrip coupled line
  painter->setPen(QPen(Qt::black, 1));
  painter->drawLine(QPoint(-shiftx, -25), QPoint(-shiftx, -14));
  painter->drawLine(QPoint(-shiftx - 0.5 * w, -14),
                    QPoint(-shiftx + 0.5 * w, -14));
  painter->drawLine(QPoint(-shiftx - 0.5 * w, -14),
                    QPoint(-shiftx - 0.5 * w, 16));
  painter->drawLine(QPoint(-shiftx + 0.5 * w, -14),
                    QPoint(-shiftx + 0.5 * w, 16));
  painter->drawLine(QPoint(-shiftx - 0.5 * w, 16),
                    QPoint(-shiftx + 0.5 * w, 16));
  painter->drawLine(QPoint(-shiftx, 16), QPoint(-shiftx, 25));

  // Draw right microstrip coupled line
  painter->drawLine(QPoint(shiftx, -25), QPoint(shiftx, -14));
  painter->drawLine(QPoint(shiftx - 0.5 * w, -14),
                    QPoint(shiftx + 0.5 * w, -14));
  painter->drawLine(QPoint(shiftx - 0.5 * w, -14),
                    QPoint(shiftx - 0.5 * w, 16));
  painter->drawLine(QPoint(shiftx + 0.5 * w, -14),
                    QPoint(shiftx + 0.5 * w, 16));
  painter->drawLine(QPoint(shiftx - 0.5 * w, 16), QPoint(shiftx + 0.5 * w, 16));
  painter->drawLine(QPoint(shiftx, 16), QPoint(shiftx, 25));

  // Undo rotation for text
  if (Rotation != 0) {
    painter->rotate(-Rotation);
  }

  QPoint OriginText(20, -10);
  if (Rotation != 0) {
    OriginText.setX(-20), OriginText.setY(20);
  }

  // Draw ID and parameters text
  painter->drawText(QRect(OriginText, QPoint(100, 100)),
                    QString("%1").arg(this->ID));
  painter->drawText(QRect(OriginText + QPoint(0, 10), QPoint(100, 100)),
                    QString("W=%1").arg(Value["W"]));
  painter->drawText(QRect(OriginText + QPoint(0, 20), QPoint(100, 100)),
                    QString("L=%1").arg(Value["L"]));
  painter->drawText(QRect(OriginText + QPoint(0, 30), QPoint(100, 100)),
                    QString("S=%1").arg(Value["S"]));
}
