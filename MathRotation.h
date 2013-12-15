#ifndef MATHROTATION_H
#define MATHROTATION_H

#define PI 3.14159265

#include <iostream>
using namespace std;

#include "Matrix.h"
#include "MathImplimintation.h"
#include "TransformationParameters.h"
#include "CustomException.h"

Matrix<double> rotX(TransformationParameters& transfParams)
{
    Matrix<double> rotX(3, 3);

    double angle = transfParams.angleX * PI / 180;

    rotX[0][0] = 1;
    rotX[1][0] = 0;
    rotX[2][0] = 0;

    rotX[0][1] = 0;
    rotX[1][1] = cos(angle);
    rotX[2][1] = -1 * sin (angle);

    rotX[0][2] = 0;
    rotX[1][2] = sin(angle);
    rotX[2][2] = cos(angle);

    return rotX;
}

Matrix<double> rotY(TransformationParameters& transfParams)
{
    Matrix<double> rotY(3, 3);

    double angle = transfParams.angleY * PI / 180;

    rotY[0][0] = cos(angle);
    rotY[1][0] = 0;
    rotY[2][0] = sin(angle);

    rotY[0][1] = 0;
    rotY[1][1] = 1;
    rotY[2][1] = 0;

    rotY[0][2] = -1 * sin(angle);
    rotY[1][2] = 0;
    rotY[2][2] = cos(angle);

    return rotY;
}

Matrix<double> rotZ(TransformationParameters& transfParams)
{
    Matrix<double> rotZ(3, 3);

    double angle = transfParams.angleZ * PI / 180;

    rotZ[0][0] = cos(angle);
    rotZ[1][0] = -1 * sin(angle);
    rotZ[2][0] = 0;

    rotZ[0][1] = sin(angle);
    rotZ[1][1] = cos(angle);
    rotZ[2][1] = 0;

    rotZ[0][2] = 0;
    rotZ[1][2] = 0;
    rotZ[2][2] = 1;

    return rotZ;
}

Matrix<double> translation(TransformationParameters& transfParams)
{
    Matrix<double> tr(4, 4);

    tr[0][0] = 1;
    tr[1][1] = 1;
    tr[2][2] = 1;
    tr[3][3] = 1;

    tr[3][0] = transfParams.dX;
    tr[3][1] = transfParams.dY;
    tr[3][2] = transfParams.dZ;
    return tr;
}

Matrix<double> rotationMatrix(TransformationParameters& transfParams)
{
    Matrix<double> rX = rotX(transfParams);
    Matrix<double> rY = rotY(transfParams);
    Matrix<double> rZ = rotZ(transfParams);

    Matrix<double> rXY = MultMatr<double>(rX, rY);
    Matrix<double> rXYZ = MultMatr<double>(rXY, rZ);

    return rXYZ;
}

Matrix<double> translitionMatrix(TransformationParameters& transfParams)
{
    Matrix<double> rot = rotationMatrix(transfParams);
    Matrix<double> r = ResizeMatrix(rot, 4, 4);
    r[3][3] = 1;

    Matrix<double> tr = translation(transfParams);

    Matrix<double> result = MultMatr<double>(r, tr);
//    Matrix<double> result = Mult<double>(tr, rot);

//    cout << "-----\n";
//    for (int j = 0; j < 4; j++)
//    {
//        for (int i = 0; i < 4; i++)
//        {
//            cout << result[i][j] << " ";
//        }
//        cout << "\n";
//    }
//    cout.flush();
//    cout << "\---------\n";
    return result;
}

Matrix<double> tx(TransformationParameters& transfParams)
{
    Matrix<double> tr(3, 3);

    tr[0][0] = 0;
    tr[1][0] = -1 * transfParams.dZ;
    tr[2][0] = transfParams.dY;

    tr[0][1] = transfParams.dZ;
    tr[1][1] = 0;
    tr[2][1] = -1 * transfParams.dX;

    tr[0][2] = -1 * transfParams.dY;
    tr[1][2] = transfParams.dX;
    tr[2][2] = 0;

    return tr;
}

double Determinant(Matrix<double> m, int colCount, int rowCount)
{
    if ((3 != colCount) || (3 != rowCount))
    {
        throw new CustomException("I can not calculate determinant for matrix that size is bigger than 3x3");
    }
    double det = m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1])
               - m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0])
               + m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][1]);
    return det;
}

Matrix<double> essentialMatrix(TransformationParameters& transfParams)
{
    Matrix<double> rot = rotationMatrix(transfParams);
    Matrix<double> tr = tx(transfParams);

    Matrix<double> result = MultMatr<double>(rot, tr);
//    Matrix<double> result = Mult<double>(tr, rot);

    cout << "essential-matrix-----\n";
    result.Print();
    cout << "end-of-essential-matrix---------\n";

    double det = Determinant(result, 3, 3);
    cout << det << endl;

    return result;
}

#endif // MATHROTATION_H
