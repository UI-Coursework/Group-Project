#include "mainwindow.hpp"
#include "overviewpage.hpp"
#include <QLabel>
#include <QVBoxLayout>
#include "compliance_dashboard.hpp"
#include "dashboard.hpp"
#include "enviwindow.hpp"
#include "pop.hpp"
#include "fluorinatedcompounds.hpp"


MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    tabWidget = new QTabWidget(this);
    tabWidget->addTab(new Dashboard(), "Dashboard"); // Use the Dashboard class
    tabWidget->addTab(new OverviewPage(), "Overview");
    tabWidget->addTab(new ComplianceDashboard(), "Compliance Dashboard");
    tabWidget->addTab(new EnviWindow(), "Environmental Litter");
    tabWidget->addTab(new FluorinatedCompounds(), "Fluorinated Compounds");
    tabWidget->addTab(new popWindow(), "POP");
    setCentralWidget(tabWidget);
    setWindowTitle("Water Quality Monitoring");
    resize(1200, 800);
}

MainWindow::~MainWindow() {}



