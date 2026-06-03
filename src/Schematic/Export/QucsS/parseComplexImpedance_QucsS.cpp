/// @file parseComplexImpedance_QucsS.cpp
/// @brief Converts a complex impedance component to a RL/RC equivalent at an specific (match) frequency
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date June 3, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "Schematic/Export/QucsS/QucsSExporter.h"

QString QucsSExporter::parseComplexImpedance_QucsS(ComponentInfo Comp) {
    QString Zstr = Comp.val["Z"];
    std::complex<double> Z = Str2Complex(Zstr);
    double R = Z.real();
    double X = Z.imag();
    int x_pos = Comp.Coordinates.at(0) * scale_x + x_offset;
    int y_pos = Comp.Coordinates.at(1) * scale_y + y_offset;
    const bool hasR = (R != 0.0);
    const bool hasX = (X != 0.0);

    // Convert series R+jX to parallel equivalent
    double Rp = 0.0, Xp = 0.0;
    if (hasR && hasX) {
        double mag2 = R * R + X * X;
        Rp = mag2 / R;
        Xp = mag2 / X;
    } else if (hasR) {
        Rp = R;
    } else if (hasX) {
        Xp = X;
    }

    const bool hasRp = (Rp != 0.0);
    const bool hasXp = (Xp != 0.0);

    // Reactive element
    bool isInductive = (Xp >= 0.0);
    double XL = 0.0, XC = 0.0;
    if (hasXp) {
        double f0 = schematic.properties.value("f_match", 0.0);
        if (f0 <= 0.0)
            f0 = std::sqrt(schematic.f_start.toDouble() * schematic.f_stop.toDouble());
        double omega = 2.0 * M_PI * f0;
        if (isInductive) {
            XL = Xp / omega;
        } else {
            XC = -1.0 / (omega * Xp);
        }
    }

    QString R_ID  = Comp.ID + QString("_R");
    QString LC_ID = Comp.ID + (isInductive ? QString("_L") : QString("_C"));


    // Pin positions (same regardless of the imaginary part)
    ComponentPinMap[Comp.ID][0] = QPoint(x_pos, y_pos + 30); // Pin 1
    ComponentPinMap[Comp.ID][1] = QPoint(x_pos, y_pos - 30); // Pin 2

    QString result;

    if (hasRp && hasXp) {
        // Two parallel branches: Real and imaginary part
        result += QString("<R %1 1 %2 %3 75 -45 0 1 \"%4\" 1 \"26.85\" 0 \"US\" 0>\n")
                      .arg(R_ID).arg(x_pos).arg(y_pos)
                      .arg(num2str(Rp, Units::Resistance));

        int reactive_x_pos = x_pos + 60;

        if (isInductive) {
            result += QString("<L %1 1 %2 %3 15 0 0 1 \"%4\" 1>\n")
                          .arg(LC_ID).arg(reactive_x_pos).arg(y_pos)
                          .arg(num2str(XL, Units::Inductance));
        } else {
            result += QString("<C %1 1 %2 %3 15 0 0 1 \"%4\" 1>\n")
                          .arg(LC_ID).arg(reactive_x_pos).arg(y_pos)
                          .arg(num2str(XC, Units::Capacitance));
        }

        result += QString("<GND * 1 %1 %2 0 0 0 0>\n").arg(reactive_x_pos).arg(y_pos+30);

        // Qucs-S wire format: <x1 y1 x2 y2>
        // Top horizontal rail
        m_pendingWires << QString("<%1 %2 %3 %4>")
                              .arg(x_pos).arg(y_pos-50)
                              .arg(reactive_x_pos).arg(y_pos-50);

        // Vertical wire connecting the reactive load
        m_pendingWires << QString("<%1 %2 %3 %4>")
                              .arg(reactive_x_pos).arg(y_pos-50)
                              .arg(reactive_x_pos).arg(y_pos-30);

    } else if (hasRp) {
        // ── Purely resistive ──────────────────────────────────────────────
        result += QString("<R %1 1 %2 %3 20 -10 0 1 \"%4\" 1 \"26.85\" 0 \"US\" 0>\n")
                      .arg(R_ID).arg(x_pos).arg(y_pos)
                      .arg(num2str(Rp, Units::Resistance));
        // No extra wires needed; component pins land exactly on Pin1/Pin2.

    } else if (hasXp) {
        // ── Purely reactive ───────────────────────────────────────────────
        if (isInductive) {
            result += QString("<L %1 1 %2 %3 20 -10 0 1 \"%4\" 1>\n")
                          .arg(LC_ID).arg(x_pos).arg(y_pos)
                          .arg(num2str(XL, Units::Inductance));
        } else {
            result += QString("<C %1 1 %2 %3 20 -10 0 1 \"%4\" 1>\n")
                          .arg(LC_ID).arg(x_pos).arg(y_pos)
                          .arg(num2str(XC, Units::Capacitance));
        }
        // No extra wires needed.
    }

    return result;
}
