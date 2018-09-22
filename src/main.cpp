#include "mainwindow.h"

#include <QApplication>
#include <QFile>
#include <QFileInfo>
#include <QLocale>
#include <QTranslator>
#include <QLibraryInfo>
#include <string>

#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QString appName = QCoreApplication::applicationName().toLower();
    QString locale = QLocale::system().name();
    QString translationsPath = QLibraryInfo::location(QLibraryInfo::TranslationsPath);
    QString appDirectory = app.applicationDirPath();

#if defined(Q_OS_MAC)
    QFileInfo amTranslationsPath(appDirectory + "/../../../data/");
#elif defined(Q_OS_UNIX)
    QFileInfo amTranslationsPath(appDirectory + "/../share/net.bartkessels." + appName + "/translations/");
#else
    QFileInfo amTranslationsPath(appDirectory + "/data/");
#endif

    // Load Qt translations
    QTranslator qtTranslator;
    bool qtTranslationFound = qtTranslator.load("qt_" + locale,
                                                translationsPath);

    if (qtTranslationFound) {
        app.installTranslator(&qtTranslator);
    }

    // Load Advanced Metronome translations
    QTranslator amTranslator;
    bool amTranslationsFound = amTranslator.load(appName + "_" + locale,
                                                 amTranslationsPath.absolutePath());

    if (amTranslationsFound) {
        app.installTranslator(&amTranslator);
    }

    // Display the main window
    MainWindow w;
    w.show();

    // Check if a file is being opened
    if (argc >= 2 && strlen(argv[1]) > 0) {
        qInfo() << "Komt in args: " << argv[1] << endl;
        w.loadFromJson(argv[1]);
    }

    return app.exec();
}
