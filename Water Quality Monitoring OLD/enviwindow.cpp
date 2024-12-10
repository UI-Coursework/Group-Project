#include <QtWidgets>
#include <stdexcept>
#include <iostream>
#include "enviwindow.hpp"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

EnviWindow::EnviWindow(QWidget *parent) : QWidget(parent)
{
  createMainWidget();
  createSelector();
  updateChart();
  loadData();
  setWindowTitle("Environmental Litter Indicators Page");
}


void EnviWindow::createMainWidget()
{
  series = new QBarSeries();

  QBarSet *set_1 = new QBarSet(tr("Location"));
  series->append(set_1);

  litter_chart = new QChart();
  litter_chart->addSeries(series);
  litter_chart->setTitle(tr("Environmental Litter Distribution"));

  QBarCategoryAxis *axisX = new QBarCategoryAxis();
  axisX->append(littersPresent);
  litter_chart->addAxis(axisX, Qt::AlignBottom);
  series->attachAxis(axisX);

  QValueAxis *axisY = new QValueAxis();
  axisY->setTitleText(tr("Litter Amount (Garber C)"));
  axisY->setRange(0, 4);
  litter_chart->addAxis(axisY, Qt::AlignLeft);
  series->attachAxis(axisY);

  litter_chart->legend()->setVisible(true);
  litter_chart->legend()->setAlignment(Qt::AlignBottom);

  chartView = new QChartView(litter_chart);
  chartView->setRenderHint(QPainter::Antialiasing);

  chartView->setVisible(true);
}

void EnviWindow::createSelector()
{
    QHBoxLayout *mainLayout = new QHBoxLayout(this); 

    QVBoxLayout *toolbarLayout = new QVBoxLayout(); 

    toolbarLayout->addWidget(new QLabel(tr("Select Location:")));
    litterLocationComboBox = new QComboBox(this);
    toolbarLayout->addWidget(litterLocationComboBox); 
    connect(litterLocationComboBox, &QComboBox::currentIndexChanged, this, &EnviWindow::updateChart);

    QStringList locationOptions;
    locationOptions << tr("Select Location"); //insert location for the water sample
    litterLocationComboBox->addItems(locationOptions);

    QLabel *bwpExplanation = new QLabel();
    bwpExplanation->setText(tr("\nLITTER TYPES:\nAlgal Bloom: BWP - A.B.\nAnimal Feces: BWP - A.F.\nMacroalgae: BWP - Ma\nOther Litter (incl. plastics): BWP - O.L."));
    toolbarLayout->addWidget(bwpExplanation);
    toolbarLayout->addStretch();

    mainLayout->addLayout(toolbarLayout); 
    mainLayout->addWidget(chartView);
    setLayout(mainLayout);
}


void EnviWindow::loadData() {
    QFile file("data.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, tr("Error"), tr("Unable to open the data file."));
        return;
    }

    QTextStream in(&file);
    headers = in.readLine().split(",");

    QSet<QString> littersList;
    QSet<QString> litterLocations; 

    while (!in.atEnd()) {
        QStringList fields = in.readLine().split(",");
        if (fields.size() != headers.size()) continue;

        QString litters = fields[headers.indexOf("determinand.label")];
        QString location = fields[headers.indexOf("sample.samplingPoint.label")];
        QString result = fields[headers.indexOf("result")];

        if (litters.contains("BWP")){
            littersList.insert(litters);
            litterLocations.insert(location);
            litterResults.insert(result); 

        }
        records[fields[headers.indexOf("@id")]] = fields;
    }
    
    litterLocationComboBox->addItems(litterLocations.values());

    QList<QString> litterslist_str(littersList.begin(), littersList.end());
    littersPresent = QStringList::fromList(litterslist_str);

    file.close();
}

void EnviWindow::updateChart() { 
  QString selectedLocation = litterLocationComboBox->currentText(); 
  if (selectedLocation == tr("Select Location")) return;

  QMap<QString, QVector<double>> litterValues; 

  for (const QString& id : records.keys()) { 
    QString location = records[id][headers.indexOf("sample.samplingPoint.label")]; 
    QString litter = records[id][headers.indexOf("determinand.label")]; 
    QString resultStr = records[id][headers.indexOf("result")]; 
    QString metricName = records[id][headers.indexOf("determinand.label")]; 

    if (location != selectedLocation || !litter.contains("BWP")) { 
      continue; 
        } 

    bool ok; 
    double result = resultStr.toDouble(&ok); 
    if (!ok) continue; 
      litterValues[litter].append(result); 
    } 

    // Calculate averages 
    QStringList litterNames; 
    QVector<double> litterResults; 

    for (auto it = litterValues.begin(); it != litterValues.end(); ++it) { 
      const QString& litterName = it.key(); 
      const QVector<double>& values = it.value(); 

      double mean = std::accumulate(values.begin(), values.end(), 0.0) / values.size(); 
      litterNames.append(litterName); 
      litterResults.append(mean); 
    } 
  
    // Update the chart 
    series->clear(); 
    QBarSet *set = new QBarSet(selectedLocation); 

    for (double value : litterResults) { 
      set->append(value); 
    } 
    series->append(set); 

    // Update the x-axis 
    QBarCategoryAxis *axisX = qobject_cast<QBarCategoryAxis *>(litter_chart->axes(Qt::Horizontal).first()); 
    if (axisX) { 
        axisX->clear(); 
        axisX->append(litterNames); 
    }   
    litter_chart->update(); 

  QString message = QString(tr("For location '%1':\nAverage Bathing Water Profile Results:\n%2: %3\n%4: %5\n%6: %7\n%8: %9")) 
    .arg(selectedLocation)
    .arg(litterNames[0])
    .arg(litterResults[0], 0, 'f', 2)
    .arg(litterNames[1])
    .arg(litterResults[1], 0, 'f', 2)
    .arg(litterNames[2])
    .arg(litterResults[2], 0, 'f', 2)
    .arg(litterNames[3])
    .arg(litterResults[3], 0, 'f', 2);
  
    QMessageBox::information(this, tr("Litter Results"), message); 
}
