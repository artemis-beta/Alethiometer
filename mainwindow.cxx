#include "mainwindow.hxx"
#include "ui_mainwindow.h"

const extern double pi = 4*atan(1);

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    this->setGeometry(0, 0, 768, 768);
}

MainWindow::~MainWindow()
{
    delete ui;
}

double MainWindow::toRad(double a)
{
    return a*pi/180.;
}

void MainWindow::setArm(QPainter* painter, QIcon* arm, int x, int y, int pos, int arm_offset)
{
    const double angle = toRad(10*pos);
    const double centre_offset = -16;
    const QPixmap _pxmap = arm->pixmap(QSize(x, y));
    painter->save();
    painter->translate(resolution[1]/2., resolution[1]/2.-centre_offset);
    painter->rotate(10*pos);
    painter->translate(-x/2.,-y+arm_offset);
    painter->drawPixmap(0, 0, x, y, _pxmap);
    painter->restore();
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter* _painter = new QPainter(this);
    const double offset = 0.5*(resolution[1]-aleth_dimensions[1]);
    _painter->drawPixmap(offset, offset, aleth_dimensions[0], aleth_dimensions[1], _aleth_svg->pixmap(QSize(aleth_dimensions[0],aleth_dimensions[1])));
    setArm(_painter, _arm_1, arm1_dimensions[0], arm1_dimensions[1], 4);
    setArm(_painter, _arm_2, arm2_dimensions[0], arm2_dimensions[1], 2, 67);
    setArm(_painter, _arm_3, arm3_dimensions[0], arm3_dimensions[1], 7);
    setArm(_painter, _needle, needle_dimensions[0], needle_dimensions[1], 11, 67);
    _painter->end();
}

