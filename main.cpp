/*
 * Copyright 2017 by Andrey Yanchenko <admin@dredd.ru>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "main.h"
#include "ip.h"
#include "mac.h"
#include <QApplication>

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

#ifndef Q_OS_WIN
	QTextCodec::setCodecForCStrings(QTextCodec::codecForName("utf-8"));
#endif

#ifdef Q_OS_WIN
	QSettings settings("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
	//settings.setValue(APPLICATION_NAME, QDir::toNativeSeparators(QCoreApplication::applicationFilePath()));
	settings.contains(APPLICATION_NAME);
	settings.sync();
#endif

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

	QObject::connect(tray_icon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), mev, SLOT(trayIconActivated(QSystemTrayIcon::ActivationReason)));

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
	M_W->main_line_selected = false;
	M_W->activateWindow();
	}

void menu_events::Ip_action()
	{
	I_W->show();
	I_W->move_to_corner();
	I_W->activateWindow();
	}

void menu_events::trayIconActivated(QSystemTrayIcon::ActivationReason reason)
	{
	switch (reason)
		{
	case QSystemTrayIcon::Trigger:
		//        case QSystemTrayIcon::DoubleClick:
		this->Mac_action();
		break;
	case QSystemTrayIcon::MiddleClick:
		this->Ip_action();
	default:
		break;
		}
	}

menu_events::menu_events()
	{
	return;
	}
