#include "compliance_dashboard.hpp"
#include <QHBoxLayout>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QFile>
#include <QTextStream>
#include <QDebug>

ComplianceDashboard::ComplianceDashboard(QWidget* parent) : QWidget(parent)
{
    // Create filters
    locationFilter = new QComboBox();
    locationFilter->addItem("All Locations");

    pollutantFilter = new QComboBox();
    pollutantFilter->addItem("All Pollutants");

    statusFilter = new QComboBox();
    statusFilter->addItem("All Statuses");
    statusFilter->addItem("Compliant");
    statusFilter->addItem("Non-Compliant");

    // Create compliance list
    complianceList = new QListWidget();

    // Connect item click signal
    connect(complianceList, &QListWidget::itemClicked, this, &ComplianceDashboard::onItemClicked);

    // Create refresh button
    refreshButton = new QPushButton("Refresh");
    connect(refreshButton, &QPushButton::clicked, this, &ComplianceDashboard::onRefreshClicked);

    // Layout
    QVBoxLayout* mainLayout = new QVBoxLayout();
    QHBoxLayout* filterLayout = new QHBoxLayout();

    filterLayout->addWidget(locationFilter);
    filterLayout->addWidget(pollutantFilter);
    filterLayout->addWidget(statusFilter);

    mainLayout->addLayout(filterLayout);
    mainLayout->addWidget(complianceList);
    mainLayout->addWidget(refreshButton);

    setLayout(mainLayout);

    // Load data from the CSV and populate the compliance list
    loadDataFromCSV("data.csv");
    populateComplianceList();
}

void ComplianceDashboard::loadDataFromCSV(const QString& filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Unable to open file:" << filePath;
        return;
    }

    QTextStream in(&file);
    QString headerLine = in.readLine(); // Read the header line
    QStringList headers = headerLine.split(',');

    // Clear any existing data
    data.clear();

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');

        if (fields.size() != headers.size()) {
            continue; // Skip malformed rows
        }

        QMap<QString, QString> row;
        for (int i = 0; i < headers.size(); ++i) {
            row[headers[i]] = fields[i];
        }
        data.append(row);
    }

    file.close();
    updateFilters();
}

void ComplianceDashboard::populateComplianceList()
{
    complianceList->clear();

    for (const auto& row : data) {
        QString location = row["sample.samplingPoint.label"];
        QString pollutant = row["determinand.label"];
        double value = row["result"].toDouble();

        QString complianceStatus;
        if (value <= 50) {
            complianceStatus = "Compliant";
        } else if (value <= 150) {
            complianceStatus = "Moderate";
        } else {
            complianceStatus = "Non-Compliant";
        }

        // Apply filters
        if (!matchesFilters(location, pollutant, complianceStatus)) {
            continue;
        }

        // Create a list item if it matches the filters
        QListWidgetItem* item = new QListWidgetItem(
            QString("%1 - %2: %3")
                .arg(location)
                .arg(pollutant)
                .arg(value, 0, 'f', 2)
        );

        if (complianceStatus == "Compliant") {
            item->setBackground(Qt::green);
            item->setText(item->text() + " - Compliant");
        } else if (complianceStatus == "Moderate") {
            item->setBackground(Qt::yellow);
            item->setText(item->text() + " - Moderate");
        } else {
            item->setBackground(Qt::red);
            item->setText(item->text() + " - Non-Compliant");
        }

        complianceList->addItem(item);
    }
}



void ComplianceDashboard::updateFilters()
{
    QSet<QString> locations;
    QSet<QString> pollutants;

    for (const auto& row : data) {
        locations.insert(row["sample.samplingPoint.label"]);
        pollutants.insert(row["determinand.label"]);
    }

    locationFilter->clear();
    locationFilter->addItem("All Locations");
    for (const QString& location : locations) {
        locationFilter->addItem(location);
    }

    pollutantFilter->clear();
    pollutantFilter->addItem("All Pollutants");
    for (const QString& pollutant : pollutants) {
        pollutantFilter->addItem(pollutant);
    }
}

bool ComplianceDashboard::matchesFilters(const QString& location, const QString& pollutant, const QString& compliance)
{
    QString selectedLocation = locationFilter->currentText();
    if (selectedLocation != "All Locations" && location != selectedLocation) {
        return false;
    }

    QString selectedPollutant = pollutantFilter->currentText();
    if (selectedPollutant != "All Pollutants" && pollutant != selectedPollutant) {
        return false;
    }

    QString selectedStatus = statusFilter->currentText();
    if (selectedStatus == "Compliant" && compliance != "Compliant") {
        return false;
    }
    if (selectedStatus == "Moderate" && compliance != "Moderate") {
        return false;
    }
    if (selectedStatus == "Non-Compliant" && compliance != "Non-Compliant") {
        return false;
    }

    return true;
}


void ComplianceDashboard::onItemClicked(QListWidgetItem* item)
{
    QString details = "Detailed information about:\n" + item->text();
    QMessageBox::information(this, "Compliance Details", details);
}

void ComplianceDashboard::onRefreshClicked()
{
    populateComplianceList();
}
