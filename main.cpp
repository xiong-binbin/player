#include "mainwindow.h"
#include <QScopedPointer>
#include <QApplication>


MainWindow* MainWindow::m_mainWindow = nullptr;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QScopedPointer<MainWindow> pWin(MainWindow::GetInstance());
    pWin->show();
    return a.exec();
}
