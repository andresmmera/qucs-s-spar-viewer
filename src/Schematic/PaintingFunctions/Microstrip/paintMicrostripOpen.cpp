/// @file paintMicrostripOpen.cpp
/// @brief Microstrip open painting method
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 3, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "Schematic/component.h"

/// @brief Microstrip open painting method
/// \param painter Painter object
void Component::paintMicrostripOpen(QPainter *painter) {
  if (Rotation != 0) {
    painter->rotate(Rotation);
  }

  int w = 15;      // Microstrip width (similar to line)
  int length = 22; // Shortened section for open

  // Fill rectangle for the microstrip segment
  QRect fillRect(-w / 2, -14, w, length);
  painter->fillRect(fillRect, QColor(255, 140, 0)); // dark orange

  // Draw outline and left port connector
  painter->setPen(QPen(Qt::black, 1));
  painter->drawLine(QPoint(0, -25), QPoint(0, -14));          // left connector
  painter->drawLine(QPoint(-w / 2, -14), QPoint(w / 2, -14)); // top edge
  painter->drawLine(QPoint(-w / 2, -14),
                    QPoint(-w / 2, length - 14)); // left edge
  painter->drawLine(QPoint(w / 2, -14),
                    QPoint(w / 2, length - 14)); // right edge
  painter->drawLine(QPoint(-w / 2, length - 14),
                    QPoint(w / 2, length - 14)); // bottom edge

  // Draw 4 parallel thin diagonal lines at the open end
  int edgeY = length - 14;
  int lineSpacing = 5;
  int lineLen = 4;
  int baseOffset = -7;

  painter->setPen(QPen(Qt::black, 1));
  painter->drawLine(
      QPoint(baseOffset + 0 * lineSpacing, edgeY),
      QPoint(baseOffset + 0 * lineSpacing + lineLen, edgeY + lineLen));
  painter->drawLine(
      QPoint(baseOffset + 1 * lineSpacing, edgeY),
      QPoint(baseOffset + 1 * lineSpacing + lineLen, edgeY + lineLen));
  painter->drawLine(
      QPoint(baseOffset + 2 * lineSpacing, edgeY),
      QPoint(baseOffset + 2 * lineSpacing + lineLen, edgeY + lineLen));
  painter->drawLine(
      QPoint(baseOffset + 3 * lineSpacing, edgeY),
      QPoint(baseOffset + 3 * lineSpacing + lineLen, edgeY + lineLen));

  // Undo rotation for parameter text
  if (Rotation != 0) {
    painter->rotate(-Rotation);
  }

  QPoint OriginText(10, -10);
  if (Rotation != 0) {
    OriginText.setX(-15), OriginText.setY(10);
  }

  // Draw ID and parameters: width only
  painter->drawText(QRect(OriginText, QPoint(100, 100)),
                    QString("%1").arg(this->ID));
  painter->drawText(QRect(OriginText + QPoint(0, 10), QPoint(100, 100)),
                    QString("W=%1").arg(Value["Width"]));
}
