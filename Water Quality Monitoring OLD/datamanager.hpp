#ifndef DATAMANAGER_HPP
#define DATAMANAGER_HPP

#include <QString>
#include <vector>
#include <set>
#include "csv.hpp"

// Define the PollutantData structure
struct PollutantData {
    QString id;
    QString samplingPoint;
    QString samplingPointNotation;
    QString samplingPointLabel;
    QString sampleDateTime;
    QString determinandLabel;
    QString determinandDefinition;
    QString determinandNotation;
    QString resultQualifierNotation;
    double result;
    QString codedResultInterpretation;
    QString determinandUnitLabel;
    QString sampledMaterialTypeLabel;
    bool isComplianceSample;
    QString purposeLabel;
    double easting;
    double northing;
};

class DataManager {
public:
    DataManager();
    void loadData(const QString& filePath);
    const std::vector<PollutantData>& getData() const;
    const std::set<QString>& getPollutants() const;

private:
    std::vector<PollutantData> dataCache;
    std::set<QString> pollutants;
};

#endif // DATAMANAGER_HPP
