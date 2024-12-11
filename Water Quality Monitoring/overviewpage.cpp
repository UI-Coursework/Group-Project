#include "overviewpage.hpp"
#include "csv.hpp"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDateTime>
#include <set>

OverviewPage::OverviewPage(QWidget* parent)
    : QWidget(parent)
    , isLineChart(false)
    , axisX(nullptr)
    , axisY(nullptr)
    , barAxisX(nullptr)
    , tooltip(new ChartTooltip()) {
    setupUI();
    loadData();
    chartView->scene()->addItem(tooltip);
    tooltip->setVisible(false);
}

void OverviewPage::setupUI() {
    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    // Left Column
    QVBoxLayout* leftColumn = new QVBoxLayout();

    // Search and Filter Section
    QGroupBox* searchCard = new QGroupBox(tr("Search and Filter"));
    QVBoxLayout* searchCardLayout = new QVBoxLayout(searchCard);

    pollutantComboBox = new QComboBox();
    pollutantComboBox->setEditable(true);
    connect(pollutantComboBox, &QComboBox::currentTextChanged,
        this, &OverviewPage::updateLocationComboBox);

    searchCardLayout->addWidget(new QLabel(tr("Search:")));
    searchCardLayout->addWidget(pollutantComboBox);

    locationComboBox = new QComboBox();
    connect(locationComboBox, &QComboBox::currentTextChanged,
        this, &OverviewPage::updateDateComboBoxes);

    searchCardLayout->addWidget(new QLabel(tr("Location:")));
    searchCardLayout->addWidget(locationComboBox);

    QHBoxLayout* dateLayout = new QHBoxLayout();
    startDateComboBox = new QComboBox();
    endDateComboBox = new QComboBox();

    dateLayout->addWidget(new QLabel(tr("Start Date:")));
    dateLayout->addWidget(startDateComboBox);
    dateLayout->addWidget(new QLabel(tr("End Date:")));
    dateLayout->addWidget(endDateComboBox);

    searchCardLayout->addLayout(dateLayout);

    // Add Load Button
    QPushButton* loadButton = new QPushButton(tr("Load Data"));
    connect(loadButton, &QPushButton::clicked, this, &OverviewPage::onLoadButtonClicked);
    searchCardLayout->addWidget(loadButton);

    leftColumn->addWidget(searchCard);

    // Details Table
    detailsTable = new QTableWidget();
    detailsTable->setColumnCount(3);
    detailsTable->setHorizontalHeaderLabels({ tr("Date"), tr("Value"), tr("Status") });
    detailsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    detailsTable->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    detailsTable->setMinimumHeight(200);

    leftColumn->addWidget(detailsTable);

    mainLayout->addLayout(leftColumn);

    // Right Column
    QVBoxLayout* rightColumn = new QVBoxLayout();

    chart = new QChart();
    chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    toggleChartButton = new QPushButton(tr("Switch to Line Chart"));
    connect(toggleChartButton, &QPushButton::clicked, this, &OverviewPage::toggleChartType);

    rightColumn->addWidget(chartView);
    rightColumn->addWidget(toggleChartButton);

    mainLayout->addLayout(rightColumn);

    setLayout(mainLayout);
}

void OverviewPage::loadData() {
    csv::CSVReader reader("data.csv");
    dataCache.clear();

    std::set<QString> pollutants;

    for (csv::CSVRow& row : reader) {
        overviewData data{
            QString::fromStdString(row["determinand.definition"].get<std::string>()),
            QString::fromStdString(row["sample.samplingPoint.label"].get<std::string>()),
            QString::fromStdString(row["sample.sampleDateTime"].get<std::string>()).split('T')[0],
            row["result"].get<double>()
        };
        dataCache.push_back(data);
        pollutants.insert(data.pollutant);
    }

    pollutantComboBox->clear();
    for (const QString& pollutant : pollutants) {
        pollutantComboBox->addItem(pollutant);
    }
}

void OverviewPage::clearAxes() {
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
    if (barAxisX) {
        chart->removeAxis(barAxisX);
        delete barAxisX;
        barAxisX = nullptr;
    }
}

