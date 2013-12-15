#ifndef CHECKESSENTIALMATRIX_H
#define CHECKESSENTIALMATRIX_H

#include "Point2D.h"
#include "Point3D.h"
#include "Matrix.h"
#include "MathImplimintation.h"

#include <iostream>
using namespace std;

template<class A>
int CheckFirstTheorem1(Point2D<A>& p1, Matrix<A>& e, Point2D<A>& p2)
{
    Matrix<A>* m1 = new Matrix<A>(3, 1);
    Matrix<A>* m2 = new Matrix<A>(1, 3);
    (*m1)[0][0] = p1.getX();
    (*m1)[1][0] = p1.getY();
    (*m1)[2][0] = 1;

    (*m2)[0][0] = p2.getX();
    (*m2)[0][1] = p2.getY();
    (*m2)[0][2] = 1;
    Matrix<A> M = MultMatr<A>(*m1, e);

//    m1->Print("point1");
//    m2->Print("point2");
//    e.Print("essentialMatrix");
//    M.Print("M");

    return (MultMatr<A>(M, *m2)[0][0]);
//    if (MultMatr<A>(M, *m2)[0][0] == 0)
////    Matrix<A> M = Mult<A>(Matrix<A>((NormImgCoord<A>)p1), e);
////    if (Mult<A>(M, Matrix<A>((NormImgCoord<A>)p2))[0][0] == 0)
//    {
//        return 1;
//    }
//    return 0;
}

template<class A>
int CheckFirstTheorem(Point3D<A>& p1, Matrix<A>& e, Point3D<A>& p2)
{
    Matrix<A>* m1 = new Matrix<A>(3, 1);
    Matrix<A>* m2 = new Matrix<A>(1, 3);
    (*m1)[0][0] = p1.getX();
    (*m1)[1][0] = p1.getY();
    (*m1)[2][0] = p1.getZ();

    (*m2)[0][0] = p2.getX();
    (*m2)[0][1] = p2.getY();
    (*m2)[0][2] = p2.getZ();
    Matrix<A> M = MultMatr<A>(*m1, e);

//    m1->Print("point1");
//    m2->Print("point2");
//    e.Print("essentialMatrix");
//    M.Print("M");

    return (MultMatr<A>(M, *m2)[0][0]);
}

#endif // CHECKESSENTIALMATRIX_H
