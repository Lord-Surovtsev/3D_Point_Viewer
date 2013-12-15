#ifndef JOINEDCOORDINATES_H
#define JOINEDCOORDINATES_H

#include "Point2D.h"
#include "CustomException.h"

class JoinedCoordinates
{
public:
    JoinedCoordinates(Point2D<double> fP, Point2D<double> sP)
    {
        _q = new double[9];

        double x1 = fP.getX();
        double y1 = fP.getY();
        double x2 = sP.getX();
        double y2 = sP.getY();

        //q1: matrix([x1 * x2, y1 * x2, x2
        //          , x1 * y2, y1 * y2, y2
        //          , x1,  y1, 1]);
        _q[0] = x1 * x2;
        _q[1] = y1 * x2;
        _q[2] = x2;
        _q[3] = x1 * y2;
        _q[4] = y1 * y2;
        _q[5] = y2;
        _q[6] = x1;
        _q[7] = y1;
        _q[8] = 1;

    }

    double get(int i){
        if ((i < 0) or (i > 8))
        {
            throw new CustomException("wrong index");
        }
        return _q[i];
    }

    virtual ~JoinedCoordinates()
    {
        delete[] _q;
    }

private:
    double* _q;
};

#endif // JOINEDCOORDINATES_H
