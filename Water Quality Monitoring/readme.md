---

# **Water Quality Monitoring and Analysis Application**

---

## **Team Members**
- **Mohamed Aik Shamir**
- **Hpone Thu**
- **Veerinrada Pianapitham**
- **Alp Akkor**

---

## **Project Overview**
This application monitors and analyzes water quality data, focusing on pollutant tracking and compliance with safety standards. Developed using **C++/Qt6**, it features a modular, user-friendly interface with basic internationalization capabilities. Key functionalities include dynamic data visualization, advanced filtering, and compliance analysis to empower decision-makers with actionable insights.

---

## **Prerequisites**

### **Software Requirements**
- **CMake** (Version `3.16` or newer): For building the project and managing dependencies.
- **Qt6 Framework**:
  - Required Modules: `Qt6::Widgets`, `Qt6::Charts`, `Qt6::LinguistTools`.
- **C++ Compiler**:
  - Minimum Standard: `C++17`
  - Supported Compilers: GCC 7.2+, Clang 5.0+, MSVC 15.7+.

---

### **Installation Steps**
1. Install the required software packages (`Qt6`, `CMake`, and a C++ compiler).
2. Build the project:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```
3. Run the application:
   ```bash
   ./watertool
   ```

---

### **Notes**
- Ensure **Qt6 Framework** is properly installed and available in the system path.
- Verify the data source location to ensure correct display of data. Bare in mind that only loading specific locations and pollutants will display on charts and graphs.

---

## **File Structure**

```
Monitoring/
├── build/
├── CMakeLists.txt
├── compliance_dashboard/
│   ├── compliance_dashboard.cpp
│   ├── compliance_dashboard.hpp
├── csv.hpp
├── dashboard/
│   ├── dashboard.cpp
│   ├── dashboard.hpp
├── datamanager/
│   ├── datamanager.cpp
│   ├── datamanager.hpp
├── enviwindow/
│   ├── enviwindow.cpp
│   ├── enviwindow.hpp
├── fluorinatedcompounds/
│   ├── fluorinatedcompounds.cpp
│   ├── fluorinatedcompounds.hpp
│   ├── fluorinatedcompounds.ui
├── main/
│   ├── main.cpp
│   ├── mainwindow.cpp
│   ├── mainwindow.hpp
├── map.qml
├── overviewpage/
│   ├── overviewpage.cpp
│   ├── overviewpage.hpp
├── pop/
│   ├── pop.cpp
│   ├── pop.hpp
│   ├── pop.ui
├── Quality/
├── readme.md
├── resources.qrc
├── translations/
│   ├── watertool_de.ts
│   ├── watertool_fr.ts
├── Y-2024.csv
```

---

## **Known Issues**
1. **Performance Delays**: Slight delays during startup and page transitions.
2. **Map Functionality**: Relies on static placeholder data; full implementation pending.
3. **Footer Placeholder**: Dashboard footer lacks functionality.
4. **Chart Functionality**: Inconsistent performance with charts.
5. **Compliance Thresholds**: Missing data for compliance thresholds may cause inaccuracies.
6. **Data Loading Strategy**: Individual page data loading causes performance issues.
7. **Code Modularity**: Functions could be further modularized into separate files.
8. **Data Analysis**: Cross-referencing data could provide deeper insights.

---

## **Key Features**

### **1. Main Window**
Tabbed interface for seamless navigation between features via a top-left navigation bar.

### **2. Dashboard**
- **Summary View**: Card-based layout showing pollutant-level overviews.
- **Use Case**: Identifies safe, moderate, or dangerous pollution levels.

### **3. Pollutant Overview Page**
- **Filters**: By pollutant, location, and date range.
- **Visualization**: Detailed tables and bar charts; toggleable line charts.
- **Compliance Status**: Traffic-light color coding for quick identification.

### **4. Persistent Organic Pollutants (POPs) Page**
- **Dynamic Loading**: Loads data from CSV files.
- **Health Insights**: Displays safety thresholds and health risks.
- **Interactive Charts**: Time-series charts with tooltips.

### **5. Environmental Litter Page**
- **Details**: Summarizes physical pollutants like plastic litter and algal bloom.
- **Comparison**: Displays average pollutant levels in bar charts.
- **Filtering**: Real-time location-based filtering.

### **6. Fluorinated Compounds Page**
- **Dashboard**: Monitors PFAS levels against thresholds.
- **Visualization**: Displays charts and tables for results.

### **7. Compliance Dashboard**
- **Regulatory Insights**: Granular compliance details.
- **Interactive Filters**: Identifies and resolves issues.

### **8. Data Visualization**
- Bar and line charts implemented using QtCharts.
- Accessible titles, labels, and clear design.

### **9. Compliance Indicators**
- Traffic-light indicators (green, amber, red) highlight compliance levels.

### **10. Accessibility Features**
- Tooltips on charts for context.
- High-contrast colors for readability.
- Clear titles and labels.

### **11. Internationalization**
- Multiple language support via Qt translation system.
- Language settings based on system locale, managed via CMake.

---