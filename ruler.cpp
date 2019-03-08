#include "ruler.h"
#include <QPainter>
#include <QStyleOption>
#include <QApplication>
#include <iostream>
#include <QDebug>



using namespace  std;

Ruler::Ruler()
{
    setWindowOpacity(1);


    this->setMinimumHeight(QApplication::desktop()->screen()->height() * 0.8);
    this->setMinimumWidth(200);
    opacitySlider = new QSlider();
    opacitySlider->setRange(1,100);
    opacitySlider->setMaximumHeight(100);
    opacitySlider->setToolTip("Adjust Transperancy");


    closeButton = new QToolButton();
    closeButton->setText("X");



    QVBoxLayout *v = new QVBoxLayout(this);
    v->setAlignment(Qt::AlignHCenter);
    v->addWidget(opacitySlider,Qt::AlignHCenter);
    v->addWidget(closeButton,Qt::AlignHCenter);
    this->setLayout(v);


    //connect()
    //connect(opacitySlider,SIGNAL(valueChanged(int),this,SLOT(resetOpacity(int)));
  qDebug()<<this->logicalDpiX()<<this->physicalDpiX();


  connect(opacitySlider,SIGNAL(valueChanged(int)),this,SLOT(resetOpacity(int)));
  connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));
  //  setWindowFlags(Qt::FramelessWindowHint);
   /* setAttribute(Qt::WA_NoSystemBackground);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_TransparentForMouseEvents);
    this->setWindowTitle("Scale");
    setStyleSheet("background-color: rgba(0,0,0,0)");*/

  }

void Ruler::resetOpacity(int op)
{
    qDebug()<<op;
    this->setWindowOpacity(1 - op/120.0);
}



void Ruler::paintEvent(QPaintEvent *event)
{

    Q_UNUSED(event)

    /*QPainter painter(this);
     painter.setOpacity(0.5);
     QStyleOption opt;
     opt.initFrom(this);
     QStyle* pStyle =  QApplication::style();
     pStyle->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

*/

    this->setMaximumWidth(this->logicalDpiX()*2);

    QPainter painter(this);

    QPen p;
    p.setWidth(1);

    painter.setPen(p);



    int h = 0;
    int i = 0;

    //Drawing Centimeter markings
    while(h < this->height()){

        h = int(i * double( this->physicalDpiY() ) /25.4) ;
        if(i%10 == 0)  painter.drawLine(0,h,20,h);
        else if(i%5 == 0) painter.drawLine(0,h,15,h);
        else painter.drawLine(0,h,10,h);

        if(i%10 == 0) painter.drawText(25,h + 5,QString::number(i/10));

        i++;
    }

    h = 0;
    i = 0;
    int w = this->width();

    //Drawing Inch Markings
    while (h < this->height()) {
        h = int(i * double(this->physicalDpiY())/10);
        if(i%10 == 0)  painter.drawLine(w,h,w-20,h);
        else if(i%5 == 0) painter.drawLine(w,h,w-15,h);
        else painter.drawLine(w,h,w-10,h);

        if(i%10 == 0) painter.drawText(w-35,h + 5,QString::number(i/10));

        i++;

    }

}

void Ruler::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<event->pos();
    isMousePressed = true;
    mousePressX = event->x();
    mousePressY = event->y();
}

void Ruler::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)
    isMousePressed = false;
}

void Ruler::mouseMoveEvent(QMouseEvent *event)
{
    if(isMousePressed){
        move(event->globalX() - mousePressX,event->globalY() -mousePressY);
    }
}
