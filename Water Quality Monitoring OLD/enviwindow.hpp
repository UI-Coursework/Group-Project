#pragma once

#include <QMainWindow>
// #include "model.hpp"
#include <QComboBox>
#include <QtCharts>

class QString;
class QComboBox;
class QLabel;
class QPushButton;
class QTableView;
class StatsDialog;

class EnviWindow: public QWidget
{
  Q_OBJECT

  public:
    explicit EnviWindow(QWidget* parent = nullptr);

  private:
    void createMainWidget();
    void createSelector();
    void createButtons();


    QString dataLocation;      
    QChart *litter_chart;      
    QBarSeries *series;           
    QChartView *chartView;
    QComboBox* litterLocationComboBox;
    QComboBox* litterComboBox;
    QStringList headers;
    QMap<QString, QStringList> records;
    QSet<QString> litterResults;
    QStringList littersPresent; 

  private slots:
    void loadData();
    void updateChart();
};
