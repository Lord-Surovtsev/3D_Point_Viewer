#ifndef FPAMAINFORM_H
#define FPAMAINFORM_H

#include <QMainWindow>
#include <QWorkspace>

#include "scene.h"
#include "viewform.h"
#include "IViewFormManager.h"

namespace Ui {
class FPAMainForm;
}

class FPAMainForm : public QMainWindow, public IViewFormManager
{
    Q_OBJECT
    
public:
    explicit FPAMainForm(QWidget *parent = 0);
    ~FPAMainForm();
    
private slots:
    void on_actionLoad_scene_triggered();

    void on_actionShow_points_triggered();

    void on_actionSave_scene_triggered();

    void on_actionShow_view_triggered();

 public:
    QMainWindow* getMainViewForm();
    void setAsMainViewForm(QMainWindow* viewForm);
    void updateOthers(QMainWindow *viewForm);

private:
    Ui::FPAMainForm *ui;
    QWorkspace* _workspace;
    Scene _scene;
    QMainWindow* _mainViewForm;


};

#endif // FPAMAINFORM_H
