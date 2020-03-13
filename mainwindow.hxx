#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX

#include <QMainWindow>
#include <QIcon>
#include <QPainter>
#include <QPaintEvent>
#include <cmath>
#include <QDebug>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

extern const double pi;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    double toRad(double);

private:
    Ui::MainWindow *ui;
    const int aleth_dimensions[2]  = {760, 760},
              arm1_dimensions[2]   = {21, 230},
              arm2_dimensions[2]   = {51, 290},
              arm3_dimensions[2]   = {38, 230},
              needle_dimensions[2] = {40, 315};
    QIcon* _aleth_svg = new QIcon(":/media/images/alethiometer.svg");
    QIcon* _arm_1 = new QIcon(":/media/images/arm1.svg");
    QIcon* _arm_2 = new QIcon(":/media/images/arm2.svg");
    QIcon* _arm_3 = new QIcon(":/media/images/arm3.svg");
    QIcon* _needle = new QIcon(":/media/images/needle.svg");
    void paintEvent(QPaintEvent*);
    void setArm(QPainter*, QIcon*, int, int, int, int arm_offset=0);
    const int resolution[2] = {1024, 768};
};
#endif // MAINWINDOW_HXX
