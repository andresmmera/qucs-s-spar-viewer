/// @file paintMicrostripLine.cpp
/// @brief Microstrip line painting method
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 3, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "Schematic/component.h"

/// @brief Microstrip line painting method
/// \param painter Painter object
void Component::paintMicrostripLine(QPainter *painter) {

  if (Rotation != 0) {
    painter->rotate(Rotation);
  }

  int w = 15;

  // Fill rectangle with dark orange
  QRect fillRect(-w / 2, -14, w, 30);
  painter->fillRect(fillRect, QColor(255, 140, 0)); // dark orange

  // Draw microstrip rectangle outline and connectors
  painter->setPen(QPen(Qt::black, 1));
  painter->drawLine(QPoint(0, -25), QPoint(0, -14));
  painter->drawLine(QPoint(-0.5 * w, -14), QPoint(0.5 * w, -14));
  painter->drawLine(QPoint(-0.5 * w, -14), QPoint(-0.5 * w, 16));
  painter->drawLine(QPoint(0.5 * w, -14), QPoint(0.5 * w, 16));
  painter->drawLine(QPoint(-0.5 * w, 16), QPoint(0.5 * w, 16));
  painter->drawLine(QPoint(0, 16), QPoint(0, 25));

  // Undo rotation for text
  if (Rotation != 0) {
    painter->rotate(-Rotation);
  }

  QPoint OriginText(10, -10);
  if (Rotation != 0) {
    OriginText.setX(-15), OriginText.setY(10);
  }

  // Draw ID and other parameters text
  painter->drawText(QRect(OriginText, QPoint(100, 100)),
                    QString("%1").arg(this->ID));
  painter->drawText(QRect(OriginText + QPoint(0, 10), QPoint(100, 100)),
                    QString("W=%1").arg(Value["Width"]));
  painter->drawText(QRect(OriginText + QPoint(0, 20), QPoint(100, 100)),
                    QString("L=%1").arg(Value["Length"]));
}
