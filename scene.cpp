#include "scene.h"

#include <fstream>
#include <iostream>
using namespace std;

#include "stdlib.h"

#include "MathImplimintation.h"
#include "PointIsNotVisible.h"


Scene::Scene()
{
}

Scene::~Scene()
{

}

void Scene::addNewPoint(Point3D<double> p)
{
    _points.insert(_points.end(),p);
}

int Scene::getCount()
{
    return _points.size();
}

Point3D<double> Scene::getPoint3D(int pos)
{
    if (_points.size() <= pos)
    {
        return NULL;
    }
    return _points.at(pos);
}

Point3D<double> Scene::getPoint3D(Matrix<double>& trans, int pos)
{
    if (_points.size() <= pos)
    {
        return NULL;
    }
    Point3D<double> p = Mult(_points.at(pos), trans);
//    if (p.getZ() == 0)
//    {
//        throw PointIsNotVisible("point is not visible");
////        throw exception();
//    }
//    Point2D<double> result;
//    result.setX(p.getX() / p.getZ());
//    result.setY(p.getY() / p.getZ());

//    return result;
    return p;
}

int Scene::LoadFromFile(string path)
{
    fstream inF;
    inF.open(path.data(), fstream::in);
    if (inF.fail())
    {
        return -1;
    }
    char* xString = new char[100];
    char* yString = new char[100];
    char* zString = new char[100];
    while (!inF.eof())
    {
        inF >> xString;
        double x = atof(xString);
        double y;
        double z;
        if (!inF.eof())
        {
            inF >> yString;
            y = atof(yString);
        }
        else
        {
            break;
        }
        if (!inF.eof())
        {
            inF >> zString;
            z = atof(zString);
        }
        else
        {
            break;
        }
        this->addNewPoint(Point3D<double>(- 1 * x, - 1 * y, z));

    }
    delete[] xString;
    delete[] yString;
    delete[] zString;
    inF.close();
    return 0;
}

void Scene::erase(int pos)
{
    if (_points.size() <= pos)
    {
        return;
    }
    _points.erase(_points.begin() + pos);
}

void Scene::eraseAllPoints()
{
    _points.erase(_points.begin(), _points.begin() + _points.size());
}

int Scene::SaveToFile(string path)
{
    fstream outF;
    outF.open(path.data(), fstream::out);
    int count = getCount();
    Point3D<double> p;
    for (int i = 0; i < count; i++)
    {
        p = _points.at(i);
        outF << p.getX() << " "
             << p.getY() << " "
             << p.getZ() << "\n";
    }
    outF.close();
    return 0;
}

void Scene::updatePoint(int pos, double x, double y, double z)
{
    if (_points.size() <= pos)
    {
        return;
    }
    Point3D<double>& p = _points.at(pos);
    p.setX(x);
    p.setY(y);
    p.setZ(z);
}
