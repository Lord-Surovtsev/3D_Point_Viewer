#include <QApplication>

#include "fpamainform.h"

int main(int argc,char* argv[]) {
    QApplication app(argc,argv);
    app.setApplicationName("five points algorithm");

    FPAMainForm mF;
    mF.show();
    return app.exec();
}
