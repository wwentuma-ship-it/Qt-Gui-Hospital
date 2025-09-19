#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QMouseEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

private slots:
    void onToggleButtonClicked();

    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    void on_close_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_patientsButton_clicked();

    void on_homeButton_clicked();

    void on_appointmentsButton_clicked();

private:
    Ui::MainWindow *ui;
    bool isSidebarOpen = false; // Sidebar starts open as per the UI file
    QPropertyAnimation *sidebarAnimation;

    void alignButtons();
    void setupMainChart();
    void setupBarChart();
    void setupDonutChart();
    void setupVerticalBarChart();

    bool dragging = false;
    QPoint dragPosition;
};

#endif // MAINWINDOW_H
