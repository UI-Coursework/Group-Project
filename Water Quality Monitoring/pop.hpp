#ifndef POP_H
#define POP_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QtCharts/QValueAxis>
#include <QtCharts/QDateTimeAxis>
#include <QGridLayout>
#include <QTimer>
#include <QStringListModel>
#include <QStackedWidget>
#include <QtCharts/QChartView>
#include <QLabel>
#include <QComboBox>
#include "datamanager.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
    class popWindow;
}
QT_END_NAMESPACE

struct PopData {
    QString determinandDefinition;
    QString samplingPoint;
    QString sampleDateTime;
    double result;
};

class popWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit popWindow(QWidget *parent = nullptr);
    ~popWindow();

private slots:
    void loadPopData();
    void updateChart();
    void populateComboBoxes();
    void updateDateComboBoxes(const QString& location);
    QString getHealthRiskInfo(const QString& pollutant);

private:
    Ui::popWindow *ui;
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    DataManager dataManager;
    QLabel* healthInfoLabel = nullptr;
    std::vector<PopData> dataCache;
    void setupSearchableComboBox(QComboBox* comboBox);
    void filterComboBox(QComboBox* comboBox, const QString& text);
    QComboBox* pollutantComboBox;
    QComboBox* locationComboBox;
    QComboBox* startDateComboBox;
    QComboBox* endDateComboBox;
    QChartView* mainChartView;
};

#endif // POP_H
