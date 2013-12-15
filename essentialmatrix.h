#ifndef ESSENTIALMATRIX_H
#define ESSENTIALMATRIX_H

#include "Matrix.h"
#include "Point3D.h"
#include "Point2D.h"
#include "JoinedCoordinates.h"

class EssentialMatrix
{
public:
    EssentialMatrix(int count
                    , Point3D<double>* fP3D, Point3D<double>* sP3D
                    , Point2D<double>** fP2D, Point2D<double>** sP2D);
    virtual ~EssentialMatrix();

    void CalculateJC();
    void EstiamteAMatrix();

private:
    Matrix<double>* _matrix;
    int _count;
    Point3D<double>* _fP3D;
    Point3D<double>* _sP3D;
    Point2D<double>** _fP2D;
    Point2D<double>** _sP2D;

    JoinedCoordinates** _jC;

};

#endif // ESSENTIALMATRIX_H
