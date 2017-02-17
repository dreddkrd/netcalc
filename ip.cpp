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

#include "ip.h"
#include "ui_ip.h"
#include <QtGui/QCloseEvent>
#include <QDesktopWidget>

ip_window::ip_window(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::ip_mod)
	{
	ui->setupUi(this);
	connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(ip_change(QString)));

	ipmask = new Ipmask();
	ipmask->setIp("192.168.0.1");
	ipmask->setMask("255.255.255.252");

	ipbar = new Paint_mask(ui->ip_bar);
	ipbar->setParent(ui->ip_bar);
	ipbar->mask = ipmask->getIp32();

	maskbar = new Paint_mask(ui->mask_bar);
	maskbar->setParent(ui->mask_bar);
	maskbar->mask = ipmask->getMask32();
	//    ui->verticalLayout->addWidget(bits);
	}

ip_window::~ip_window()
	{
	delete ui;
	}

void ip_window::closeEvent(QCloseEvent *e)
	{
	this->hide();
	e->ignore();
	}

void ip_window::move_to_corner()
	{
	QDesktopWidget desktop;
	QRect rect = desktop.availableGeometry(-1/*desktop.primaryScreen()*/); // прямоугольник с размерами экрана
	QRect window = this->frameGeometry();
	QPoint pos = rect.bottomRight(); //координаты угла экрана
	pos.setX(pos.x() - (window.width()));  // учитываем половину ширины окна
	pos.setY(pos.y() - (window.height()));  // .. половину высоты
	move(pos);
	}

void ip_window::ip_change(QString str)
	{
	bool mode = 0;
	QString ip, mask;
	for(int i=0;i<str.length();i++)
		{
		if(ip.length() && (str[i] == ' ' || str[i] == '/')) {mode = 1; continue;}
		if(!mode)
			ip += str[i];
		else
			mask += str[i];
		}
	ipmask->setIp(ip);

	if(!ipmask->setCidr(mask)) ipmask->setMask(mask);

	update();
	}

void ip_window::update()
	{
	ui->edit_ip->setText(ipmask->getIpStr());
	ui->edit_mask->setText(ipmask->getMaskStr());
	qint32 network = ipmask->getIp32() & ipmask->getMask32();
	qint32 bcast = ipmask->getIp32() | ~ipmask->getMask32();
	ui->edit_network->setText(ipmask->itoa(network));
	ui->edit_bcast->setText(ipmask->itoa(bcast));

	qint8 cidr = ipmask->getCidr8();
	QString cidr_str;
	if(cidr) cidr_str = "/" + ipmask->getCidrStr();

	ui->cidr_label->setText(cidr_str);

	if(cidr<31)
		{
		ui->edit_host_min->setText(ipmask->itoa(network+1));
		ui->edit_host_max->setText(ipmask->itoa(bcast-1));
		}
	else
		{
		ui->edit_host_min->setText("n/a");
		ui->edit_host_max->setText("n/a");
		}

	if(cidr<31)
		{
		ui->edit_hosts->setText(QString::number((quint32)(~(ipmask->getMask32())-1),10));
		}
	else
		{
		ui->edit_hosts->setText("n/a");
		}

	ipbar->mask = ipmask->getIp32();
	ipbar->repaint();
	maskbar->mask = ipmask->getMask32();
	maskbar->repaint();
	}
