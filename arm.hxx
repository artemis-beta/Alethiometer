#ifndef ARM_HXX
#define ARM_HXX

#include <QIcon>
#include <cmath>
#include <QPainter>

extern const double pi;

class Arm
{
    private:
        QIcon* _svg = nullptr;
        const QList<int> _dimensions;
        const int _offset;
        const QList<int> _resolution;
        const double _ctr_offset;
        int _position = 0;
    public:
        Arm(const QString& address, const QList<int> resolution, const QList<int> dimensions, const double centre_offset=0, const int offset=0) :
            _svg(new QIcon(address)), _resolution(resolution), _dimensions(dimensions), _offset(offset), _ctr_offset(centre_offset) {}

        void setPosition(const int position);
        int getPosition() const {return _position;}
        double toRad(const double);
        void Paint(QPainter*);
};

#endif // ARM_HXX
