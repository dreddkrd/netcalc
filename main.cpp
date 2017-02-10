#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.mSystemTrayIcon = new QSystemTrayIcon(nullptr);
    w.mSystemTrayIcon->setIcon(QIcon(":/network.png"));
    w.mSystemTrayIcon->setVisible(true);

    QMenu *menu = new QMenu("&Меню");
    menu->addAction("&About Qt",
                   &a,
                   SLOT(aboutQt()),
                   Qt::CTRL + Qt::Key_Q
                  );
    menu->addSeparator();
    menu->addAction("Quit");
    w.mSystemTrayIcon->setContextMenu(menu);

    w.show();

    return a.exec();
}
