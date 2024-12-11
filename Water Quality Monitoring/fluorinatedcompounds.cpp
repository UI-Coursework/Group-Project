#include "fluorinatedcompounds.hpp"
#include "ui_fluorinatedcompounds.h"
#include <QVBoxLayout>
#include <QDateTime>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QToolTip>
#include <set>

const double FluorinatedCompounds::PFAS_THRESHOLD = 0.1;

FluorinatedCompounds::FluorinatedCompounds(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::FluorinatedCompounds)
    , axisX(nullptr)
    , axisY(nullptr) {
    ui->setupUi(this);
    setWindowTitle(tr("PFAS Monitoring Dashboard"));
    setupUI();
    loadData();
}

void FluorinatedCompounds::setupUI() {
    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    QVBoxLayout* leftColumn = new QVBoxLayout();
    QGroupBox* searchCard = new QGroupBox(tr("Search and Filter"));
    QVBoxLayout* searchLayout = new QVBoxLayout(searchCard);

    locationComboBox = new QComboBox();
    locationComboBox->setEditable(true);
    connect(locationComboBox, &QComboBox::currentTextChanged,
            this, &FluorinatedCompounds::updateDateComboBoxes);

    searchLayout->addWidget(new QLabel(tr("Location:")));
    searchLayout->addWidget(locationComboBox);

    QHBoxLayout* dateLayout = new QHBoxLayout();
    startDateComboBox = new QComboBox();
    endDateComboBox = new QComboBox();

    dateLayout->addWidget(new QLabel(tr("Start Date:")));
    dateLayout->addWidget(startDateComboBox);
    dateLayout->addWidget(new QLabel(tr("End Date:")));
    dateLayout->addWidget(endDateComboBox);
    searchLayout->addLayout(dateLayout);

    loadButton = new QPushButton(tr("Load Data"));
    connect(loadButton, &QPushButton::clicked,
            this, &FluorinatedCompounds::onLoadButtonClicked);
    searchLayout->addWidget(loadButton);
    leftColumn->addWidget(searchCard);

    detailsTable = new QTableWidget();
    detailsTable->setColumnCount(3);
    detailsTable->setHorizontalHeaderLabels({tr("Date"), tr("Value"), tr("Status")});
    detailsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    detailsTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    detailsTable->setMinimumHeight(200);
    leftColumn->addWidget(detailsTable);

    mainLayout->addLayout(leftColumn);

    chart = new QChart();
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(600, 400);

    QVBoxLayout* rightColumn = new QVBoxLayout();
    rightColumn->addWidget(chartView);
    mainLayout->addLayout(rightColumn);
}

void FluorinatedCompounds::loadData() {
    csv::CSVReader reader("data.csv");
    dataCache.clear();
    std::set<QString> locations;

    for (csv::CSVRow& row : reader) {
        PFASData data{
            QString::fromStdString(row["sample.samplingPoint.label"].get<std::string>()),
            QString::fromStdString(row["sample.sampleDateTime"].get<std::string>()).split('T')[0],
            row["result"].get<double>()
        };
        dataCache.push_back(data);
        locations.insert(data.location);
    }

    locationComboBox->addItems(QStringList(locations.begin(), locations.end()));
    if (locationComboBox->count() > 0) {
        locationComboBox->setCurrentIndex(0);
    }
}

void FluorinatedCompounds::clearAxes() {
    if (axisX) {
        chart->removeAxis(axisX);
        delete axisX;
        axisX = nullptr;
    }
    if (axisY) {
        chart->removeAxis(axisY);
        delete axisY;
        axisY = nullptr;
    }
}

