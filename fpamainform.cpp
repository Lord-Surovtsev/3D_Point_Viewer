#include "fpamainform.h"
#include "ui_fpamainform.h"

#include <QFileDialog>
#include <QMessageBox>

#include "stdio.h"

#include "pointsmanagerform.h"
#include "viewform.h"

FPAMainForm::FPAMainForm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::FPAMainForm)
{
    ui->setupUi(this);
    _workspace = new QWorkspace();
    setCentralWidget(_workspace);
    _mainViewForm = NULL;
}

FPAMainForm::~FPAMainForm()
{
    delete _workspace;
    delete ui;
}

void FPAMainForm::on_actionLoad_scene_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this
                                                    , tr("Load scene")
                                                    , QDir::currentPath()
                                                    , tr("scene (*.scene)"));
    if (fileName != NULL)
    {
        _scene.LoadFromFile(fileName.toUtf8().data());
//        QMessageBox mB;
//        char buffer[10];
//        sprintf(buffer, "%d",  _scene.getCount());
//        mB.setText(buffer);
//        mB.setModal(false);
//        mB.exec();
    }
}

void FPAMainForm::on_actionShow_points_triggered()
{
    PointsManagerForm* pMF = new PointsManagerForm(&_scene, this);
    _workspace->addWindow(pMF);
    pMF->show();
}

void FPAMainForm::on_actionSave_scene_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this
                                                    , tr("Save scene")
                                                    , QDir::currentPath()
                                                    , tr("scene (*.scene)"));
    if (fileName != NULL)
    {
        _scene.SaveToFile(fileName.toUtf8().data());
//        QMessageBox mB;
//        char buffer[10];
//        sprintf(buffer, "%d",  _scene.getCount());
//        mB.setText(buffer);
//        mB.setModal(false);
//        mB.exec();
    }
}

void FPAMainForm::on_actionShow_view_triggered()
{
    ViewForm* vF = new ViewForm(this, &_scene, this);
    _workspace->addWindow(vF);
    vF->show();
}

QMainWindow* FPAMainForm::getMainViewForm()
{
    return _mainViewForm;
}

void FPAMainForm::setAsMainViewForm(QMainWindow *viewForm)
{
    _mainViewForm = viewForm;
}

void FPAMainForm::updateOthers(QMainWindow *viewForm)
{

}
