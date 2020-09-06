#ifndef TITLEBAR_H
#define TITLEBAR_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QEvent>

class TitleBar : public QWidget
{
    Q_OBJECT
public:
    explicit TitleBar(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    bool eventFilter(QObject *object, QEvent *event) override;
    void updateMaxButton();

private slots:
    void onClicked();
    void onOpenFile();
    void onOpenUrl();

private:
    QPushButton *m_menuButton;
    QPushButton *m_minButton;
    QPushButton *m_maxButton;
    QPushButton *m_closeButton;

signals:
    void startPlayVideo(QString path);
    void updatePlayStatus(bool start);
};

#endif // TITLEBAR_H
