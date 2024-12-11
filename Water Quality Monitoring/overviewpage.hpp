#ifndef OVERVIEWPAGE_HPP
#define OVERVIEWPAGE_HPP

#include <QWidget>
#include <QComboBox>
#include <QTableWidget>
#include <QPushButton>
#include <QtCharts/QChartView>
#include <QtCharts/QChart>
#include <QtCharts/QLineSeries>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QtCharts/QDateTimeAxis>
#include <QLineEdit>
#include <QLabel>
#include <QGroupBox>
#include <QHeaderView>
#include <vector>
#include <QString>
#include "charttooltip.hpp"  // Include the custom tooltip header
#include "csv.hpp"
#include <set>

// Define the PollutantData structure
struct overviewData {
    QString pollutant;
    QString location;
    QString date;
    double value;
    QString unit; // New field for unit
};

class OverviewPage : public QWidget {
    Q_OBJECT

public:
    explicit OverviewPage(QWidget* parent = nullptr);

private slots:
    void onLoadButtonClicked();
    // void toggleChartType();
    void updateLocationComboBox(const QString& pollutant);
    void updateDateComboBoxes(const QString& location);

private:
    void setupUI();
    void loadData();
    void updateChart();
    void updateDetailsTable();
    void clearAxes();

    // Cached data
    std::vector<overviewData> dataCache;

    // UI components
    QComboBox* pollutantComboBox;
    QComboBox* locationComboBox;
    QComboBox* startDateComboBox;
    QComboBox* endDateComboBox;
    QTableWidget* detailsTable;
    QPushButton* toggleChartButton;
    QChartView* chartView;
    QChart* chart;
    bool isLineChart;

    // Axes
    QDateTimeAxis* axisX;
    QValueAxis* axisY;
    QBarCategoryAxis* barAxisX;

    // Tooltip
    ChartTooltip* tooltip;
};

#endif // OVERVIEWPAGE_HPP
