 #include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>
#include <QPen>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QChart>
#include <QtCharts/QValueAxis>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QPieSeries>
#include <QtCharts/QBarCategoryAxis>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Sidebar animation setup
    sidebarAnimation = new QPropertyAnimation(ui->sidebar, "minimumWidth", this);
    sidebarAnimation->setDuration(200);

    connect(ui->toggleButton, &QPushButton::clicked, this, &MainWindow::onToggleButtonClicked);

    alignButtons();
    setupMainChart();
    setupBarChart();
    setupDonutChart();
    setupVerticalBarChart();

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowMaximizeButtonHint);

    // Set initial page to home
    ui->contentStackWidget->setCurrentWidget(ui->homePage);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupMainChart()
{
    // Data series
    QLineSeries *series = new QLineSeries();
    series->append(0, 45);
    series->append(1, 60);
    series->append(2, 75);
    series->append(3, 55);
    series->append(4, 85);
    series->append(5, 95);
    series->append(6, 70);

    // Chart setup
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle(" ");
    chart->setBackgroundBrush(QBrush(QColor("#161B22"))); // Match frame color

    // Series pen
    QPen seriesPen(QColor("#00F6FF"));
    seriesPen.setWidth(3);
    series->setPen(seriesPen);

    QPen axisPen(QColor("#21262D"));
    axisPen.setWidth(2);

    // X-Axis
    QValueAxis *axisX = new QValueAxis();
    axisX->setGridLineVisible(false);
    axisX->setLinePen(axisPen);
    axisX->setLabelsColor(QColor("#E6EDF3"));
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Y-Axis
    QValueAxis *axisY = new QValueAxis();
    axisY->setGridLinePen(axisPen);
    axisY->setLinePen(axisPen);
    axisY->setLabelsColor(QColor("#E6EDF3"));
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // ChartView
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Replace placeholder
    delete ui->mainChartPlaceholder;
    ui->mainChartLayout->addWidget(chartView);
}

void MainWindow::setupBarChart()
{
    // Data sets
    QBarSet *set0 = new QBarSet("Set 1");
    *set0 << 250 << 310 << 280 << 330 << 290 << 350;
    set0->setColor(QColor("#00F6FF"));

    // Series
    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->setBarWidth(0.8);

    // Chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle(" ");
    chart->setBackgroundBrush(QBrush(QColor("#161B22")));
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Axes
    QStringList categories = {"Jan", "Feb", "Mar", "Apr", "May", "Jun"};
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setGridLineVisible(false);
    axisX->setLabelsColor(QColor("#E6EDF3"));
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setGridLineVisible(true);
    axisY->setLinePenColor(QColor("#21262D"));
    axisY->setGridLineColor(QColor("#21262D"));
    axisY->setLabelsColor(QColor("#E6EDF3"));
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // ChartView
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Replace placeholder
    delete ui->barChartPlaceholder;
    ui->barChartLayout->addWidget(chartView);
}


void MainWindow::setupDonutChart()
{
    QPieSeries *series = new QPieSeries();
    series->setHoleSize(0.40);
    series->append("Cardiology", 40)->setBrush(QColor("#00F6FF"));
    series->append("Neurology", 25)->setBrush(QColor("#4E535A"));
    series->append("Oncology", 20)->setBrush(QColor("#8A929B"));
    series->append("Pediatrics", 15)->setBrush(QColor("#21262D"));

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle(" ");
    chart->setBackgroundBrush(QBrush(QColor("#161B22")));

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    delete ui->donutChartPlaceholder;
    ui->verticalLayout_5->addWidget(chartView);
}


void MainWindow::setupVerticalBarChart()
{
    // Data sets
    QBarSet *set0 = new QBarSet("Set 1");
    *set0 << 180 << 220 << 150 << 250 << 200;
    set0->setColor(QColor("#00F6FF"));

    // Series
    QBarSeries *series = new QBarSeries();
    series->append(set0);
    series->setBarWidth(0.5);

    // Chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->hide();
    chart->setTitle(" ");
    chart->setBackgroundBrush(QBrush(QColor("#161B22")));
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Axes
    QStringList categories = {"Dr. Smith", "Dr. Jones", "Dr. Lee", "Dr. White", "Dr. Green"};
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    axisX->setGridLineVisible(false);
    axisX->setLabelsColor(QColor("#E6EDF3"));
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setGridLineVisible(true);
    axisY->setLinePenColor(QColor("#21262D"));
    axisY->setGridLineColor(QColor("#21262D"));
    axisY->setLabelsColor(QColor("#E6EDF3"));
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);


    // ChartView
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Replace placeholder
    delete ui->verticalBarPlaceholder;
    ui->verticalLayout_6->addWidget(chartView);
}


void MainWindow::alignButtons()
{
    for (int i = 0; i < ui->sidebarLayout->count(); ++i) {
        QWidget *widget = ui->sidebarLayout->itemAt(i)->widget();
        if (QPushButton *button = qobject_cast<QPushButton*>(widget)) {
            button->setLayoutDirection(Qt::LeftToRight);
        }
    }
}


void MainWindow::onToggleButtonClicked()
{
    int endWidth = isSidebarOpen ? 60 : 200;

    // Set the end value for the animation and start it
    sidebarAnimation->setEndValue(endWidth);
    sidebarAnimation->start();

    // Toggle the state for the next click
    isSidebarOpen = !isSidebarOpen;
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        if (ui->topbar->geometry().contains(event->pos())) {
            dragging = true;
            dragPosition = event->globalPos() - frameGeometry().topLeft();
            event->accept();
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
    if (dragging && (event->buttons() & Qt::LeftButton)) {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event) {
    dragging = false;
}

void MainWindow::on_close_clicked()
{
    QApplication::closeAllWindows();
}


void MainWindow::on_pushButton_2_clicked()
{
    if(isMaximized())
    {
        showNormal();
    }
    else
    {
        showMaximized();
    }
}


void MainWindow::on_pushButton_3_clicked()
{
    showMinimized();
}


void MainWindow::on_patientsButton_clicked()
{
    ui->contentStackWidget->setCurrentWidget(ui->patientsPage);
}


void MainWindow::on_homeButton_clicked()
{
    ui->contentStackWidget->setCurrentWidget(ui->homePage);
}


void MainWindow::on_appointmentsButton_clicked()
{
    ui->contentStackWidget->setCurrentWidget(ui->appointmentsPage);
}

