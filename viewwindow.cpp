#include "viewwindow.h"
#include <QStyleOption>
#include <QPainter>


ViewWindow::ViewWindow(QWidget *parent) : QWidget(parent)
{

}

void ViewWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
