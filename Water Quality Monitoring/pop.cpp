#include "pop.hpp"
#include <QtCharts/QLineSeries>
#include <QPushButton>
#include <QFile>
#include <QDir>
#include <QDebug>

popWindow::popWindow(QWidget *parent) : QMainWindow(parent)
{
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);
    mainLayout = new QVBoxLayout(centralWidget);

    QHBoxLayout* controlLayout = new QHBoxLayout();

    pollutantComboBox = new QComboBox();
    locationComboBox = new QComboBox();
    locationComboBox->setEditable(true);
    connect(locationComboBox, &QComboBox::currentTextChanged, this, &popWindow::updateDateComboBoxes);

    startDateComboBox = new QComboBox();
    endDateComboBox = new QComboBox();

    controlLayout->addWidget(new QLabel(tr("Pollutant:")));
    controlLayout->addWidget(pollutantComboBox);
    controlLayout->addWidget(new QLabel(tr("Location:")));
    controlLayout->addWidget(locationComboBox);
    controlLayout->addWidget(new QLabel(tr("Start Date:")));
    controlLayout->addWidget(startDateComboBox);
    controlLayout->addWidget(new QLabel(tr("End Date:")));
    controlLayout->addWidget(endDateComboBox);

    QPushButton* updateButton = new QPushButton(tr("Update Chart"));
    connect(updateButton, &QPushButton::clicked, this, &popWindow::updateChart);
    controlLayout->addWidget(updateButton);

    mainLayout->addLayout(controlLayout);

    mainChartView = new QChartView();
    mainChartView->setMinimumHeight(400);
    mainLayout->addWidget(mainChartView);

    loadPopData();
    populateComboBoxes();
}

popWindow::~popWindow() {}

void popWindow::loadPopData()
{
    csv::CSVReader reader("data.csv");
    const auto &data = dataManager.getData();

    for (csv::CSVRow& row : reader) {
        PopData pollutant{
            QString::fromStdString(row["determinand.definition"].get<std::string>()),
            QString::fromStdString(row["sample.samplingPoint.label"].get<std::string>()),
            QString::fromStdString(row["sample.sampleDateTime"].get<std::string>()),
            row["result"].get<double>()
        };
        dataCache.push_back(pollutant);
        qDebug() << "Loaded:" << pollutant.determinandDefinition
                 << pollutant.samplingPoint
                 << pollutant.sampleDateTime
                 << pollutant.result;
    }
}

void popWindow::populateComboBoxes()
{
    std::set<QString> pollutants;
    std::set<QString> locations;
    std::set<QString> dates;

    for (const auto& data : dataCache) {
        pollutants.insert(data.determinandDefinition);
        locations.insert(data.samplingPoint);
        dates.insert(data.sampleDateTime.split('T')[0]);
    }

    pollutantComboBox->addItems(QStringList(pollutants.begin(), pollutants.end()));
    locationComboBox->addItems(QStringList(locations.begin(), locations.end()));
    startDateComboBox->addItems(QStringList(dates.begin(), dates.end()));
    endDateComboBox->addItems(QStringList(dates.begin(), dates.end()));
}

void popWindow::updateDateComboBoxes(const QString& location)
{
    startDateComboBox->clear();
    endDateComboBox->clear();

    std::set<QString> dates;
    for (const auto& data : dataCache) {
        if (data.samplingPoint == location) {
            dates.insert(data.sampleDateTime.split('T')[0]);
        }
    }

    startDateComboBox->addItems(QStringList(dates.begin(), dates.end()));
    endDateComboBox->addItems(QStringList(dates.begin(), dates.end()));

    if (endDateComboBox->count() > 0) {
        endDateComboBox->setCurrentIndex(endDateComboBox->count() - 1);
    }
}

