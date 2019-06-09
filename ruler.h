#ifndef RULER_H
#define RULER_H


#include <QPaintEvent>
#include <QtWidgets>



enum scaleSide { leftSide, rightSide };
enum scaleMarking { Inch, Cm, Pixel };


class Side: public QWidget
{
    Q_OBJECT

public:
    Side(scaleSide side,scaleMarking marking, int height );

private:
    scaleSide side;
    scaleMarking marking;


};

class Controller : public QWidget
{
    Q_OBJECT

public:
    Controller();

private:
    QSlider *opacitySlider;
    bool isMousePressed = false;
    int mousePressX,mousePressY;
    QToolButton *closeButton;

    Side *leftSide, *rightSide;

    QRadioButton * leftCmBtn, *leftInchBtn, *leftPxlBtn;
    QRadioButton * rightCmBtn, *rightInchBtn, *rightPxlBtn;

public slots:


};


class Ruler : public QDialog
{
    Q_OBJECT




public:
    Ruler();
    QSlider *opacitySlider;
    bool isMousePressed = false;
    int mousePressX,mousePressY;
    QToolButton *closeButton;

    Side *leftSide, *rightSide;

    QRadioButton * leftCmBtn, *leftInchBtn, *leftPxlBtn;
    QRadioButton * rightCmBtn, *rightInchBtn, *rightPxlBtn;
    int paintcounter = 0;

public slots:
    void resetOpacity(int op);
    void updateMarkings();
protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void paintMarkings(scaleMarking,scaleSide);
};


#endif // RULER_H
