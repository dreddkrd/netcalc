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
//	ipmask->setIp("192.168.0.1");
//	ipmask->setMask("255.255.255.252");

	ipbar = new Paint_mask(ui->ip_bar);
	ipbar->setParent(ui->ip_bar);
	ipbar->mask = ipmask->getIp32();
	connect(ipbar, SIGNAL(bitSelected(qint8)), this, SLOT(ipBitChange(qint8)));

	maskbar = new Paint_mask(ui->mask_bar);
	maskbar->setParent(ui->mask_bar);
	maskbar->mask = ipmask->getMask32();
	connect(maskbar, SIGNAL(bitSelected(qint8)), this, SLOT(maskBitChange(qint8)));

	ui->description->setHidden(true);
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

	qint8 cidr = ipmask->getCidr8();
	QString cidr_str;
	if(cidr) cidr_str = "/" + ipmask->getCidrStr();

	ui->cidr_label->setText(cidr_str);

	if(cidr<32)
		{
		ui->edit_bcast->setText(ipmask->itoa(bcast));
		}
	else
		{
		ui->edit_bcast->setText("n/a");
		}

	if(cidr<31)
		{
		ui->edit_host_min->setText(ipmask->itoa(network+1));
		ui->edit_host_max->setText(ipmask->itoa(bcast-1));
		ui->edit_hosts->setText(QString::number((quint32)(~(ipmask->getMask32())-1),10));
		}
	else
		{
		ui->edit_host_min->setText("n/a");
		ui->edit_host_max->setText("n/a");
		ui->edit_hosts->setText("n/a");
		}

	SInfo info;
	if(ipmask->get_info(&info))
		{
		ui->description->setHidden(false);
		ui->text_small->setText(info.small);
		ui->text_large->setText(info.large);
		}
	else
		ui->description->setHidden(true);

	ui->class_label->setText(ipmask->get_class());

	ipbar->mask = ipmask->getIp32();
	ipbar->repaint();
	maskbar->mask = ipmask->getMask32();
	maskbar->repaint();
	}

void ip_window::ipBitChange(qint8 bit)
	{
	qint32 ip = ipmask->getIp32();
	if((ip>>bit)&1) // был 1, ставим 0
		{
		ip &= ~(1<<bit);
		}
	else // был 0, ставим 1
		{
		ip |= (1<<bit);
		}
	if(ipmask->setIp(ip)) update();
	}

void ip_window::maskBitChange(qint8 bit)
	{
	if(ipmask->getCidr8() == 1 && bit == 31)
		{
		ipmask->setCidr(0);
		update();
		}
	else if(ipmask->setCidr(32-bit)) update();
	}
