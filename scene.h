#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <string>
using namespace std;

#include "Point3D.h"
#include "Point2D.h"
#include "Matrix.h"
#include "Array.h"

class Scene
{
public:
    Scene();
    virtual ~Scene();
    void addNewPoint(Point3D<double> p);
    void erase(int pos);
    void eraseAllPoints();
    int getCount();
    Point3D<double> getPoint3D(int pos);
    Point3D<double> getPoint3D(Matrix<double>& trans, int pos);
    int LoadFromFile(string path);
    int SaveToFile(string path);
    void updatePoint(int pos, double x, double y, double z);


private:
    vector< Point3D<double> > _points;


};

#endif // SCENE_H
