#include "viewform.h"
#include "ui_viewform.h"

#include "stdio.h"
#include "math.h"

#include "PointIsNotVisible.h"
#include "MathRotation.h"
#include "MathImplimintation.h"

#include "CheckEssentialMatrix.h"

#include "essentialmatrix.h"

#include <iostream>
using namespace std;


ViewForm::ViewForm(IViewFormManager* mF, Scene *scene, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewForm)
{
    ui->setupUi(this);
    _scene = scene;
    _mainForm = mF;

    _gScene = new QGraphicsScene(this);
    ui->graphicsView->setScene(_gScene);

    UpdatePresentation();
}

ViewForm::~ViewForm()
{
    delete ui;
}


void ViewForm::UpdatePresentation()
{
    if (_mainForm->getMainViewForm() == this)
    {
        this->ui->lbl_FlagMain->setText("this is main window");
        this->ui->hS_Focus->setVisible(true);
        this->ui->pB_Calculate->setVisible(false);
    }
    else
    {
        this->ui->lbl_FlagMain->setText("this is not main window");
        ViewForm* vF = qobject_cast<ViewForm*>(_mainForm->getMainViewForm());
        if (vF != NULL)
        {
            this->ui->hS_Focus->setVisible(false);
            this->ui->pB_Calculate->setVisible(true);
            _transfParams.focus = vF->getFocus();
            Matrix<double> eM = essentialMatrix(_transfParams);
        }
        else
        {
            this->ui->pB_Calculate->setVisible(false);
        }
    }
    char* buffer = new char[100];
    sprintf(buffer, "%f", _transfParams.focus);
    ui->lbl_valueFocus->setText(buffer);
    sprintf(buffer, "%f", _transfParams.angleX);
    ui->lbl_valueX->setText(buffer);
    sprintf(buffer, "%f", _transfParams.angleY);
    ui->lbl_valueY->setText(buffer);
    sprintf(buffer, "%f", _transfParams.angleZ);
    ui->lbl_valueZ->setText(buffer);

    sprintf(buffer, "%f", _transfParams.dX);
    ui->lbl_valueDX->setText(buffer);
    sprintf(buffer, "%f", _transfParams.dY);
    ui->lbl_valueDY->setText(buffer);
    sprintf(buffer, "%f", _transfParams.dZ);
    ui->lbl_valueDZ->setText(buffer);
    delete[] buffer;
    DrawScene();
//    QBrush redBrush(Qt::red);
//    QBrush blueBrush(Qt::blue);
//    QPen blackPen(Qt::black);
//    blackPen.setWidth(6);

//    _gEllipse = _gScene->addEllipse(10, 10, 100, 100, blackPen, redBrush);

//    _gRect = _gScene->addRect(-100, -100, 50, 50, blackPen, blueBrush);

//    _gRect->setFlag(QGraphicsItem::ItemIsMovable);
//    _gEllipse->setFlag(QGraphicsItem::ItemIsMovable);
}

Point3D<double>* ViewForm::getPoints3D()
{
//    Matrix<double> translition = essentialMatrix(_transfParams);
    Matrix<double> translition = getTranslitionMatrix();
    if (_mainForm->getMainViewForm() != this)
    {
        ViewForm* vF = qobject_cast<ViewForm*>(_mainForm->getMainViewForm());
        if (vF != NULL)
        {
            Matrix<double> tr = vF->getTranslitionMatrix();
            Matrix<double> tmp = MultMatr<double>(tr, translition);
            translition = tmp;
       }
    }

    int count = _scene->getCount();
    Point3D<double>* result = new Point3D<double>[count];

    for (int i = 0; i < count; i++)
    {
        result[i] = _scene->getPoint3D(translition, i);
    }
    return result;
}

Point2D<double>** ViewForm::getPoints2D()
{
    Point3D<double>* p3D = getPoints3D();
    int count = _scene->getCount();
    Point2D<double>** result = new Point2D<double>*[count];
    for (int i = 0; i < count; i++)
    {
        int z = p3D[i].getZ();
        if (z == 0)
        {
            result[i] = NULL;
        }
        else
        {
            double x = p3D[i].getX() / z;// * _transfParams.focus;
            double y = p3D[i].getY() / z;// * _transfParams.focus;
            result[i] = new Point2D<double>(x, y);
        }
    }
    delete[] p3D;
    return result;
}

void ViewForm::DrawScene()
{
    _gScene->clear();
    int count = _scene->getCount();
    Point2D<double>** points2D = getPoints2D();
    QPen blackPen(Qt::black);

    for (int i = 0; i < count; i++)
    {
        if (points2D[i] == NULL)
        {
            continue;
        }
        int x = -1 * points2D[i]->getX() * _transfParams.focus;
        int y = -1 * points2D[i]->getY() * _transfParams.focus;
        _gScene->addLine(x - 1, y - 1, x + 1, y + 1, blackPen);
        delete points2D[i];
    }
    delete[] points2D;
}

