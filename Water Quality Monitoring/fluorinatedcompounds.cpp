#include "fluorinatedcompounds.hpp"
#include "ui_fluorinatedcompounds.h"
#include <QVBoxLayout>
#include <QToolTip>
#include <QDateTime>
#include <QRandomGenerator>
#include <QtCharts/QChart>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>

const double FluorinatedCompounds::PFAS_THRESHOLD = 0.1; // µg/L

FluorinatedCompounds::FluorinatedCompounds(QWidget *parent)
    : QDialog(parent), ui(new Ui::FluorinatedCompounds)
{
    ui->setupUi(this);
    setWindowTitle("PFAS Monitoring Dashboard");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    setupChart();
    loadAndDisplayData();

    mainLayout->addWidget(chartView);
}

void FluorinatedCompounds::loadAndDisplayData()
{
    dataManager.loadData("data.csv");  // Please Adjust the path to your CSV file
    updateChart(dataManager.getData());
}

void FluorinatedCompounds::updateChart(const std::vector<PollutantData>& data)
{
    QLineSeries *series = new QLineSeries();
    series->setName("PFAS Levels");

    std::map<QDateTime, double> sortedData;
    for(const auto& point : data) {
        QDateTime dateTime = QDateTime::fromString(point.sampleDateTime, "yyyy-MM-dd HH:mm:ss");
        sortedData[dateTime] = point.result;
    }

    for(const auto& [date, value] : sortedData) {
        series->append(date.toMSecsSinceEpoch(), value);
    }

    if (chartView && chartView->chart()) {
        chartView->chart()->addSeries(series);
        series->attachAxis(chartView->chart()->axes(Qt::Horizontal).first());
        series->attachAxis(chartView->chart()->axes(Qt::Vertical).first());
    }
}

void FluorinatedCompounds::setupChart()
{
    QChart *chart = new QChart();
    chart->setTitle("PFAS Levels Over Time");

    QDateTime startDate = QDateTime::currentDateTime().addMonths(-6);

    // Add threshold line
    QLineSeries *threshold = new QLineSeries();
    threshold->setName("Safety Threshold");
    threshold->setPen(QPen(Qt::red, 2, Qt::DashLine));
    threshold->append(startDate.toMSecsSinceEpoch(), PFAS_THRESHOLD);
    threshold->append(QDateTime::currentDateTime().toMSecsSinceEpoch(), PFAS_THRESHOLD);
    chart->addSeries(threshold);

    // Setup axes
    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setFormat("MMM yyyy");
    axisX->setTitleText("Time Period");
    chart->addAxis(axisX, Qt::AlignBottom);

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText("PFAS Level (µg/L)");
    axisY->setRange(0, 0.2);
    chart->addAxis(axisY, Qt::AlignLeft);

    threshold->attachAxis(axisX);
    threshold->attachAxis(axisY);

    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
}

void FluorinatedCompounds::handleSeriesHovered(const QPointF &point, bool state)
{
    if (state) {
        QDateTime pointDate = QDateTime::fromMSecsSinceEpoch(point.x());
        QString status = point.y() > PFAS_THRESHOLD ? "Exceeds" : "Within";
        QString impact = point.y() > PFAS_THRESHOLD ?
                             "High Risk - Remediation Required" : "Low Risk - Continue Monitoring";

        QString tooltipText = QString(
                                  "Date: %1\n"
                                  "PFAS Level: %2 µg/L\n"
                                  "Status: %3 threshold\n"
                                  "Environmental Impact: %4\n"
                                  "Persistence: High - Bioaccumulative"
                                  ).arg(pointDate.toString("MMM yyyy"))
                                  .arg(point.y(), 0, 'f', 3)
                                  .arg(status)
                                  .arg(impact);

        QToolTip::showText(QCursor::pos(), tooltipText);
    }
}

FluorinatedCompounds::~FluorinatedCompounds()
{
    delete ui;
}
