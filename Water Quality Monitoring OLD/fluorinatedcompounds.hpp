#ifndef FLUORINATEDCOMPOUNDS_H
#define FLUORINATEDCOMPOUNDS_H

#include <QDialog>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QPushButton>
#include "datamanager.hpp"

namespace Ui {
class FluorinatedCompounds;
}

class FluorinatedCompounds : public QDialog {
    Q_OBJECT

public:
    explicit FluorinatedCompounds(QWidget *parent = nullptr);
    ~FluorinatedCompounds();

private slots:
    void handleSeriesHovered(const QPointF &point, bool state);

private:
    Ui::FluorinatedCompounds *ui;
    QChartView *chartView;
    QMap<QString, QLineSeries*> siteSeries;
    DataManager dataManager;
    static const double PFAS_THRESHOLD;

    void setupChart();
    void loadAndDisplayData();
    void updateChart(const std::vector<PollutantData>& data);
};

#endif
