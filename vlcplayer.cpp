#include "vlcplayer.h"
#include <QDebug>
#include <string>
#include "mainwindow.h"

VlcPlayer::VlcPlayer(QObject *parent) : QObject(parent)
{
}

VlcPlayer::~VlcPlayer()
{
    m_instance = nullptr;
    m_media = nullptr;
    m_mediaPlayer = nullptr;
}

void VlcPlayer::startPlayVideo(QString path)
{
    MainWindow *pMainWindow = MainWindow::GetInstance();
    m_instance = libvlc_new(0, nullptr);
    m_media = libvlc_media_new_path(m_instance, path.toStdString().c_str());
    m_mediaPlayer = libvlc_media_player_new_from_media(m_media);
    libvlc_media_release(m_media);
    libvlc_media_player_set_hwnd(m_mediaPlayer, pMainWindow->getViewWindowId());

    libvlc_media_player_play(m_mediaPlayer);
}

void VlcPlayer::playVideo()
{
    if(m_mediaPlayer != nullptr)
    {
        libvlc_media_player_play(m_mediaPlayer);
    }
}

void VlcPlayer::pauseVideo()
{
    if(m_mediaPlayer != nullptr)
    {
        libvlc_media_player_pause(m_mediaPlayer);
    }
}
