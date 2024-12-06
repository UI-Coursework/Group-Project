#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QTabWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

private:
    QTabWidget* tabWidget;
    QWidget* createPage1();
    QWidget* createPage3();
};

#endif // MAINWINDOW_HPP