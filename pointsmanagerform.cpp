#include "pointsmanagerform.h"
#include "ui_pointsmanagerform.h"

#include <string>

#include "stdio.h"

#include <iostream>
using namespace std;

PointsManagerForm::PointsManagerForm(Scene* scene, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PointsManagerForm)
{
    static PointsManagerForm* _instance;
    if (_instance != NULL)
    {
        delete _instance;
        _instance = this;
    }
    else
    {
        _instance = this;
    }
    ui->setupUi(this);
    _scene = scene;
    this->UpdatePresentation();
}

PointsManagerForm::~PointsManagerForm()
{
    delete ui;
}

void PointsManagerForm::UpdatePresentation()
{
    int count = _scene->getCount();
    this->ui->lW_Points->clear();
    char* buffer = new char[100];
    for (int i = 0; i < count; i++)
    {
        Point3D<double> p = _scene->getPoint3D(i);
        sprintf(buffer, "x = %f; y = %f; z = %f", p.getX(), p.getY(), p.getZ());
        this->ui->lW_Points->addItem(buffer);
    }
    delete[] buffer;
}

void PointsManagerForm::on_lW_Points_clicked(const QModelIndex &index)
{
    int i = this->ui->lW_Points->currentRow();
    Point3D<double> p = _scene->getPoint3D(i);
    char* buffer = new char[100];
    sprintf(buffer, "%f", p.getX());
    this->ui->lE_CoordX->setText(buffer);
    sprintf(buffer, "%f", p.getY());
    this->ui->lE_CoordY->setText(buffer);
    sprintf(buffer, "%f", p.getZ());
    this->ui->lE_CoordZ->setText(buffer);
    _row = this->ui->lW_Points->currentRow();
    delete[] buffer;
}

void PointsManagerForm::on_pb_Add_clicked()
{
    double x = atof(this->ui->lE_CoordX->text().toUtf8().data());
    double y = atof(this->ui->lE_CoordY->text().toUtf8().data());
    double z = atof(this->ui->lE_CoordZ->text().toUtf8().data());
    this->_scene->addNewPoint(Point3D<double>(x, y, z));
    this->UpdatePresentation();
}

void PointsManagerForm::on_pB_Delete_clicked()
{
    if (_row < 0)
    {
        return;
    }
    _scene->erase(_row);
    this->UpdatePresentation();
}

void PointsManagerForm::on_pB_Update_clicked()
{
    if (_row < 0)
    {
        return;
    }
    double x = atof(this->ui->lE_CoordX->text().toUtf8().data());
    double y = atof(this->ui->lE_CoordY->text().toUtf8().data());
    double z = atof(this->ui->lE_CoordZ->text().toUtf8().data());
    _scene->updatePoint(_row, x, y, z);
    this->UpdatePresentation();
}
