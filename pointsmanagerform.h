#ifndef POINTSMANAGERFORM_H
#define POINTSMANAGERFORM_H

#include <QMainWindow>
#include <QModelIndex>

#include "scene.h"

namespace Ui {
class PointsManagerForm;
}

class PointsManagerForm : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit PointsManagerForm(Scene* scene, QWidget *parent = 0);
    ~PointsManagerForm();
    void UpdatePresentation();
    
private slots:
    void on_lW_Points_clicked(const QModelIndex &index);

    void on_pb_Add_clicked();

    void on_pB_Delete_clicked();

    void on_pB_Update_clicked();

private:
    Ui::PointsManagerForm *ui;
    Scene* _scene;
    int _row;
};

#endif // POINTSMANAGERFORM_H
