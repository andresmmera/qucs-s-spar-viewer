/// @file SecondaryImageDocs.cpp
/// @brief Documentation for the secondary image frequency calculator
/// @author Andrés Martínez Mera - andresmmera@protonmail.com
/// @date Jan 31, 2026
/// @copyright Copyright (C) 2026 Andrés Martínez Mera
/// @license GPL-3.0-or-later

#include "SecondaryImageCalculatorDialog.h"
#include <QCoreApplication>
#include <QDesktopServices>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QMessageBox>
#include <QUrl>

void SecondaryImageCalculatorDialog::showDocumentation() { // Determine
                                                           // documentation path
  QString docPath;
  QString appDir = QCoreApplication::applicationDirPath();
  QString path = QString("/Calculators/SecondaryImageFrequency/index.html");

#ifdef Q_OS_MACOS
  // macOS bundle: app.app/Contents/MacOS/../Resources/doc/
  docPath = appDir + "/../Resources/doc" + path;
#else
  // Linux/Windows installed: bin/../share/qucs-sspar-viewer/doc/
  docPath = appDir + "/../share/qucs-sspar-viewer/doc/" + path;
#endif

  // Fallback 1: Running from Qt Creator build directory
  if (!QFile::exists(docPath)) {
    QDir buildDir(appDir);
    buildDir.cdUp(); // out of build subdir
    buildDir.cdUp(); // out of build-xxx directory
    docPath = buildDir.filePath("docs/help/build/html" + path);
  }

  // Fallback 2: Source tree (direct relative path)
  if (!QFile::exists(docPath)) {
    docPath = appDir + "/../../../docs/help/build/html" + path;
  }

  // Open in default web browser
  if (QFile::exists(docPath)) {
    QUrl url = QUrl::fromLocalFile(QFileInfo(docPath).absoluteFilePath());
    if (!QDesktopServices::openUrl(url)) {
      QMessageBox::warning(
          nullptr, "Error",
          "Could not open documentation in web browser.\nPath: " + docPath);
    }
  } else {
    QMessageBox::warning(nullptr, "Documentation Not Found",
                         "Could not find documentation file.\nSearched path: " +
                             docPath);
  }
}
