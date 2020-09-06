#ifndef VIEWWINDOW_H
#define VIEWWINDOW_H

#include <QObject>
#include <QWidget>

class ViewWindow : public QWidget
{
    Q_OBJECT
public:
    explicit ViewWindow(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // VIEWWINDOW_H
