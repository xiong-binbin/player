#include "mainwindow.h"
#include <QVBoxLayout>
#include <QFile>
#include <QDebug>

#ifdef Q_OS_WIN
#include <qt_windows.h>
#include <Windowsx.h>
#endif

MainWindow* MainWindow::m_mainWindow = nullptr;

MainWindow::MainWindow()
{
    resize(1024, 680);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowIcon(QIcon(":/icon/logo.ico"));

    QFile qss(":/qss/style.qss");
    qss.open(QFile::ReadOnly);
    this->setStyleSheet(qss.readAll());
    qss.close();

    m_titleBar = new TitleBar(this);
    m_titleBar->setObjectName("titleBar");
    installEventFilter(m_titleBar);

    m_viewWindow = new ViewWindow(this);
    m_viewWindow->setObjectName("viewWindow");

    m_controlBar = new ControlBar(this);
    m_controlBar->setObjectName("controlBar");

    QVBoxLayout *pLayout = new QVBoxLayout(this);
    pLayout->addWidget(m_titleBar);
    pLayout->addWidget(m_viewWindow);
    pLayout->addWidget(m_controlBar);
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(pLayout);

    m_vlcPlayer = new VlcPlayer(this);

    connect(m_titleBar, SIGNAL(startPlayVideo(QString)), m_vlcPlayer, SLOT(startPlayVideo(QString)));
    connect(m_titleBar, SIGNAL(updatePlayStatus(bool)), m_controlBar, SLOT(updatePlayStatue(bool)));
    connect(m_controlBar, SIGNAL(playEvent()), m_vlcPlayer, SLOT(playVideo()));
    connect(m_controlBar, SIGNAL(pauseEvent()), m_vlcPlayer, SLOT(pauseVideo()));
}

MainWindow::~MainWindow()
{
    qDebug() << "~MainWindow";
    this->deleteLater();
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    Q_UNUSED(eventType)

    int nBorder = 5;
    MSG *msg = static_cast<MSG *>(message);

    switch (msg->message)
    {
        case WM_NCHITTEST:
        {
            int nX = GET_X_LPARAM(msg->lParam) - this->geometry().x();
            int nY = GET_Y_LPARAM(msg->lParam) - this->geometry().y();

            *result = HTCAPTION;

            // if mouse in the border of mainframe,we zoom mainframe
            if ((nX > 0) && (nX < nBorder))
                *result = HTLEFT;

            if ((nX > this->width() - nBorder) && (nX < this->width()))
                *result = HTRIGHT;

            if ((nY > 0) && (nY < nBorder))
                *result = HTTOP;

            if ((nY > this->height() - nBorder) && (nY < this->height()))
                *result = HTBOTTOM;

            if ((nX > 0) && (nX < nBorder) && (nY > 0)
                && (nY < nBorder))
                *result = HTTOPLEFT;

            if ((nX > this->width() - nBorder) && (nX < this->width())
                && (nY > 0) && (nY < nBorder))
                *result = HTTOPRIGHT;

            if ((nX > 0) && (nX < nBorder)
                && (nY > this->height() - nBorder) && (nY < this->height()))
                *result = HTBOTTOMLEFT;

            if ((nX > this->width() - nBorder) && (nX < this->width())
                && (nY > this->height() - nBorder) && (nY < this->height()))
                *result = HTBOTTOMRIGHT;

            if (*result == HTCAPTION)
            {
                return false;
            }
            else
            {
                return true;
            }

        }

        default:
            break;
    }

    return QWidget::nativeEvent(eventType, message, result);
}

void* MainWindow::getViewWindowId()
{
    return (void *)m_viewWindow->winId();
}
