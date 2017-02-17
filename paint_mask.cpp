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
	mask = 0;
	}

void Paint_mask::paintEvent(QPaintEvent *)
	{
	QPainter p(this);
	//p.setRenderHint(QPainter::TextAntialiasing);

	QRect r;
	r.setWidth(wid->width());
	r.setHeight(wid->height());
	setGeometry(r);

	int block_width = wid->width()/35;
	int block_height = block_width*1.5;
	int bit = 31;
	for(int i=0;i<=34;i++)
		{
		if(i==8 || i==17 || i==26) continue;
		QColor cRed, cGreen, cWhite;
		cRed.setRed(255); cRed.setGreen(220); cRed.setBlue(220);
		cGreen.setRed(220); cGreen.setGreen(255); cGreen.setBlue(220);
		cWhite.setRed(255); cWhite.setGreen(255); cWhite.setBlue(255);

		p.setPen(QPen(Qt::black,1,Qt::SolidLine));
		p.fillRect(i*block_width, 0, block_width, block_height, ((mask>>bit)&1)?cGreen:cRed);
		p.drawRect(i*block_width, 0, block_width, block_height);


		p.setPen(QPen(Qt::black,1,Qt::SolidLine));

		if((mask>>bit)&1) // draw 1
			{
			QRect letter = QRect(i*block_width, 0, block_width, block_height);
			p.drawText(letter, Qt::AlignCenter, "1");
			}
		else // draw 0
			{
			QRect letter = QRect(i*block_width+1, 0, block_width, block_height);
			p.drawText(letter, Qt::AlignCenter, "0");
			}
		bit--;
		}

//	int w = wid->width();
//	int h = wid->height();
	//p.fillRect(0,0,w,h,c);

//	painter.fillRect(0,0,w,h,c);
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
