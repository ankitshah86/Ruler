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
    leftCmBtn = new QRadioButton();
    leftCmBtn->setText("CM");
    leftInchBtn = new QRadioButton();
    leftInchBtn->setText("Inch");
    leftPxlBtn = new QRadioButton();
    leftPxlBtn->setText("Pixel");
    rightCmBtn = new QRadioButton();
    rightCmBtn->setText("CM");
    rightInchBtn = new QRadioButton();
    rightInchBtn->setText("Inch");
    rightPxlBtn = new QRadioButton();
    rightPxlBtn->setText("Pixel");

    QGroupBox *gl = new QGroupBox("left");
    QGroupBox *gr = new QGroupBox("right");




  /*  QVBoxLayout *vl = new QVBoxLayout();
    vl->addWidget(leftCmBtn);
    vl->addWidget(leftInchBtn);
    vl->addWidget(leftPxlBtn);
    vl->addStretch(1);
    gl->setLayout(vl);

    QVBoxLayout *vr = new QVBoxLayout();
    vr->addWidget(rightCmBtn);
    vr->addWidget(rightInchBtn);
    vr->addWidget(rightPxlBtn);
    vr->addStretch(1);
    gr->setLayout(vr);

    QVBoxLayout *h0 = new QVBoxLayout();
    h0->addStretch(1);

    h0->addWidget(gr);h0->addWidget(gl);
    h0->addStretch(1);




    QVBoxLayout *v = new QVBoxLayout(this);
    v->addLayout(h0);
    v->addStretch(1);
    v->setAlignment(Qt::AlignHCenter);
    v->addWidget(opacitySlider,Qt::AlignHCenter);
    v->addWidget(closeButton,Qt::AlignHCenter);
    v->addStretch(1);

    QHBoxLayout *h1 = new QHBoxLayout();
    leftSide = new Side(scaleSide::leftSide,scaleMarking::Cm,this->height());
    //h1->addWidget(leftSide);
    h1->addLayout(v);
  //  this->setLayout(h1);

*/

    //connect()
    //connect(opacitySlider,SIGNAL(valueChanged(int),this,SLOT(resetOpacity(int)));
   // qDebug()<<this->logicalDpiX()<<this->physicalDpiX();

    connect(opacitySlider,SIGNAL(valueChanged(int)),this,SLOT(resetOpacity(int)));
   /*
    connect(closeButton,SIGNAL(clicked()),this,SLOT(close()));

    connect(leftCmBtn,SIGNAL(clicked()),this,SLOT(updateMarkings()));
    connect(leftInchBtn,SIGNAL(clicked()),this,SLOT(updateMarkings()));*/

    //setWindowFlags(Qt::FramelessWindowHint);
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

void Ruler::updateMarkings()
{
    this->update();
}



void Ruler::paintEvent(QPaintEvent *event)
{
   // return;

   // Q_UNUSED(event)

    /*QPainter painter(this);
     painter.setOpacity(0.5);
     QStyleOption opt;
     opt.initFrom(this);
     QStyle* pStyle =  QApplication::style();
     pStyle->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);

*/
    this->paintcounter++;
    qDebug() << paintcounter;

    this->setMaximumWidth(this->logicalDpiX()*4);
    QPainter painter(this);

    QPen p;
    p.setWidth(1);

    painter.setPen(p);

    int h = 0;
    int i = 0;
  /*  if(leftCmBtn->isChecked()){
        this->paintMarkings(scaleMarking::Cm,scaleSide::leftSide);
    }
    else if(leftInchBtn->isChecked()){
         this->paintMarkings(scaleMarking::Inch,scaleSide::leftSide);
    }*/
   // return;




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

    QDialog::paintEvent(event);
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

void Ruler::paintMarkings(scaleMarking, scaleSide)
{
    this->setMaximumWidth(this->logicalDpiX()*2);
    QPainter painter(this);

    QPen p;
    p.setWidth(1);

    painter.setPen(p);

    int h = 0;
    int i = 0;
    if(leftCmBtn->isChecked()){
        h = int(i * double( this->physicalDpiY() ) / 25.4) ;
    }
    else if(leftInchBtn->isChecked()){
        h = int(i * double( this->physicalDpiY() ) / 10) ;
    }



    //Drawing  markings
    while(h < this->height()){
        if(i%10 == 0)  painter.drawLine(0,h,20,h);
        else if(i%5 == 0) painter.drawLine(0,h,15,h);
        else painter.drawLine(0,h,10,h);
        if(i%10 == 0) painter.drawText(25,h + 5,QString::number(i/10));
        i++;
    }


}


Side::Side(scaleSide side, scaleMarking marking, int height)
{
    this->setMinimumWidth(100);
    this->setMinimumHeight(height);
    this->setMaximumHeight(height);
    this->side = side;
    this->marking = marking;
   // this->setStyleSheet("background-color:black;");
}

Controller::Controller()
{
    this->setMinimumHeight(QApplication::desktop()->screen()->height() * 0.8);
    this->setMinimumWidth(200);
    opacitySlider = new QSlider();
    opacitySlider->setRange(1,100);
    opacitySlider->setMaximumHeight(100);
    opacitySlider->setToolTip("Adjust Transperancy");


    closeButton = new QToolButton();
    closeButton->setText("X");
    leftCmBtn = new QRadioButton();
    leftCmBtn->setText("CM");
    leftInchBtn = new QRadioButton();
    leftInchBtn->setText("Inch");
    leftPxlBtn = new QRadioButton();
    leftPxlBtn->setText("Pixel");
    rightCmBtn = new QRadioButton();
    rightCmBtn->setText("CM");
    rightInchBtn = new QRadioButton();
    rightInchBtn->setText("Inch");
    rightPxlBtn = new QRadioButton();
    rightPxlBtn->setText("Pixel");

     leftSide = new Side(scaleSide::leftSide,scaleMarking::Cm,200);

    QGroupBox *gl = new QGroupBox("left");
    QGroupBox *gr = new QGroupBox("right");




    QVBoxLayout *vl = new QVBoxLayout();
    vl->addWidget(leftCmBtn);
    vl->addWidget(leftInchBtn);
    vl->addWidget(leftPxlBtn);
    vl->addStretch(1);
    gl->setLayout(vl);

    QVBoxLayout *vr = new QVBoxLayout();
    vr->addWidget(rightCmBtn);
    vr->addWidget(rightInchBtn);
    vr->addWidget(rightPxlBtn);
    vr->addStretch(1);
    gr->setLayout(vr);


    QVBoxLayout *v = new QVBoxLayout(this);
    v->addWidget(gr);
    v->addWidget(gl);
    v->setAlignment(Qt::AlignHCenter);
    v->addWidget(opacitySlider,Qt::AlignHCenter);
    v->addWidget(closeButton,Qt::AlignHCenter);
    v->addStretch(1);


    QGraphicsView *view = new QGraphicsView;
    view->setMinimumSize(300,this->height());
    QHBoxLayout *h1 = new QHBoxLayout();
    h1->addWidget(view);
    h1->addWidget(leftSide);
    h1->addLayout(v);
    this->setLayout(h1);



}