void popWindow::updateChart()
{
    QString selectedPollutant = pollutantComboBox->currentText();
    QString selectedLocation = locationComboBox->currentText();
    QString startDate = startDateComboBox->currentText();
    QString endDate = endDateComboBox->currentText();

    QLineSeries *series = new QLineSeries();
    QLineSeries *thresholdLine = new QLineSeries();

    series->setPen(QPen(Qt::blue, 2));
    thresholdLine->setPen(QPen(Qt::red, 2, Qt::DashLine));

    QMap<QString, double> safetyThresholds = {
        {"Lead", 0.5},
        {"Mercury", 1.0},
        {"PCB", 0.5},
        {"Dioxins", 0.1}
    };

    QMap<QDateTime, double> sortedData;
    double threshold = safetyThresholds.value(selectedPollutant, 1.0);

    for (const auto& data : dataCache) {
        if (data.determinandDefinition == selectedPollutant &&
            data.samplingPoint == selectedLocation) {
            QString dateStr = data.sampleDateTime.split('T')[0];
            if (dateStr >= startDate && dateStr <= endDate) {
                QDateTime date = QDateTime::fromString(dateStr, "yyyy-MM-dd");
                if (date.isValid()) {
                    sortedData[date] = data.result;
                }
            }
        }
    }

    double minY = std::numeric_limits<double>::max();
    double maxY = std::numeric_limits<double>::min();

    for (auto it = sortedData.begin(); it != sortedData.end(); ++it) {
        series->append(it.key().toMSecsSinceEpoch(), it.value());
        minY = qMin(minY, it.value());
        maxY = qMax(maxY, it.value());
    }

    for (auto it = sortedData.begin(); it != sortedData.end(); ++it) {
        series->append(it.key().toMSecsSinceEpoch(), it.value());
        qDebug() << "Adding point:" << it.key() << it.value();
    }

    if (!sortedData.isEmpty()) {
        QDateTime firstDate = sortedData.firstKey();
        QDateTime lastDate = sortedData.lastKey();
        thresholdLine->append(firstDate.toMSecsSinceEpoch(), threshold);
        thresholdLine->append(lastDate.toMSecsSinceEpoch(), threshold);
        qDebug() << "Threshold line points:" << firstDate << lastDate << threshold;
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->addSeries(thresholdLine);

    QString healthInfo = getHealthRiskInfo(selectedPollutant);

    if (healthInfoLabel) {
        mainLayout->removeWidget(healthInfoLabel);
        delete healthInfoLabel;
    }

    healthInfoLabel = new QLabel(healthInfo);
    healthInfoLabel->setWordWrap(true);
    mainLayout->addWidget(healthInfoLabel);

    QDateTimeAxis *axisX = new QDateTimeAxis;
    axisX->setFormat("yyyy-MM-dd");
    axisX->setTitleText(tr("Date"));

    QDateTime startDateTime = QDateTime::fromString(startDate, "yyyy-MM-dd");
    QDateTime endDateTime = QDateTime::fromString(endDate, "yyyy-MM-dd");
    axisX->setRange(startDateTime, endDateTime.addDays(1));

    QValueAxis *axisY = new QValueAxis;
    axisY->setTitleText(tr("Concentration (μg/m³)"));
    axisY->setRange(qMin(minY * 0.9, threshold * 0.9), qMax(maxY * 1.1, threshold * 1.1));

    chart->addAxis(axisX, Qt::AlignBottom);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisX);
    series->attachAxis(axisY);
    thresholdLine->attachAxis(axisX);
    thresholdLine->attachAxis(axisY);

    series->setName(tr("Measured Levels"));
    thresholdLine->setName(tr("Safety Threshold"));

    chart->setTitle(QString(tr("%1 Levels at %2")).arg(selectedPollutant).arg(selectedLocation));
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignBottom);

    mainChartView->setChart(chart);
}

