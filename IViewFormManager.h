#ifndef IVIEWFORMMANAGER_H
#define IVIEWFORMMANAGER_H

#include <QMainWindow>

class IViewFormManager
{
public:
    virtual QMainWindow* getMainViewForm() = 0;
    virtual void setAsMainViewForm(QMainWindow* viewForm) = 0;
    virtual void updateOthers(QMainWindow* viewForm) = 0;
};

#endif // IVIEWFORMMANAGER_H
