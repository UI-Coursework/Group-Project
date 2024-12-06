#include "mainwindow.hpp"
#include "overviewpage.hpp"
#include <QLabel>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    tabWidget = new QTabWidget(this);
    tabWidget->addTab(createPage1(), "Dashboard");
    tabWidget->addTab(new OverviewPage(), "Overview");
    tabWidget->addTab(createPage3(), "POP");
    setCentralWidget(tabWidget);
    setWindowTitle("Water Quality Monitoring");
    resize(1200, 800);
}

MainWindow::~MainWindow() {}


QWidget* MainWindow::createPage1() {
    QWidget* page = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->addWidget(new QLabel("Dashboard"));
    return page;
}

QWidget* MainWindow::createPage3() {
    QWidget* page = new QWidget();
    QVBoxLayout* layout = new QVBoxLayout(page);
    layout->addWidget(new QLabel("POP"));
    return page;
}
