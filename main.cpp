#include "main.h"
#include "mainwindow.h"
#include "mac.h"
#include <QApplication>
#include <QTextCodec>

QSystemTrayIcon *tray_icon;
QMenu *tray_menu;

QAction *mac_action;
QAction *ip_action;
QAction *quit_action;
menu_events *mev;

ip_window *I_W;
mac_window *M_W;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mev = new menu_events();

    I_W = new ip_window();
    M_W = new mac_window();

    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));

// Контекстное меню иконки в трее

    // Setting actions...
    mac_action = new QAction("MAC-адреса", nullptr);
    ip_action = new QAction("IP-адреса", nullptr);
    quit_action = new QAction("Выход", nullptr);

    // Connecting actions to slots...
    QObject::connect(mac_action, SIGNAL(triggered()), mev, SLOT(Mac_action()));
    QObject::connect(ip_action, SIGNAL(triggered()), mev, SLOT(Ip_action()));
    QObject::connect(quit_action, SIGNAL(triggered()), qApp, SLOT(quit()));

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

    //connect(tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));

//    tray_icon->setVisible(true);
    tray_icon->show();

//    w->show();
//    m->show();

    return a.exec();
}

void menu_events::Mac_action()
{
    M_W->show();
    M_W->move_to_corner();
}

void menu_events::Ip_action()
{
    I_W->show();
    I_W->move_to_corner();
}

menu_events::menu_events()
{
    return;
}
