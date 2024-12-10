#pragma once

#include <QWidget>
#include <QComboBox>
#include <QListWidget>
#include <QPushButton>
#include <QString>
#include <QVBoxLayout>
#include <QMap>
#include <QVector>

class ComplianceDashboard : public QWidget
{
    Q_OBJECT

public:
    ComplianceDashboard(QWidget* parent = nullptr);

private:
    QComboBox* locationFilter;   // Filter by location
    QComboBox* pollutantFilter;  // Filter by pollutant
    QComboBox* statusFilter;     // Filter by compliance status
    QListWidget* complianceList; // List of compliance statuses
    QPushButton* refreshButton;  // Button to refresh the dashboard

    QVector<QMap<QString, QString>> data; // Vector of maps to hold CSV rows

    void populateComplianceList(); // Populate the compliance list based on filters
    void loadDataFromCSV(const QString& filePath); // Load data from CSV file
    void updateFilters(); // Update filter options dynamically
    bool matchesFilters(const QString& location, const QString& pollutant, const QString& compliance); // Apply filters

private slots:
    void onItemClicked(QListWidgetItem* item); // Show details for clicked item
    void onRefreshClicked(); // Handle refresh button click
};
