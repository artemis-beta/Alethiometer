#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX

#include <QMainWindow>
#include <QIcon>
#include <QMap>
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>

#include "arm.hxx"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    double toRad(double);

private:
    Ui::MainWindow *ui;
    const QList<int> aleth_dimensions  = {760, 760},
              arm1_dimensions   = {21, 230},
              arm2_dimensions   = {51, 290},
              arm3_dimensions   = {38, 230},
              needle_dimensions = {40, 315};
    const QList<int> resolution = {1024, 768};
    const double centre_offset = -16;
    QIcon* _aleth_svg = new QIcon(":/media/images/alethiometer.svg");
    QMap<int, Arm*> _arms = {{1, new Arm(QString(":/media/images/arm1.svg"), resolution, arm1_dimensions, centre_offset)},
                            {2, new Arm(QString(":/media/images/arm2.svg"), resolution, arm2_dimensions, centre_offset, 67)},
                            {3, new Arm(QString(":/media/images/arm3.svg"), resolution, arm3_dimensions, centre_offset)},
                            {0, new Arm(QString(":/media/images/needle.svg"), resolution, needle_dimensions, centre_offset, 67)}};

    const QMap<int, QList<QList<int>>> dial_positions = {{1, {{356, 55}, {412, 81}}},
                                                         {2, {{21, 607}, {71, 672}}},
                                                         {3, {{700, 615},{742, 652}}}
                                                         };
    void paintEvent(QPaintEvent*);
    void wheelEvent(QWheelEvent*);
    void setArm(QPainter*, QIcon*, int, int, int, int arm_offset=0);
};
#endif // MAINWINDOW_HXX
