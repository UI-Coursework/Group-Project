#ifndef FLUORINATEDCOMPOUNDS_H
#define FLUORINATEDCOMPOUNDS_H

#include <QDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QDateTimeAxis>
#include <QtCharts/QValueAxis>
#include <QComboBox>
#include <QTableWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QLabel>
#include <QHeaderView>
#include "csv.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class FluorinatedCompounds; }
QT_END_NAMESPACE

struct PFASData {
    QString location;
    QString date;
    double value;
};

class FluorinatedCompounds : public QDialog {
    Q_OBJECT

public:
    explicit FluorinatedCompounds(QWidget *parent = nullptr);
    ~FluorinatedCompounds();

private slots:
    void updateLocationComboBox();
    void updateDateComboBoxes(const QString& location);
    void onLoadButtonClicked();
    void handleSeriesHovered(const QPointF &point, bool state);

private:
    static const double PFAS_THRESHOLD;
    Ui::FluorinatedCompounds *ui;
    
    // Chart components
    QChartView *chartView;
    QChart *chart;
    QDateTimeAxis *axisX;
    QValueAxis *axisY;
    
    // UI Components
    QComboBox *locationComboBox;
    QComboBox *startDateComboBox;
    QComboBox *endDateComboBox;
    QTableWidget *detailsTable;
    QPushButton *loadButton;
    
    // Data storage
    std::vector<PFASData> dataCache;
    
    // Member functions
    void setupUI();
    void loadData();
    void updateChart();
    void updateDetailsTable();
    void clearAxes();
};

#endif