QString popWindow::getHealthRiskInfo(const QString& pollutant)
{
    QMap<QString, QString> healthInfo = {
        {"Lead", tr("Health Risks: Neurological damage, developmental issues, kidney problems\n"
                    "Monitoring: Essential for protecting vulnerable populations\n"
                    "Safety Level: 0.5 μg/m³ (WHO guideline)")},
        {"Mercury", tr("Health Risks: Nervous system damage, cognitive impairment\n"
                       "Monitoring: Critical for aquatic ecosystem protection\n"
                       "Safety Level: 1.0 μg/m³ (Environmental standard)")},
        {"PCB", tr("Health Risks: Cancer, immune system effects, reproductive issues\n"
                   "Monitoring: Important for long-term environmental tracking\n"
                   "Safety Level: 0.5 μg/m³ (Regulatory limit)")},
        {"Dioxins", tr("Health Risks: Cancer, developmental effects, hormone disruption\n"
                       "Monitoring: Crucial for food chain contamination prevention\n"
                       "Safety Level: 0.1 μg/m³ (International standard)")},
        {"Endrin", tr("Health Risks: Nervous system effects, seizures\n"
                      "Monitoring: Essential for pesticide contamination tracking\n"
                      "Safety Level: 0.02 μg/L (EPA guideline)")},
        {"Phenoxyacetic acid", tr("Health Risks: Eye and skin irritation, potential endocrine disruption\n"
                                  "Monitoring: Required for agricultural runoff\n"
                                  "Safety Level: 0.1 μg/L (Regulatory standard)")},
        {"Manganese", tr("Health Risks: Neurological effects, especially in children\n"
                         "Monitoring: Important for drinking water quality\n"
                         "Safety Level: 0.4 mg/L (WHO guideline)")},
        {"Nitrogen", tr("Health Risks: Eutrophication in water bodies, nitrate poisoning\n"
                        "Monitoring: Critical for agricultural runoff management\n"
                        "Safety Level: 10 mg/L as NO3 (WHO guideline)")},
        {"Sodium", tr("Health Risks: Hypertension, cardiovascular issues (in excess)\n"
                      "Monitoring: Useful for drinking water quality\n"
                      "Safety Level: 200 mg/L (WHO guideline)")},
        {"Dichlorvos", tr("Health Risks: Nervous system toxicity, potential carcinogen\n"
                          "Monitoring: Essential for pesticide contamination control\n"
                          "Safety Level: 0.01 μg/L (Regulatory limit)")},
        {"Chlorotoluron", tr("Health Risks: Endocrine disruption, potential toxicity to aquatic life\n"
                             "Monitoring: Required for agricultural pesticide monitoring\n"
                             "Safety Level: 0.3 μg/L (EU standard)")},
        {"Trifluralin", tr("Health Risks: Potential carcinogen, endocrine disruption\n"
                           "Monitoring: Necessary for agricultural runoff tracking\n"
                           "Safety Level: 0.05 μg/L (EPA guideline)")},
        {"Heptachlor", tr("Health Risks: Liver toxicity, potential carcinogen\n"
                          "Monitoring: Important for pesticide residue analysis\n"
                          "Safety Level: 0.01 μg/L (WHO guideline)")},
        {"Naphthalene", tr("Health Risks: Hemolytic anemia, respiratory issues\n"
                           "Monitoring: Important for air and water quality\n"
                           "Safety Level: 0.2 μg/m³ (WHO guideline)")},
        {"Cyanide", tr("Health Risks: Acute toxicity, respiratory failure\n"
                       "Monitoring: Critical for industrial discharge tracking\n"
                       "Safety Level: 0.05 mg/L (WHO guideline)")},
        {"Chloridazon", tr("Health Risks: Endocrine disruption, aquatic toxicity\n"
                           "Monitoring: Required for herbicide residue monitoring\n"
                           "Safety Level: 0.1 μg/L (Regulatory limit)")},
        {"Copper", tr("Health Risks: Gastrointestinal distress, liver toxicity (in excess)\n"
                      "Monitoring: Important for water safety\n"
                      "Safety Level: 2.0 mg/L (WHO guideline)")},
        {"Zinc", tr("Health Risks: Gastrointestinal irritation (in high concentrations)\n"
                    "Monitoring: Useful for drinking water and industrial discharge\n"
                    "Safety Level: 3.0 mg/L (WHO guideline)")}
    };

    return healthInfo.value(pollutant, tr("Information not available for this pollutant."));
}
