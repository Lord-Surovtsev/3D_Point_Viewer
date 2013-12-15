#ifndef VIEWFORM_H
#define VIEWFORM_H

#include <QMainWindow>
#include <QtCore>
#include <QtGui>

#include "scene.h"
#include "TransformationParameters.h"
#include "IViewFormManager.h"
#include "Matrix.h"

namespace Ui {
class ViewForm;
}

class ViewForm : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit ViewForm(IViewFormManager* mF, Scene* scene, QWidget *parent = 0);
    ~ViewForm();
    
//protected:
//    void paintEvent(QPaintEvent *);

private slots:
    void on_hS_X_sliderMoved(int position);

    void on_hS_Y_sliderMoved(int position);

    void on_hS_Z_sliderMoved(int position);

    void on_hS_dX_sliderMoved(int position);

    void on_hS_dY_sliderMoved(int position);

    void on_hS_dZ_sliderMoved(int position);

    void on_pB_setAsMain_clicked();

    void on_hS_Focus_sliderMoved(int position);

    void on_pB_Calculate_clicked();

public:
    void UpdatePresentation();
    Matrix<double> getTranslitionMatrix();
    double getFocus();

private:
    void DrawScene();
    Point3D<double>* getPoints3D();
    Point2D<double>** getPoints2D();

private:
    Ui::ViewForm *ui;
    Scene* _scene;
    TransformationParameters _transfParams;
    IViewFormManager* _mainForm;
    QGraphicsScene* _gScene;
//    QGraphicsEllipseItem* _gEllipse;
//    QGraphicsRectItem* _gRect;
};

#endif // VIEWFORM_H
