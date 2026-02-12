/****************************************************************************
**     Qucs Attenuator Synthesis
**     main.cpp
**
**
**
**
**
**
**
*****************************************************************************/

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <stdlib.h>

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QFont>
#include <QMessageBox>
#include <QScreen>
#include <QSettings>
#include <QString>
#include <QStyle>
#include <QTextStream>
#include <QTranslator>

#include "UI/qucs-s-spar-viewer.h"

struct tQucsSettings QucsSettings;

// #########################################################################
// Loads the settings file and stores the settings.
bool loadSettings() {
    QSettings settings("qucs", "qucs_s");
    settings.beginGroup("QucsSparViewer");
    if (settings.contains("x")) {
        QucsSettings.x = settings.value("x").toInt();
    }
    if (settings.contains("y")) {
        QucsSettings.y = settings.value("y").toInt();
    }
    settings.endGroup();

    if (settings.contains("font")) {
        QucsSettings.font.fromString(settings.value("font").toString());
    }
    if (settings.contains("Language")) {
        QucsSettings.Language = settings.value("Language").toString();
    }
    if (settings.contains("theme")) {
        QucsSettings.theme = settings.value("theme").toString();
    } else {
        QucsSettings.theme = "light"; // Default theme
    }
    if (settings.contains("customThemePath")) {
        QucsSettings.customThemePath = settings.value("customThemePath").toString();
    }

    return true;
}

// #########################################################################
// Saves the settings in the settings file.
bool saveApplSettings(Qucs_S_SPAR_Viewer* qucs) {
    QSettings settings("qucs", "qucs_s");
    settings.beginGroup("QucsSparViewer");
    settings.setValue("x", qucs->x());
    settings.setValue("y", qucs->y());
    settings.endGroup();
    settings.setValue("theme", QucsSettings.theme);
    settings.setValue("customThemePath", QucsSettings.customThemePath);
    return true;
}

bool loadTheme(const QString& themeName) {
    QString themePath;

    if (themeName == "custom") {
        // Load custom theme from file system
        themePath = QucsSettings.customThemePath;
        if (themePath.isEmpty() || !QFile::exists(themePath)) {
            qWarning() << "Custom theme path is invalid";
            return false;
        }
    } else {
        // Load built-in theme from resources
        themePath = QString(":/themes/%1-theme.qss").arg(themeName);
    }

    QFile styleFile(themePath);
    if (!styleFile.exists()) {
        qWarning() << "Theme file does not exist:" << themePath;
        return false;
    }

    if (!styleFile.open(QFile::ReadOnly | QFile::Text)) {
        qWarning() << "Cannot open theme file:" << themePath;
        return false;
    }

    QTextStream stream(&styleFile);
    QString styleSheet = stream.readAll();
    styleFile.close();

    if (styleSheet.isEmpty()) {
        qWarning() << "Theme file is empty:" << themePath;
        return false;
    }

    qApp->setStyleSheet(styleSheet);
    qDebug() << "Successfully loaded theme:" << themeName;
    return true;
}

int main(int argc, char** argv) {
  QApplication a(argc, argv);

  // Force Fusion style
  QApplication::setStyle("Fusion");

  // apply default settings
  QucsSettings.x = 200;
  QucsSettings.y = 100;

  // is application relocated?
  char* var = getenv("QUCSDIR");
  QDir QucsDir;
  if (var != NULL) {
    QucsDir            = QDir(var);
    QString QucsDirStr = QucsDir.canonicalPath();
    QucsSettings.LangDir =
        QDir::toNativeSeparators(QucsDirStr + "/share/" QUCS_NAME "/lang/");
  } else {
    QString QucsApplicationPath = QCoreApplication::applicationDirPath();
#ifdef __APPLE__
    QucsDir = QDir(QucsApplicationPath.section("/bin", 0, 0));
#else
    QucsDir = QDir(QucsApplicationPath);
    QucsDir.cdUp();
#endif
    QucsSettings.LangDir = QucsDir.canonicalPath() + "/share/qucs/lang/";
  }

  loadSettings();

  // Apply theme
  if (!loadTheme(QucsSettings.theme)) {
      qWarning() << "Failed to load theme, falling back to light theme";
      QucsSettings.theme = "light";
      loadTheme("light");
  }

  QTranslator tor(0);
  QString lang = QucsSettings.Language;
  if (lang.isEmpty()) {
    lang = QString(QLocale::system().name());
  }
  static_cast<void>(
      tor.load(QStringLiteral("qucs_") + lang, QucsSettings.LangDir));
  a.installTranslator(&tor);

  Qucs_S_SPAR_Viewer* qucs = new Qucs_S_SPAR_Viewer();

  if (argc > 1) { // File or directory path to watch
    QString path = QString(argv[1]);
    QFileInfo fileInfo(path);

    if (fileInfo.exists()) {
      if (fileInfo.isDir()) {
        // It's a directory
        qucs->addPathToWatcher(path);
      } else if (fileInfo.isFile()) {
        // It's a file
        qucs->addFile(fileInfo);
      }
    } else {
      QMessageBox::warning(qucs, "Path Error",
                           "The specified path does not exist.");
    }
  }
  qucs->raise();
  qucs->move(QucsSettings.x, QucsSettings.y); // position before "show" !!!
  qucs->show();

  // Window size
  // In initially, the window's size was proportional to the screen size, but after testing the program in
  // big screens, it seemed more convenient to have a fixed, small size. Then the user can resize as it likes.
  QSize initialWindowSize(1200, 650); // width x height in pixels

  qucs->resize(initialWindowSize);

  // Center the window on the primary screen
  QScreen* primaryScreen = QGuiApplication::primaryScreen();
  if (primaryScreen) {
      QRect screenGeometry = primaryScreen->availableGeometry();

      // Get the window's frame geometry
      QRect frameGeom = qucs->frameGeometry();

      // Move the top-left corner to center the frame on the screen
      frameGeom.moveCenter(screenGeometry.center());
      qucs->move(frameGeom.topLeft());
  }

  int result = a.exec();
  saveApplSettings(qucs);
  return result;
}
