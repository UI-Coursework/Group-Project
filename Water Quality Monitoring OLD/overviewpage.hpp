#ifndef OVERVIEWPAGE_HPP
#define OVERVIEWPAGE_HPP

#include <QWidget>
#include <QComboBox>
#include <QTableWidget>
#include <QStringList>
#include <QMap>

class OverviewPage : public QWidget {
    Q_OBJECT

public:
    explicit OverviewPage(QWidget* parent = nullptr);

private slots:
    void onLocationSelected(const QString& location);
    void onDeterminandSelected(const QString& determinand);
    void onDateTimeSelected(const QString& dateTime);

private:
    QComboBox* locationComboBox;
    QComboBox* determinandComboBox;
    QComboBox* dateTimeComboBox;
    QTableWidget* dataTable;
    QStringList headers;
    QMap<QString, QStringList> records;

    void loadData();
    void setupUI();
};

#endif // OVERVIEWPAGE_HPP