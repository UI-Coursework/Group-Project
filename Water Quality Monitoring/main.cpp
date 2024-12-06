#include "mainwindow.hpp"
#include "datamanager.hpp"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    DataManager dataManager;
    dataManager.loadData("data.csv");

    MainWindow w;
    w.show();
    return a.exec();
}
