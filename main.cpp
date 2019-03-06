#include <QApplication>
#include <QtWidgets>
#include "ruler.h"


int main(int argc, char * argv[]){

    QApplication app(argc,argv);

    Ruler s;
    s.show();

    return app.exec();
}
