#ifndef MAIN_H
#define MAIN_H

#include <QSystemTrayIcon>
#include <QMenu>
//#include <QObject>

class menu_events : public QObject
{
    Q_OBJECT
public:
    menu_events();
public slots:
    void Mac_action();
    void Ip_action();
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
};

#endif // MAIN_H
