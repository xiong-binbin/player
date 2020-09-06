#include "titlebar.h"
#include <QDebug>
#include <QHBoxLayout>
#include <QStyleOption>
#include <QPainter>
#include <QIcon>
#include <QEvent>
#include <QMenu>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>

#ifdef Q_OS_WIN
#include <qt_windows.h>
#endif

TitleBar::TitleBar(QWidget *parent) : QWidget(parent)
{
    setFixedHeight(30);

    m_menuButton = new QPushButton(this);
    m_minButton = new QPushButton(this);
    m_maxButton = new QPushButton(this);
    m_closeButton = new QPushButton(this);

    m_menuButton->setToolTip("菜单");
    m_minButton->setToolTip("最小化");
    m_maxButton->setToolTip("最大化");
    m_closeButton->setToolTip("关闭");

    m_menuButton->setObjectName("menuButton");
    m_minButton->setObjectName("minButton");
    m_maxButton->setObjectName("maxButton");
    m_closeButton->setObjectName("closeButton");

    m_menuButton->setFixedSize(80, 30);
    m_minButton->setFixedSize(45, 30);
    m_maxButton->setFixedSize(45, 30);
    m_closeButton->setFixedSize(45, 30);

    QMenu *pMenu = new QMenu(this);
    QAction *pAction1 = new QAction("打开文件", this);
    QAction *pAction2 = new QAction("打开URL", this);
    pMenu->addAction(pAction1);
    pMenu->addAction(pAction2);

    m_menuButton->setMenu(pMenu);
    m_menuButton->setText("影音");

    QHBoxLayout *pLayout = new QHBoxLayout(this);
    pLayout->addWidget(m_menuButton);
    pLayout->addStretch();
    pLayout->addWidget(m_minButton);
    pLayout->addWidget(m_maxButton);
    pLayout->addWidget(m_closeButton);
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(pLayout);

    connect(pAction1, SIGNAL(triggered()), this, SLOT(onOpenFile()));
    connect(pAction2, SIGNAL(triggered()), this, SLOT(onOpenUrl()));

    connect(m_minButton, SIGNAL(clicked()), this, SLOT(onClicked()));
    connect(m_maxButton, SIGNAL(clicked()), this, SLOT(onClicked()));
    connect(m_closeButton, SIGNAL(clicked()), this, SLOT(onClicked()));
}

//处理qss失效问题
void TitleBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void TitleBar::mousePressEvent(QMouseEvent *event)
{
#ifdef Q_OS_WIN
    Q_UNUSED(event)

    if (ReleaseCapture())
    {
        QWidget *pWindow = this->window();
        if (pWindow->isTopLevel())
        {
           SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
        }
    }
#else
#endif
}

bool TitleBar::eventFilter(QObject *object, QEvent *event)
{
    switch (event->type())
    {
        case QEvent::WindowStateChange:
        case QEvent::Resize:
        {
            updateMaxButton();
            return true;
        }

        default:
            return QWidget::eventFilter(object, event);
    }
}

void TitleBar::onClicked()
{
    QPushButton *pButton = qobject_cast<QPushButton *>(sender());
    QWidget *pWindows = this->window();

    if(pWindows->isTopLevel())
    {
        if(pButton == m_minButton)
        {
            pWindows->showMinimized();
        }
        else if(pButton == m_maxButton)
        {
            pWindows->isMaximized() ? pWindows->showNormal() : pWindows->showMaximized();
        }
        else if (pButton == m_closeButton)
        {
            pWindows->close();
        }
    }
}

void TitleBar::updateMaxButton()
{
    QWidget *pWindow = this->window();
    if(pWindow->isTopLevel())
    {
        if(pWindow->isMaximized())
        {
            m_maxButton->setStyleSheet("QPushButton{image:url(:/icon/normal.png);}");
            m_maxButton->setToolTip("还原");
        }
        else
        {
            m_maxButton->setStyleSheet("QPushButton{image:url(:/icon/max.png);}");
            m_maxButton->setToolTip("最大化");
        }
    }
}

void TitleBar::onOpenFile()
{
    QString path = QFileDialog::getOpenFileName(this, tr("打开文件"), "D:/", tr("*.mp4"));

    if(path.length() > 0)
    {
        path = QDir::toNativeSeparators(path);  //斜杠转反斜杠
        emit startPlayVideo(path);
        emit updatePlayStatus(true);
    }
}

void TitleBar::onOpenUrl()
{
    QMessageBox::information(nullptr, tr("提示"), tr("暂未支持"));
}
