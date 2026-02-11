/// @file theme_management.cpp
/// @brief Function for handling the UI theme
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Feb 9, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "UI/qucs-s-spar-viewer.h"

void Qucs_S_SPAR_Viewer::applyTheme(const QString& themeName) {
    QString themePath;

    if (themeName == "custom") {
        themePath = QucsSettings.customThemePath;
        if (themePath.isEmpty() || !QFile::exists(themePath)) {
            QMessageBox::warning(this, tr("Theme Error"),
                                 tr("Custom theme file is invalid or does not exist."));
            return;
        }
    } else {
        if (themeName == QString("light")){
            themePath = QString(":/themes/light-theme.qss");
        } else {
            themePath = QString(":/themes/dark-theme.qss");
        }
    }

    QFile styleFile(themePath);
    if (!styleFile.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Theme Error"),
                             tr("Failed to load theme: %1").arg(styleFile.errorString()));
        return;
    }

    QTextStream stream(&styleFile);
    QString styleSheet = stream.readAll();
    styleFile.close();

    qApp->setStyleSheet(styleSheet);
    QucsSettings.theme = themeName;

    // Save preference
    QSettings settings("qucs", "qucs_s");
    settings.setValue("theme", QucsSettings.theme);
    if (themeName == "custom") {
        settings.setValue("customThemePath", QucsSettings.customThemePath);
    }
}

void Qucs_S_SPAR_Viewer::slotSetLightTheme() {
    applyTheme("light");
}

void Qucs_S_SPAR_Viewer::slotSetDarkTheme() {
    applyTheme("dark");
}

void Qucs_S_SPAR_Viewer::slotLoadCustomTheme() {
    // Determine the themes directory path
    QString appDir = QCoreApplication::applicationDirPath();
    QString themesDir = appDir + "/themes/";

    // Check if themes directory exists, otherwise fall back to home
    QString startDir = QDir(themesDir).exists() ? themesDir : QDir::homePath();

    QString filename = QFileDialog::getOpenFileName(
        this,
        tr("Select Custom Theme File"),
        startDir,  // Changed from QDir::homePath()
        tr("Stylesheet Files (*.qss *.css);;All Files (*)")
        );

    if (filename.isEmpty()) {
        return; // User cancelled
    }

    QucsSettings.customThemePath = filename;
    applyTheme("custom");
}


