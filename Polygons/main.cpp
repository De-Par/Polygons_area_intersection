#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include "ui/MainWindow.hpp"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QApplication::setWindowIcon(QIcon(":/res/ico/logo.ico"));
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString& locale : uiLanguages) {
        const QString baseName = "Polygons_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            QApplication::installTranslator(&translator);
            break;
        }
    }
    MainWindow w;
    w.show();
    return QApplication::exec();
}
