#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "cstdlib"
#include "vector"
#include <QTimer>
#include <QFile>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile file("/sys/class/thermal/thermal_zone0/temp");

    std::vector<int> value(10);
    // for (int i = 0; i < 10; i++) {
    //     values.push_back(std::rand() % 31);
    //     series->append(i, values[i]);
    // }

    // read temp from file
    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical()<<"Cant open file";
        qCritical()<<file.errorString();
        return;
    }

    QTextStream stream(&file);
    QString data = stream.readLine();

    int temp = data.split(" ")[0].toInt();

    values.push_back(temp / 1000);
    series->append(0, values[0]);

    //----
    
    QChart* chart = new QChart();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Chungus");
    chart->axes(Qt::Vertical).first()->setRange(0,100);

    
    QChartView* view = new QChartView(chart);
    
    view->setRenderHint(QPainter::Antialiasing);
    view->setParent(ui->horizontalFrame);
    //view->resize(640,480);


    // Timer to update every 60 seconds (for testing, set 1000ms)
    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::updateChart);
    timer->start(1000); // 60000 ms = 1 minute
}
void MainWindow::updateChart()
{
    QFile file("/sys/class/thermal/thermal_zone0/temp");
    // shift values
    values.erase(values.begin());

    if(!file.open(QIODevice::ReadOnly))
    {
        qCritical()<<"Cant open file";
        qCritical()<<file.errorString();
        return;
    }

    QTextStream stream(&file);
    QString data = stream.readLine();

    int temp = data.split(" ")[0].toInt();

    values.push_back(temp / 1000);

    series->clear();
    for (int i = 0; i < (int)values.size(); i++) {
        series->append(i, values[i]);
    }
}
MainWindow::~MainWindow()
{
    delete ui;


}
