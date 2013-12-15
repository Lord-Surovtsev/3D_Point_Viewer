#include "essentialmatrix.h"

#include "AMatrix.h"
#include "Matrix.h"
//#include "MathRotation.h"
#include "MathImplimintation.h"

#include <iostream>
using namespace std;

EssentialMatrix::EssentialMatrix(int count
                                 , Point3D<double>* fP3D, Point3D<double>* sP3D
                                 , Point2D<double>** fP2D, Point2D<double>** sP2D)
{
    _matrix = new Matrix<double>(3, 3);
    _fP3D = fP3D;
    _sP3D = sP3D;
    _fP2D = fP2D;
    _sP2D = sP2D;
    _count = count;

    _jC = new JoinedCoordinates*[_count];
    for (int i = 0; i < _count; i++)
    {
        _jC[i] = NULL;
    }
}

EssentialMatrix::~EssentialMatrix()
{
    delete _matrix;
//    for (int i = 0; i <_count; i++)
//    {
//        delete _fP2D[i];
//        delete _sP2D[i];
//    }
//    delete[] _fP3D;
//    delete[] _sP3D;
//    delete[] _fP2D;
//    delete[] _sP2D;
}

void EssentialMatrix::CalculateJC()
{
    for (int i = 0; i < _count; i++)
    {
        Point2D<double>* fP = _fP2D[i];
        Point2D<double>* sP = _sP2D[i];
        if ((NULL == fP) || (NULL == sP))
        {
            _jC[i] = NULL;
        }
        else
        {
            _jC[i] = new JoinedCoordinates(*fP, *sP);
        }
    }
}

void EssentialMatrix::EstiamteAMatrix()
{
    AMatrix aM(_jC, _count);
    double** matrix = aM.getMatrix();
    int colCount = aM.getColCount();
    int rowCount = aM.getRowCount();
    cout << "colCount " << colCount << " rowCount " << rowCount << endl;
//    return;

    for (int j = 0; j < rowCount; j++)
    {
        for (int i = 0; i < colCount; i++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout << "-------------------------\n";
    cout.flush();

    aM.SimplifyMatrix();
    matrix = aM.getMatrix();

    for (int j = 0; j < rowCount; j++)
    {
        for (int i = 0; i < colCount; i++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
    cout.flush();

    int diagCount = aM.getRowCount();
    if (diagCount > 9)
    {
        diagCount = 9;
    }
    double* diag = aM.getDiag();
    Matrix<double> m(3, 3);

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int index = j * 3 + i;
            if (index > diagCount)
            {
                m[i][j] = 0;
            }
            else
            {
                m[i][j] = diag[j * 3 + i];
            }
        }
    }

    delete[] diag;

    double det = m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
               - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
               + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][1]);
    m.Print();

    Matrix<double> dM = Transpose(m);
    cout << "determinant is " << det << endl;
//    cout << "determinant is " << Determinant(m, 3, 3) << endl;
    cout.flush();
//    for (int i = 0; i < _count; i++)
//    {
//        Point2D<double>* fP = _fP2D[i];
//        Point2D<double>* sP = _sP2D[i];
//        if ((NULL != fP) || (NULL != sP))
//        {


//        }
//    }

}
