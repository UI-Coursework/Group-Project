#include <stdexcept>
#include <algorithm>
#include <numeric>
#include "dataset.hpp"
#include "csv.hpp"

using namespace std;

void SampleDataset::loadData(const std::string& filename) {
    csv::CSVReader reader(filename);

    data.clear();

    for (const auto& row : reader) {
        Sample sample{
            row["id"].get<>(),
            row["sample.samplingPoint.notation"].get<>(),
            row["sample.samplingPoint.label"].get<>(),
            row["sample.samplingPoint.easting"].get<double>(),
            row["sample.samplingPoint.northing"].get<double>(),
            row["sample.sampleDateTime"].get<>(),
            row["sample.sampledMaterialType.label"].get<>(),
            row["determinand.label"].get<>(),
            row["determinand.definition"].get<>(),
            row["determinand.notation"].get<>(),
            row["determinand.unit.label"].get<>(),
            row["result"].get<double>(),
            row["resultQualifier.notation"].get<>(),
            row["codedResultInterpretation.interpretation"].get<>(),
            row["sample.isComplianceSample"].get<bool>(),
            row["sample.purpose.label"].get<>()
        };
        data.push_back(sample);
    }
}

std::vector<Sample> SampleDataset::getAllSamples() const {
    return data;
}
