#include "mainwindow.hpp"
#include "datamanager.hpp"
#include <QApplication>
#include <QTranslator>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    QTranslator trn;
    if (trn.load(QLocale::system(), "watertool", "_", ":/i18n")) {
        a.installTranslator(&trn);
    }

    DataManager dataManager;
    dataManager.loadData("data.csv");

    MainWindow w;
    w.show();
    return a.exec();
}
