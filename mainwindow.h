#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    int USB = 0;
protected:
    void addPoint();
    void plot();
    unsigned long x_pos;

private slots:
    void on_but_pause_clicked();

    void on_but_save_2_clicked();

    void on_dial_sliderMoved(int position);

    void on_dial_sliderReleased();

private:
    Ui::MainWindow *ui;
    QVector<double> qv_x, qv_y;
    int baud_rate = 2000000;
    bool is_running = false;
    void run(void);
    int read_count = 100;
};

#endif // MAINWINDOW_H
