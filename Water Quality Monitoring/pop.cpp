#include "pop.hpp"
#include <QtCharts/QLineSeries>
#include <QStackedWidget>
#include <QPushButton>
#include <QFile>
#include <QDir>
#include <QDebug>
#include "fluorinatedcompounds.hpp"

popWindow::popWindow(QWidget *parent)
    : QMainWindow(parent)
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    mainLayout = new QVBoxLayout(centralWidget);

    // Create switch button
    switchButton = new QPushButton("Switch to Fluorinated Compounds");
    mainLayout->addWidget(switchButton);

    // Create stacked widget
    stackedWidget = new QStackedWidget();
    mainLayout->addWidget(stackedWidget);

    // Create pages
    QWidget *popPage = new QWidget();
    QWidget *fluorPage = new QWidget();

    popLayout = new QGridLayout(popPage);
    fluorPage = new FluorinatedCompounds();
    stackedWidget->addWidget(fluorPage);

    stackedWidget->addWidget(popPage);
    stackedWidget->addWidget(fluorPage);

    // Connect button
    connect(switchButton, &QPushButton::clicked, this, &popWindow::switchPage);

    // Load initial POP data
    QTimer::singleShot(1000, this, &popWindow::loadPopData);
}

popWindow::~popWindow() {}

void popWindow::loadPopData()
{
    QString filePath = "data.csv"; // Adjust path as needed
    if (QFile::exists(filePath)) {
        dataManager.loadData(filePath);
        updatePopPage();
    } else {
        qDebug() << "No data file found at" << filePath;
    }
}

void popWindow::updatePopPage()
{
    const auto &data = dataManager.getData();

    // Clear existing layout
    while (QLayoutItem *item = popLayout->takeAt(0)) {
        delete item->widget();
        delete item;
    }

    int row = 0;
    QMap<QString, QVector<QPair<QDateTime, double>>> trends; // Store trends per pollutant

    for (const auto &pollutant : data) {
        QDateTime date = QDateTime::fromString(pollutant.sampleDateTime, Qt::ISODate);
        trends[pollutant.determinandLabel].append({date, pollutant.result});
    }

    for (auto it = trends.begin(); it != trends.end(); ++it) {
        QString name = it.key();
        QVector<QPair<QDateTime, double>> values = it.value();

        QVector<double> results;
        QVector<QDateTime> dates;

        for (const auto &value : values) {
            dates.append(value.first);
            results.append(value.second);
        }

        // Compliance check example
        bool compliant = true; // Logic for compliance

        QWidget *widget = createPopWidget(name, results, compliant);
        popLayout->addWidget(widget, row++, 0);
    }
}

QWidget* popWindow::createPopWidget(const QString &name, const QVector<double> &data, bool compliant)
{
    QWidget *widget = new QWidget();
    QVBoxLayout *layout = new QVBoxLayout(widget);

    QLabel *nameLabel = new QLabel(name);
    nameLabel->setStyleSheet(QString("color: %1; font-weight: bold;").arg(compliant ? "green" : "red"));
    layout->addWidget(nameLabel);

    QChartView *chartView = new QChartView();
    setupChart(chartView, data);
    layout->addWidget(chartView);

    QString tooltipText = QString("Health Risks: Moderate\n"
                                  "Monitoring Importance: High\n"
                                  "Safety Levels: Check compliance.\n"
                                  "Latest Result: %1.\n").arg(QString::number(data.last())); // Convert last value
    QLabel *tooltip = new QLabel(tooltipText);
    layout->addWidget(tooltip);

    return widget;
}


void popWindow::setupChart(QChartView *chartView, const QVector<double> &data)
{
    QLineSeries *series = new QLineSeries();

    for (int i = 0; i < data.size(); ++i) {
        series->append(i, data[i]);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);

    // Create default axes first
    chart->createDefaultAxes();

    // Get the axes and set their titles
    QAbstractAxis *axisX = chart->axes(Qt::Horizontal).first();
    QAbstractAxis *axisY = chart->axes(Qt::Vertical).first();

    axisX->setTitleText("Sample Number");
    axisY->setTitleText("Concentration (μg/m³)");

    chart->setTitle("POP Levels Over Time");
    chart->legend()->hide();

    chartView->setChart(chart);
}

void popWindow::switchPage()
{
    if (stackedWidget->currentIndex() == 0) {
        stackedWidget->setCurrentIndex(1);
        switchButton->setText("Switch to POP Data");
        qDebug() << "Switching to Fluorinated Page";
    } else {
        stackedWidget->setCurrentIndex(0);
        switchButton->setText("Switch to Fluorinated Compounds");
        loadPopData();
        qDebug() << "Switching to POP Page";  // Debug output
    }
}


