#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serialdatareader.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->plot->addGraph();
    ui->plot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
    x_pos = 0;
}

MainWindow::~MainWindow()
{
    //close_connection();
    delete ui;
}

void MainWindow::plot()
{
    ui->plot->graph(0)->setData(qv_x,qv_y);
    ui->plot->replot();
    ui->plot->update();
}

void MainWindow::on_but_pause_clicked()
{
    if (is_running) {
        ui->but_pause->setText("Pause");
        is_running = false;

    }
    else {
        ui->but_pause->setText("Resume");
        is_running = true;
        while (is_running) {
            run();
            QCoreApplication::processEvents();
        }
    }
}

void MainWindow::addPoint()
{
    MainWindow::plot();

}

void MainWindow::on_but_save_2_clicked()
{
    USB = open_connection("/dev/ttyACM0");
}

void MainWindow::run() {

    for(int i = 0; i<read_count;i++)
    {
        qv_x.append(x_pos);
        float y_pos = read_line(USB);
        if (y_pos < 1) {
            qv_y.append(y_pos);
        }
        if (qv_y.size() > 7500) {
            qv_y.removeFirst();
        }
        if (qv_x.size() > 7500) {
            qv_x.removeFirst();
        }

        x_pos++;
    }
    //x_pos = 0;
    //flush();
    ui->plot->yAxis->setRange(0,1);
    ui->plot->xAxis->rescale();

    plot();
}

void MainWindow::on_dial_sliderMoved(int position)
{
    read_count = ui->scroll_speed->value();
    ui->scroll_speed->display(position);
    ui->scroll_speed->show();
}

void MainWindow::on_dial_sliderReleased()
{
        read_count = ui->scroll_speed->value();
}
