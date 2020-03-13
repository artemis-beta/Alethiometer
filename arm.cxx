#include "arm.hxx"

const extern double pi = 4*atan(1);

double Arm::toRad(const double a)
{
    return a*pi/180.;
}

void Arm::Paint(QPainter* painter)
{
    const double angle = toRad(10*getPosition());
    const QPixmap _pxmap = _svg->pixmap(QSize(_dimensions[0], _dimensions[1]));
    painter->save();
    painter->translate(_resolution[1]/2., _resolution[1]/2.-_ctr_offset);
    painter->rotate(10*getPosition());
    painter->translate(-_dimensions[0]/2.,-_dimensions[1]+_offset);
    painter->drawPixmap(0, 0, _dimensions[0], _dimensions[1], _pxmap);
    painter->restore();
}

void Arm::setPosition(const int position)
{
    if(position > 35) _position = position - 36;
    else if(position < 0) _position = 36 + position;
    else _position = position;
}