void FluorinatedCompounds::updateChart() {
    clearAxes();
    chart->removeAllSeries();

    QLineSeries *series = new QLineSeries();
    QLineSeries *threshold = new QLineSeries();

    QString selectedLocation = locationComboBox->currentText();
    QString startDate = startDateComboBox->currentText();
    QString endDate = endDateComboBox->currentText();

    QDateTime startDateTime = QDateTime::fromString(startDate, "yyyy-MM-dd");
    QDateTime endDateTime = QDateTime::fromString(endDate, "yyyy-MM-dd");

    QMap<QDateTime, double> sortedData;

    for (const auto& data : dataCache) {
        if (data.location == selectedLocation &&
            data.date >= startDate &&
            data.date <= endDate) {
            QDateTime dateTime = QDateTime::fromString(data.date, "yyyy-MM-dd");
            sortedData[dateTime] = data.value;
        }
    }

    for (auto it = sortedData.begin(); it != sortedData.end(); ++it) {
        series->append(it.key().toMSecsSinceEpoch(), it.value());
    }

    threshold->append(startDateTime.toMSecsSinceEpoch(), PFAS_THRESHOLD);
    threshold->append(endDateTime.toMSecsSinceEpoch(), PFAS_THRESHOLD);
    threshold->setPen(QPen(Qt::red, 2, Qt::DashLine));

    axisX = new QDateTimeAxis;
    axisX->setFormat("dd-MM-yyyy");
    axisX->setTitleText(tr("Date"));
    axisX->setRange(startDateTime, endDateTime.addDays(1));

    axisY = new QValueAxis;
    axisY->setTitleText(tr("PFAS Level (µg/L)"));
    axisY->setRange(0, 0.2);

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);

    chart->addSeries(series);
    chart->addSeries(threshold);

    series->attachAxis(axisX);
    series->attachAxis(axisY);
    threshold->attachAxis(axisX);
    threshold->attachAxis(axisY);

    series->setName(tr("PFAS Measurements"));
    series->setPen(QPen(Qt::blue, 2));
    threshold->setName(tr("Threshold (0.1 µg/L)"));

    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    connect(series, &QLineSeries::hovered,
            this, &FluorinatedCompounds::handleSeriesHovered);

    chart->setTitle(tr("PFAS Levels at %1").arg(selectedLocation));
}

void FluorinatedCompounds::updateDateComboBoxes(const QString& location) {
    startDateComboBox->clear();
    endDateComboBox->clear();

    std::set<QString> dates;
    for (const auto& data : dataCache) {
        if (data.location == location) {
            dates.insert(data.date);
        }
    }

    startDateComboBox->addItems(QStringList(dates.begin(), dates.end()));
    endDateComboBox->addItems(QStringList(dates.begin(), dates.end()));

    if (endDateComboBox->count() > 0) {
        endDateComboBox->setCurrentIndex(endDateComboBox->count() - 1);
    }
}

void FluorinatedCompounds::updateLocationComboBox() {
    locationComboBox->clear();
    std::set<QString> locations;

    for (const auto& data : dataCache) {
        locations.insert(data.location);
    }

    locationComboBox->addItems(QStringList(locations.begin(), locations.end()));
    if (locationComboBox->count() > 0) {
        locationComboBox->setCurrentIndex(0);
    }
}

void FluorinatedCompounds::updateDetailsTable() {
    detailsTable->setRowCount(0);

    QString selectedLocation = locationComboBox->currentText();
    QString startDate = startDateComboBox->currentText();
    QString endDate = endDateComboBox->currentText();

    for (const auto& data : dataCache) {
        if (data.location == selectedLocation &&
            data.date >= startDate &&
            data.date <= endDate) {
            int row = detailsTable->rowCount();
            detailsTable->insertRow(row);

            QTableWidgetItem* dateItem = new QTableWidgetItem(data.date);
            dateItem->setTextAlignment(Qt::AlignCenter);
            detailsTable->setItem(row, 0, dateItem);

            QTableWidgetItem* valueItem = new QTableWidgetItem(
                QString::number(data.value));
            valueItem->setTextAlignment(Qt::AlignCenter);
            detailsTable->setItem(row, 1, valueItem);

            QString status = data.value > PFAS_THRESHOLD ? tr("Exceeds") : tr("Within Limits");
            QTableWidgetItem* statusItem = new QTableWidgetItem(status);
            statusItem->setTextAlignment(Qt::AlignCenter);
            detailsTable->setItem(row, 2, statusItem);
        }
    }
}

void FluorinatedCompounds::handleSeriesHovered(const QPointF &point, bool state) {
    if (state) {
        QDateTime pointDate = QDateTime::fromMSecsSinceEpoch(point.x());
        QString status = point.y() > PFAS_THRESHOLD ? tr("Exceeds") : tr("Within");
        QString tooltipText = tr("Date: %1\nPFAS Level: %2 µg/L\nStatus: %3 threshold")
                                  .arg(pointDate.toString("dd-MM-yyyy"))
                                  .arg(point.y(), 0, 'f', 3)
                                  .arg(status);
        QToolTip::showText(QCursor::pos(), tooltipText);
    }
}

void FluorinatedCompounds::onLoadButtonClicked() {
    updateChart();
    updateDetailsTable();
}

FluorinatedCompounds::~FluorinatedCompounds() {
    delete ui;
}
