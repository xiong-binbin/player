#ifndef CONTROLBAR_H
#define CONTROLBAR_H

#include <QObject>
#include <QWidget>
#include <QPushButton>

class ControlBar : public QWidget
{
    Q_OBJECT
public:
    explicit ControlBar(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onPlayClicked(bool checked);

public slots:
    void updatePlayStatue(bool start);

private:
    QPushButton *m_playButton;

signals:
    void playEvent();
    void pauseEvent();
};

#endif // CONTROLBAR_H
