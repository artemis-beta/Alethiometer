/*
    Simulation of the Alethiometer present in the "His Dark Materials" trilogy by
    Philip Pullman.
    Copyright (C) 2020 Kristian Zarebski

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
