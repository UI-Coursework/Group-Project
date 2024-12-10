#include "datamanager.hpp"
#include <QDebug>

DataManager::DataManager() {}

void DataManager::loadData(const QString& filePath) {
    csv::CSVReader reader(filePath.toStdString());
    dataCache.clear();
    pollutants.clear();

    try {
        for (csv::CSVRow& row : reader) {
            PollutantData data{
                QString::fromStdString(row["@id"].get<std::string>()),
                QString::fromStdString(row["sample.samplingPoint"].get<std::string>()),
                QString::fromStdString(row["sample.samplingPoint.notation"].get<std::string>()),
                QString::fromStdString(row["sample.samplingPoint.label"].get<std::string>()),
                QString::fromStdString(row["sample.sampleDateTime"].get<std::string>()),
                QString::fromStdString(row["determinand.label"].get<std::string>()),
                QString::fromStdString(row["determinand.definition"].get<std::string>()),
                QString::fromStdString(row["determinand.notation"].get<std::string>()),
                QString::fromStdString(row["resultQualifier.notation"].get<std::string>()),
                row["result"].get<double>(),
                QString::fromStdString(row["codedResultInterpretation.interpretation"].get<std::string>()),
                QString::fromStdString(row["determinand.unit.label"].get<std::string>()),
                QString::fromStdString(row["sample.sampledMaterialType.label"].get<std::string>()),
                row["sample.isComplianceSample"].get<bool>(),
                QString::fromStdString(row["sample.purpose.label"].get<std::string>()),
                row["sample.samplingPoint.easting"].get<double>(),
                row["sample.samplingPoint.northing"].get<double>()
            };
            dataCache.push_back(data);
            pollutants.insert(data.determinandDefinition);
        }
    }
    catch (const std::exception& e) {
        qDebug() << "Error reading CSV file:" << e.what();
    }
}

const std::vector<PollutantData>& DataManager::getData() const {
    return dataCache;
}

const std::set<QString>& DataManager::getPollutants() const {
    return pollutants;
}
