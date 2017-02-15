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

#include "paint_mask.h"

#include <QMessageBox>
#include <QMouseEvent>

Paint_mask::Paint_mask(QWidget * parent) : QWidget(parent)
	{
	wid = parent;
	}

void Paint_mask::paintEvent(QPaintEvent *)
	{
	QPainter painter(this);

	QRect r;
	r.setWidth(wid->width());
	r.setHeight(wid->height());
	setGeometry(r);


	QColor c;
	c.setRed(255);

	int w = wid->width();
	int h = wid->height();
	//p.fillRect(0,0,w,h,c);

	painter.fillRect(0,0,w,h,c);
	//p.setPen(QPen(Qt::red,1,Qt::SolidLine)); // Настройки рисования
	//p.drawLine(0,0,wid->width(),wid->height()); // Рисование линии
	}

void Paint_mask::mousePressEvent(QMouseEvent *event)
	{
	if(event->button() == Qt::LeftButton)
		{
		int x = event->x();
		int y = event->y();
		}
	}
