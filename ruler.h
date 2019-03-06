#ifndef RULER_H
#define RULER_H

#include <QDialog>
#include <QPaintEvent>

class Ruler : public QDialog
{
public:
    Ruler();
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // RULER_H
