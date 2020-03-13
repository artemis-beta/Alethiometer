#include "mainwindow.hxx"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qsrand(time(NULL));
    this->setGeometry(0, 0, 768, 768);
    connect(timer_1, SIGNAL(timeout()), this, SLOT(setNewPosition()));
    connect(timer_2, SIGNAL(timeout()), this, SLOT(updateNeedle()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent*)
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
void MainWindow::mousePressEvent(QMouseEvent*)
{
    predict();
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_Escape)
    {
        if(!_welcome->isVisible())
        {
            _welcome->show();
            _welcome->raise();
            _welcome->setWindowState(Qt::WindowActive);
        }
        else
        {
            _welcome->hide();
        }
    }
}

void MainWindow::updateNeedle()
{
    timer_1->stop();
    if(needle_position == _results[needle_target_index])
    {
        timer_2->stop();
        if(needle_target_index > 1)
        {
            timer_1->stop();
            needle_target_index = 0;
            return;
        }
        needle_target_index += 1;
        timer_1->start(1000);
        return;
    }
    needle_position = (needle_position < 36) ? needle_position+direction : 0;
    needle_position = (needle_position < 0) ? 36+needle_position : needle_position;
    _arms[0]->setPosition(needle_position);


    this->update();
    qDebug() << _results[needle_target_index] << " " << needle_position;

}

void MainWindow::setNewPosition()
{
    if(_results[needle_target_index] > needle_position)
    {
       direction = (abs(_results[needle_target_index]-needle_position) > 18) ? -1 : 1;
    }
    else
    {
        direction = (abs(_results[needle_target_index]-needle_position) < 18) ? -1 : 1;
    }
    if(abs(_arms[0]->getPosition()-_results[needle_target_index]) < abs((36-_arms[0]->getPosition()+_results[needle_target_index])))
    {
        magnitude = abs(_arms[0]->getPosition()-_results[needle_target_index]);
    }
    else
    {
        magnitude = abs((36-_arms[0]->getPosition()+_results[needle_target_index]));
    }
    timer_2->start(100);
}

void MainWindow::predict()
{
    for(int i{0}; i < 3; ++i) _results[i] = qrand() % 36;
    direction = (abs(needle_position-_results[needle_target_index]) < 18) ? 1 : -1;
    if(abs(_arms[0]->getPosition()-_results[needle_target_index]) < abs((36-_arms[0]->getPosition()+_results[needle_target_index])))
    {
        magnitude = abs(_arms[0]->getPosition()-_results[needle_target_index]);
    }
    else
    {
        magnitude = abs((36-_arms[0]->getPosition()+_results[needle_target_index]));
    }
    timer_2->start(100);
}

