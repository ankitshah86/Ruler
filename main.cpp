#include <QApplication>
#include <QtWidgets>
#include "ruler.h"


int main(int argc, char * argv[]){

    QApplication app(argc,argv);

    Controller c;
    c.show();

    return app.exec();
}