//void ViewForm::paintEvent(QPaintEvent *)
//{
//    QPainter p;
//    p.begin(this->ui->graphicsView);
//    p.drawLine(0, 0, 10, 20);
//    p.drawText(20, 20, 20, 20, NULL, "1", NULL);
//    p.drawText(50, 50, 20, 20, NULL, "11", NULL);
//    p.end();
//}

void ViewForm::on_hS_X_sliderMoved(int position)
{
    _transfParams.angleX = ui->hS_X->value();
    UpdatePresentation();
}

void ViewForm::on_hS_Y_sliderMoved(int position)
{
    _transfParams.angleY = ui->hS_Y->value();
    UpdatePresentation();
}

void ViewForm::on_hS_Z_sliderMoved(int position)
{
    _transfParams.angleZ = ui->hS_Z->value();
    UpdatePresentation();
}

void ViewForm::on_hS_dX_sliderMoved(int position)
{
    _transfParams.dX = ui->hS_dX->value();
    UpdatePresentation();
}

void ViewForm::on_hS_dY_sliderMoved(int position)
{
    _transfParams.dY = ui->hS_dY->value();
    UpdatePresentation();
}

void ViewForm::on_hS_dZ_sliderMoved(int position)
{
    _transfParams.dZ = ui->hS_dZ->value();
    UpdatePresentation();
}

void ViewForm::on_hS_Focus_sliderMoved(int position)
{
    _transfParams.focus = ui->hS_Focus->value();
    UpdatePresentation();
}

void ViewForm::on_pB_setAsMain_clicked()
{
    _mainForm->setAsMainViewForm(this);
    UpdatePresentation();
}

double ViewForm::getFocus()
{
    return _transfParams.focus;
}

Matrix<double> ViewForm::getTranslitionMatrix()
{
    return translitionMatrix(_transfParams);
//    return essentialMatrix(_transfParams)
}

void ViewForm::on_pB_Calculate_clicked()
{
    if (_mainForm->getMainViewForm() != this)
    {
        ViewForm* vF = qobject_cast<ViewForm*>(_mainForm->getMainViewForm());
        if (vF != NULL)
        {
            Point3D<double>* fP3D = vF->getPoints3D();
            Point3D<double>* sP3D = this->getPoints3D();
            Point2D<double>** fP2D = vF->getPoints2D();
            Point2D<double>** sP2D = this->getPoints2D();


//            Matrix<double> eM = Transpose(essentialMatrix(_transfParams));

            int c = _scene->getCount();

//            for (int i = 0; i < c; i++)
//            {
//                if ((fP2D[i] != NULL) && (sP2D[i] != NULL))
//                {
//                    cout << i
//                         << ": " << fP3D[i].getX()
//                         << ": " << fP3D[i].getY()
//                         << ": " << fP3D[i].getZ()
//                         << "/ " << fP2D[i]->getX()
//                         << ": " << fP2D[i]->getY()
//                         << ": " << 1
//                         << endl;
//                    cout << i
//                         << ": " << sP3D[i].getX()
//                         << ": " << sP3D[i].getY()
//                         << ": " << sP3D[i].getZ()
//                         << "/ " << sP2D[i]->getX()
//                         << ": " << sP2D[i]->getY()
//                         << ": " << 1
//                         << endl;
//                }
//            }

//            for (int i = 0; i < c; i++)
//            {
//                if ((fP2D[i] != NULL) &&  (sP2D[i] != NULL))
//                {
//                    int res = CheckFirstTheorem1<double>(*(fP2D[i]), eM, *(sP2D[i]));
//                    cout << i << " : " << res << endl;
////                    res = CheckFirstTheorem<double>(*(sP2D[i]), eM, *(fP2D[i]));
////                    cout << i << " : " << res << endl;
//                }
////                int res = CheckFirstTheorem<double>(fP3D[i], eM, sP3D[i]);
////                cout << i << " : " << res << endl;
//            }
            EssentialMatrix eM(this->_scene->getCount()
                               , fP3D, sP3D
                               , fP2D, sP2D);
            eM.CalculateJC();
            eM.EstiamteAMatrix();

            delete[] fP3D;
            delete[] sP3D;
            int count = _scene->getCount();
            for (int i = 0; i < count; i++)
            {
                if (fP2D[i] != NULL)
                {
                    delete fP2D[i];
                }
                if (sP2D[i] != NULL)
                {
                    delete sP2D[i];
                }
            }
            delete[] fP2D;
            delete[] sP2D;
        }
    }
}
