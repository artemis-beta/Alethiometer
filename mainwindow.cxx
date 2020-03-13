#include "mainwindow.hxx"
#include "ui_mainwindow.h"

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

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter* _painter = new QPainter(this);
    const double offset = 0.5*(resolution[1]-aleth_dimensions[1]);
    _painter->drawPixmap(offset, offset, aleth_dimensions[0], aleth_dimensions[1], _aleth_svg->pixmap(QSize(aleth_dimensions[0],aleth_dimensions[1])));
    for(auto arm : _arms)
    {
        arm->Paint(_painter);
    }
    _painter->end();
}

void MainWindow::wheelEvent(QWheelEvent * event)
{
    for(int i{1}; i < dial_positions.size()+1; ++i)
    {
        QList<QList<int>> dial = dial_positions[i];
        const bool pos_check = event->globalX() > dial[0][0] && event->globalX() < dial[1][0] && event->globalY() > dial[0][1] && event->globalY() < dial[1][1];
        if(pos_check)
        {
            _arms[i]->setPosition(_arms[i]->getPosition()+(event->delta()/abs(event->delta())));
            update();
        }
    }
}