void OverviewPage::updateChart() {
    clearAxes();
    chart->removeAllSeries();

    QString selectedPollutant = pollutantComboBox->currentText();
    QString selectedLocation = locationComboBox->currentText();
    QString startDate = startDateComboBox->currentText();
    QString endDate = endDateComboBox->currentText();

    if (isLineChart) {
        QLineSeries* series = new QLineSeries();

        for (const auto& data : dataCache) {
            if (data.pollutant == selectedPollutant &&
                data.location == selectedLocation &&
                data.date >= startDate &&
                data.date <= endDate) {

                QDateTime dateTime = QDateTime::fromString(data.date, "yyyy-MM-dd");
                if (dateTime.isValid()) {
                    series->append(dateTime.toMSecsSinceEpoch(), data.value);
                }
            }
        }

        chart->addSeries(series);

        axisX = new QDateTimeAxis;
        axisX->setFormat("dd-MM-yyyy");
        axisX->setTitleText("Date");
        chart->addAxis(axisX, Qt::AlignBottom);
        series->attachAxis(axisX);

        axisY = new QValueAxis;
        axisY->setTitleText("Pollutant Value");
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        connect(series, &QLineSeries::hovered, this, [=](const QPointF& point, bool state) {
            if (state) {
                QDateTime dateTime = QDateTime::fromMSecsSinceEpoch(static_cast<qint64>(point.x()));
                QString tooltipText = QString("Date: %1\nValue: %2").arg(dateTime.toString("dd-MM-yyyy")).arg(point.y());
                tooltip->setText(tooltipText);
                tooltip->setPos(chartView->mapToScene(chartView->mapFromGlobal(QCursor::pos())));
                tooltip->setVisible(true);
            }
            else {
                tooltip->setVisible(false);
            }
            });
    }
    else {
        QBarSeries* series = new QBarSeries();
        QBarSet* barSet = new QBarSet("Values");

        QStringList dates;
        for (const auto& data : dataCache) {
            if (data.pollutant == selectedPollutant &&
                data.location == selectedLocation &&
                data.date >= startDate &&
                data.date <= endDate) {

                dates << data.date;
                *barSet << data.value;
            }
        }

        series->append(barSet);
        chart->addSeries(series);

        barAxisX = new QBarCategoryAxis();
        barAxisX->append(dates);
        chart->addAxis(barAxisX, Qt::AlignBottom);
        series->attachAxis(barAxisX);

        axisY = new QValueAxis;
        axisY->setTitleText("Pollutant Value");
        chart->addAxis(axisY, Qt::AlignLeft);
        series->attachAxis(axisY);

        connect(series, &QBarSeries::hovered, this, [=](bool status, int index, QBarSet* barset) {
            if (status) {
                QString tooltipText = QString("Date: %1\nValue: %2").arg(dates[index]).arg(barset->at(index));
                tooltip->setText(tooltipText);
                tooltip->setPos(chartView->mapToScene(chartView->mapFromGlobal(QCursor::pos())));
                tooltip->setVisible(true);
            }
            else {
                tooltip->setVisible(false);
            }
            });
    }

    chart->setTitle(QString("%1 Measurements at %2")
        .arg(selectedPollutant)
        .arg(selectedLocation));
    chart->legend()->setVisible(false);
}

void OverviewPage::updateDetailsTable() {
    detailsTable->setRowCount(0);

    QString selectedPollutant = pollutantComboBox->currentText();
    QString selectedLocation = locationComboBox->currentText();
    QString startDate = startDateComboBox->currentText();
    QString endDate = endDateComboBox->currentText();

    for (const auto& data : dataCache) {
        if (data.pollutant == selectedPollutant &&
            data.location == selectedLocation &&
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

            QTableWidgetItem* emptyItem = new QTableWidgetItem();
            emptyItem->setTextAlignment(Qt::AlignCenter);
            detailsTable->setItem(row, 2, emptyItem);
        }
    }
}

void OverviewPage::onLoadButtonClicked() {
    updateDetailsTable();
    updateChart();
}

void OverviewPage::toggleChartType() {
    isLineChart = !isLineChart;
    toggleChartButton->setText(isLineChart ?
        tr("Switch to Bar Chart") : tr("Switch to Line Chart"));
    updateChart();
}

void OverviewPage::updateLocationComboBox(const QString& pollutant) {
    locationComboBox->clear();

    std::set<QString> locations;
    for (const auto& data : dataCache) {
        if (data.pollutant == pollutant) {
            locations.insert(data.location);
        }
    }

    for (const QString& location : locations) {
        locationComboBox->addItem(location);
    }
}

void OverviewPage::updateDateComboBoxes(const QString& location) {
    startDateComboBox->clear();
    endDateComboBox->clear();

    std::set<QString> dates;
    QString selectedPollutant = pollutantComboBox->currentText();

    for (const auto& data : dataCache) {
        if (data.pollutant == selectedPollutant && data.location == location) {
            dates.insert(data.date);
        }
    }

    for (const QString& date : dates) {
        startDateComboBox->addItem(date);
        endDateComboBox->addItem(date);
    }
}
