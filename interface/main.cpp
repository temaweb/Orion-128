#include <QApplication>
#include <QTranslator>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);

    const QString lang = "ru";
    QLocale::setDefault(lang);

    QTranslator translator;
    translator.load(":/translation/language_ru.qm");
    application.installTranslator(&translator);

    MainWindow w;
    w.show();
    return application.exec();
}
