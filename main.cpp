#include "main.h"
#include "mainwindow.h"
#include "mac.h"
#include <QApplication>

QSystemTrayIcon *tray_icon;
QMenu *tray_menu;

QAction *mac_action;
QAction *ip_action;
QAction *quit_action;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    mac m;

// Контекстное меню иконки в трее

    // Setting actions...
    mac_action = new QAction("MAC-адреса", nullptr);
    ip_action = new QAction("IP-адреса", nullptr);
    quit_action = new QAction("Выход", nullptr);

    // Connecting actions to slots...
    connect(mac_action, SIGNAL(triggered()), this, SLOT(hide()));
    connect(ip_action, SIGNAL(triggered()), this, SLOT(showNormal()));
    connect(quit_action, SIGNAL(triggered()), qApp, SLOT(quit()));

    // Setting system tray's icon menu...
    tray_menu = new QMenu(nullptr);
    tray_menu->addAction(mac_action);
    tray_menu->addAction(ip_action);
    tray_menu->addSeparator();
    tray_menu->addAction(quit_action);


// Иконка в трее
    tray_icon = new QSystemTrayIcon(nullptr);
    tray_icon->setIcon(QIcon(":/network.png"));
    tray_icon->setContextMenu(tray_menu);
    tray_icon->setToolTip("Net Calc");

    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));

//    tray_icon->setVisible(true);
    tray_icon->show();

    w.show();
    m.show();

    return a.exec();
}
