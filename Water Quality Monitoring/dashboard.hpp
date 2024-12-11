#pragma once

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QMap>
#include <QString>
#include <QVector>

class Dashboard : public QWidget {
    Q_OBJECT

public:
    explicit Dashboard(QWidget* parent = nullptr);

private:
    void createHeader();
    void createMainContent();
    void createFooter();
    void showCreditsPopup();
    void populateCards(QGridLayout* layout);
    void loadData();
    void processData();
    QString determineCompliance(double averageValue);

    QString getColor(const QString& compliance) const;

    QVBoxLayout* mainLayout;
    QGridLayout* cardLayout;

    QLabel* appTitle;
    QPushButton* navButton1;
    QPushButton* navButton2;
    QPushButton* navButton3;

    QVector<QMap<QString, QString>> data;  // Vector of maps to hold CSV rows

    // Aggregated data for dashboard
    QMap<QString, double> averageValues;
    QMap<QString, QString> complianceStatuses;
    QMap<QString, double> locationValues;  // Total pollutant values by location
    QMap<QString, int> locationCounts;     // Sample counts by location
};
