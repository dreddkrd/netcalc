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

#include "mac.h"
#include "ui_mac.h"
#include <QtGui/QCloseEvent>
#include <QDesktopWidget>

mac_window::mac_window(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::mac_mod)
	{
	ui->setupUi(this);
	connect(ui->lineEdit, SIGNAL(textChanged(QString)), this, SLOT(mac_change(QString)));
	lines[0][0] = ui->lineEdit_2;
	lines[0][1] = ui->lineEdit_3;
	lines[1][0] = ui->lineEdit_4;
	lines[1][1] = ui->lineEdit_5;
	lines[2][0] = ui->lineEdit_6;
	lines[2][1] = ui->lineEdit_7;

	int i,j;
	for(i=0;i<=2;i++)
		for(j=0;j<=1;j++)
			lines[i][j]->installEventFilter(this);
	main_line_selected = false;
	}

mac_window::~mac_window()
	{
	delete ui;
	}

void mac_window::closeEvent(QCloseEvent *e)
	{
	this->hide();
	e->ignore();
	}

void mac_window::move_to_corner() {
	QDesktopWidget desktop;
	QRect rect = desktop.availableGeometry(desktop.primaryScreen()); // прямоугольник с размерами экрана
	QRect window = this->frameGeometry();
	QPoint pos = rect.bottomRight(); //координаты центра экрана
	pos.setX(pos.x() - (window.width()));  // учитываем половину ширины окна
	pos.setY(pos.y() - (window.height()));  // .. половину высоты
	move(pos);
	}

void mac_window::mac_change(QString str)
	{
#define L 0
#define U 1

	int i, j;
	QString mac[2];
	QString res[3][2];
	for(i=0; i<str.length(); i++)
		{
		if(str[i] >= '0' && str[i] <= '9') {mac[L].append(str[i]); mac[U].append(str[i]);}
		if(str[i] >= 'a' && str[i] <= 'f') {mac[L].append(str[i]); mac[U].append(str[i].toUpper());}
		if(str[i] >= 'A' && str[i] <= 'F') {mac[L].append(str[i].toLower()); mac[U].append(str[i]);}
		}
	if(mac[L].length() == 12) // MAC полон
		{
		for(i=0;i<=11;i++)
			{
			if(i && !(i%2))
				{
				res[0][L].append(":"); res[0][U].append(":");
				res[1][L].append("-"); res[1][U].append("-");
				}
			if(i && !(i%4))
				{
				res[2][L].append("."); res[2][U].append(".");
				}
			for(j=0;j<=2;j++)
				{
				res[j][L].append(mac[L][i]);
				res[j][U].append(mac[U][i]);
				}
			}
		for(i=0;i<=2;i++)
			for(j=0;j<=1;j++)
				{
				lines[i][j]->setText(res[i][j]);
				}
		}
	else // clear
		{
		for(i=0;i<=2;i++)
			{
			lines[i][L]->setText("");
			lines[i][U]->setText("");
			}
		}
	}

bool mac_window::eventFilter(QObject *obj, QEvent *event)
	{
	if(event->type() == QEvent::MouseButtonPress)
		{
		//        if(obj == this->ui->lineEdit) if(!main_line_selected) {this->ui->lineEdit->selectAll(); main_line_selected = true;}  // TODO
		int i,j;
		for(i=0;i<=2;i++)
			for(j=0;j<=1;j++)
				{
				if(obj == lines[i][j] && lines[i][j]->text().length())
					{
					lines[i][j]->selectAll();
					emit lines[i][j]->copy();
					lines[i][j]->deselect();
					hide();
					break;
					}
				}
		}
	return QWidget::eventFilter(obj, event);
	}
