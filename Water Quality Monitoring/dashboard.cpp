#include "dashboard.hpp"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QComboBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <numeric>
#include <QMessageBox>

Dashboard::Dashboard(QWidget* parent) : QWidget(parent) {
    mainLayout = new QVBoxLayout(this);

    // Load and process data
    loadData();
    processData();

    // Create layout sections
    createHeader();
    createMainContent();
    createFooter();

    setLayout(mainLayout);
}

void Dashboard::createHeader() {
    // Vertical Layout for Header
    QVBoxLayout* headerLayout = new QVBoxLayout();

    // App Title
    QLabel* title = new QLabel(tr("Water Quality Monitor"));
    title->setStyleSheet("font-size: 24px; font-weight: bold; margin: 10px;");
    title->setAlignment(Qt::AlignCenter);


    // Horizontal Layout for Language Selector
    QHBoxLayout* languageLayout = new QHBoxLayout();
    languageLayout->addStretch();
    // languageLayout->addWidget(languageComboBox);

    // Add the title and language selector to the header
    headerLayout->addWidget(title);
    headerLayout->addLayout(languageLayout);

    // Add the header layout to the main layout
    mainLayout->addLayout(headerLayout);
}

void Dashboard::createMainContent() {
    // Cards Grid Layout
    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->setSpacing(20); // Add spacing between cards

    int row = 0, col = 0;
    const int maxColumns = 4; // Fixed 4x4 grid
    const int maxCards = 16;   // Show exactly 16 cards

    int count = 0;
    for (auto it = averageValues.begin(); it != averageValues.end() && count < maxCards; ++it) {
        QString location = it.key();
        double average = it.value();
        QString compliance = complianceStatuses[location];

        // Create Card
        QFrame* card = new QFrame();
        card->setFrameShape(QFrame::StyledPanel);
        card->setStyleSheet(QString("background-color: %1; border-radius: 10px;")
                                .arg(getColor(compliance)));
        card->setFixedSize(250, 120); // Card size

        QVBoxLayout* cardLayout = new QVBoxLayout(card);

        QLabel* locationLabel = new QLabel(location);
        locationLabel->setStyleSheet("font-size: 14px; font-weight: bold; color: black;");
        locationLabel->setAlignment(Qt::AlignCenter);
        locationLabel->setWordWrap(true);

        QLabel* averageLabel = new QLabel(QString::number(average, 'f', 2));
        averageLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: black;");
        averageLabel->setAlignment(Qt::AlignCenter);

        cardLayout->addWidget(locationLabel);
        cardLayout->addWidget(averageLabel);

        gridLayout->addWidget(card, row, col);

        col++;
        if (col >= maxColumns) {
            col = 0;
            row++;
        }
        count++;
    }

    // Add the grid layout directly below the title
    mainLayout->addLayout(gridLayout);

    // Add a stretch to push footer content down while keeping cards at the top
    mainLayout->addStretch();
}

void Dashboard::createFooter() {
    QHBoxLayout* footerLayout = new QHBoxLayout();

    QPushButton* userGuideButton = new QPushButton(tr("User Guide"));
    QPushButton* helpButton = new QPushButton(tr("Help"));
    QPushButton* creditsButton = new QPushButton(tr("Credits"));

    connect(creditsButton, &QPushButton::clicked, this, &Dashboard::showCreditsPopup);

    footerLayout->addWidget(userGuideButton);
    footerLayout->addStretch();
    footerLayout->addWidget(helpButton);
    footerLayout->addWidget(creditsButton);

    mainLayout->addLayout(footerLayout);
}

void Dashboard::showCreditsPopup() {
    QMessageBox::information(this, tr("Credits"), tr("All the data used in this application is received from: <a href='https://environment.data.gov.uk/water-quality/view/doc/reference'>Here</a>"));
    
}

void Dashboard::loadData() {
    QFile file("data.csv"); // Replace with your CSV file path
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Unable to open CSV file:" << file.fileName();
        return;
    }

    QTextStream in(&file);
    QString headerLine = in.readLine(); // Read the header line
    QStringList headers = headerLine.split(',');

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');

        if (fields.size() != headers.size()) {
            continue; // Skip malformed lines
        }

        QMap<QString, QString> row;
        for (int i = 0; i < headers.size(); ++i) {
            row[headers[i]] = fields[i];
        }
        data.append(row);
    }

    file.close();
}

void Dashboard::processData() {
    // Aggregate data to calculate average pollutant levels and compliance statuses
    QMap<QString, QList<double>> locationValues;

    for (const auto& row : data) {
        QString location = row["sample.samplingPoint.label"];
        double value = row["result"].toDouble();

        if (!location.isEmpty()) {
            locationValues[location].append(value);
        }
    }

    for (auto it = locationValues.begin(); it != locationValues.end(); ++it) {
        QString location = it.key();
        QList<double> values = it.value();

        double sum = std::accumulate(values.begin(), values.end(), 0.0);
        double average = sum / values.size();
        averageValues[location] = average;

        if (average <= 50) {
            complianceStatuses[location] = "Green";
        } else if (average <= 150) {
            complianceStatuses[location] = "Yellow";
        } else {
            complianceStatuses[location] = "Red";
        }
    }
}

QString Dashboard::getColor(const QString& compliance) const {
    if (compliance == "Green") return "green";
    if (compliance == "Yellow") return "yellow";
    return "red";
}
