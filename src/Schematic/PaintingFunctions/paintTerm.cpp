/// @file paintTerm.cpp
/// @brief Term painting method
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 3, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "Schematic/component.h"

/// @brief Port terminal painting method
/// \param painter Painter object
void Component::paintTerm(QPainter *painter) {
  if (Rotation != 0) {
    painter->rotate(Rotation);
  }

  QPainterPath path;
  path.moveTo(0, 0);
  path.lineTo(0, 6);
  path.lineTo(10, 0);
  path.lineTo(0, -6);
  painter->setPen(Qt ::NoPen);
  painter->fillPath(path, QBrush(QColor("red")));
  painter->setPen(QPen(Qt::black, 1));

  int OriginText_x = -25;
  if (Rotation != 0) {
    painter->rotate(-Rotation);
    OriginText_x = 5;
  }

  painter->drawText(QRect(OriginText_x, -10, 100, 100),
                    QString("%1").arg(this->ID));
  painter->drawText(
      QRect(OriginText_x, 0, 100, 100),
      QString("%1").arg(Value["Z"].replace("Ohm", QChar(0xa9, 0x03))));
}
