#include "controlbar.h"
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include <QDebug>

ControlBar::ControlBar(QWidget *parent) : QWidget(parent)
{
    setFixedHeight(70);
    m_playButton = new QPushButton(this);
    m_playButton->setFixedSize(50, 50);
    m_playButton->setObjectName("playButton");
    m_playButton->setCheckable(true);

    QHBoxLayout *pLayout = new QHBoxLayout(this);
    pLayout->addStretch();
    pLayout->addWidget(m_playButton);
    pLayout->addStretch();
    pLayout->setContentsMargins(0, 10, 0, 10);
    setLayout(pLayout);

    connect(m_playButton, SIGNAL(clicked(bool)), this, SLOT(onPlayClicked(bool)));
}

void ControlBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void ControlBar::onPlayClicked(bool checked)
{
    if(checked == true)
    {
        emit playEvent();
        m_playButton->setStyleSheet("QPushButton{image:url(:/icon/pause.png);}");
    }
    else
    {
        emit pauseEvent();
        m_playButton->setStyleSheet("QPushButton{image:url(:/icon/play.png);}");
    }
}

void ControlBar::updatePlayStatue(bool start)
{
    if(start == true)
    {
        m_playButton->setChecked(true);
        m_playButton->setStyleSheet("QPushButton{image:url(:/icon/pause.png);}");
    }
    else
    {
        m_playButton->setChecked(false);
        m_playButton->setStyleSheet("QPushButton{image:url(:/icon/play.png);}");
    }
}
