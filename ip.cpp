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
#include "paint_mask.h"
#include <QtGui/QCloseEvent>
#include <QDesktopWidget>

Paint_mask *bits;

ip_window::ip_window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ip_mod)
{
    ui->setupUi(this);
    bits = new Paint_mask(ui->ip_bar);
    bits->setParent(ui->ip_bar);
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
