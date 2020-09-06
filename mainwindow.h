#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include "vlcplayer.h"
#include "titlebar.h"
#include "controlbar.h"
#include "viewwindow.h"

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    MainWindow();
    static MainWindow *m_mainWindow;

public:
    static MainWindow* GetInstance()
    {
        if(m_mainWindow == nullptr)
        {
            m_mainWindow = new MainWindow();
        }
        return m_mainWindow;
    }
    ~MainWindow() override;
    void* getViewWindowId();

protected:
    bool nativeEvent(const QByteArray &eventType, void *message, long *result) override;

private:
    TitleBar *m_titleBar;
    ViewWindow *m_viewWindow;
    ControlBar *m_controlBar;
    VlcPlayer *m_vlcPlayer;
};
#endif // MAINWINDOW_H
