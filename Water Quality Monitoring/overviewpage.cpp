#include "overviewpage.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QSet>

OverviewPage::OverviewPage(QWidget* parent) : QWidget(parent) {
    setupUI();
    loadData();
}

void OverviewPage::setupUI() {
    QHBoxLayout* mainLayout = new QHBoxLayout(this);

    // Left Column
    QVBoxLayout* leftLayout = new QVBoxLayout();
    leftLayout->addWidget(new QLabel("<h2>Water Quality Samples</h2>"));

    leftLayout->addWidget(new QLabel("Select Location:"));
    locationComboBox = new QComboBox();
    leftLayout->addWidget(locationComboBox);
    connect(locationComboBox, &QComboBox::currentTextChanged,
        this, &OverviewPage::onLocationSelected);

    leftLayout->addWidget(new QLabel("Select Determinand:"));
    determinandComboBox = new QComboBox();
    leftLayout->addWidget(determinandComboBox);
    connect(determinandComboBox, &QComboBox::currentTextChanged,
        this, &OverviewPage::onDeterminandSelected);

    leftLayout->addWidget(new QLabel("Select Date and Time:"));
    dateTimeComboBox = new QComboBox();
    leftLayout->addWidget(dateTimeComboBox);
    connect(dateTimeComboBox, &QComboBox::currentTextChanged,
        this, &OverviewPage::onDateTimeSelected);

    leftLayout->addStretch();

    // Right Column
    QVBoxLayout* rightLayout = new QVBoxLayout();
    rightLayout->addWidget(new QLabel("<h3>Sample Details</h3>"));

    dataTable = new QTableWidget();
    dataTable->setColumnCount(2);
    dataTable->setHorizontalHeaderLabels({ "Field", "Value" });
    dataTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    dataTable->verticalHeader()->setVisible(false);
    dataTable->setAlternatingRowColors(true);
    dataTable->setShowGrid(true);
    rightLayout->addWidget(dataTable);

    mainLayout->addLayout(leftLayout, 1);
    mainLayout->addLayout(rightLayout, 2);
}

void OverviewPage::loadData() {
    QFile file("data.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", "Unable to open the data file.");
        return;
    }

    QTextStream in(&file);
    headers = in.readLine().split(",");

    QSet<QString> uniqueLocations;
    while (!in.atEnd()) {
        QStringList fields = in.readLine().split(",");
        if (fields.size() != headers.size()) continue;

        QString location = fields[headers.indexOf("sample.samplingPoint.label")];
        uniqueLocations.insert(location);
        records[fields[headers.indexOf("@id")]] = fields;
    }

    locationComboBox->addItems(uniqueLocations.values());
    file.close();
}

void OverviewPage::onLocationSelected(const QString& location) {
    determinandComboBox->clear();
    dateTimeComboBox->clear();

    QSet<QString> filteredDeterminands;
    for (const auto& fields : records) {
        if (fields[headers.indexOf("sample.samplingPoint.label")] == location) {
            filteredDeterminands.insert(fields[headers.indexOf("determinand.label")]);
        }
    }

    determinandComboBox->addItems(filteredDeterminands.values());
}

void OverviewPage::onDeterminandSelected(const QString& determinand) {
    dateTimeComboBox->clear();

    QSet<QString> filteredDateTimes;
    for (const auto& fields : records) {
        if (fields[headers.indexOf("sample.samplingPoint.label")] == locationComboBox->currentText() &&
            fields[headers.indexOf("determinand.label")] == determinand) {
            filteredDateTimes.insert(fields[headers.indexOf("sample.sampleDateTime")]);
        }
    }

    dateTimeComboBox->addItems(filteredDateTimes.values());
}

void OverviewPage::onDateTimeSelected(const QString& dateTime) {
    dataTable->setRowCount(0);

    for (const auto& fields : records) {
        if (fields[headers.indexOf("sample.samplingPoint.label")] == locationComboBox->currentText() &&
            fields[headers.indexOf("determinand.label")] == determinandComboBox->currentText() &&
            fields[headers.indexOf("sample.sampleDateTime")] == dateTime) {

            for (int i = 0; i < headers.size(); ++i) {
                int row = dataTable->rowCount();
                dataTable->insertRow(row);
                dataTable->setItem(row, 0, new QTableWidgetItem(headers[i]));
                dataTable->setItem(row, 1, new QTableWidgetItem(fields[i]));
            }
        }
    }
}