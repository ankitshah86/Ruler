#ifndef RULER_H
#define RULER_H


#include <QPaintEvent>
#include <QtWidgets>


class Ruler : public QDialog
{
    Q_OBJECT



public:
    Ruler();
    QSlider *opacitySlider;
    bool isMousePressed = false;
    int mousePressX,mousePressY;
    QToolButton *closeButton;

public slots:
    void resetOpacity(int op);
protected:
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
};

#endif // RULER_H
