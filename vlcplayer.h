#ifndef VLCPLAYER_H
#define VLCPLAYER_H

#include <QObject>
#include <QWidget>
#include "vlc/libvlc.h"
#include "vlc/vlc.h"

class VlcPlayer : public QObject
{
    Q_OBJECT
public:
    VlcPlayer(QObject *parent);
    ~VlcPlayer();

public slots:
    void startPlayVideo(QString path);
    void playVideo();
    void pauseVideo();

private:
    libvlc_instance_t *m_instance;
    libvlc_media_t *m_media;
    libvlc_media_player_t *m_mediaPlayer;
};

#endif // VLCPLAYER_H
