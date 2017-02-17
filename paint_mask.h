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

#ifndef PAINT_MASK_H
#define PAINT_MASK_H

#include <QObject>
#include <QWidget>
#include <QPainter>

#define BLOCKS 35
#define BLOCKS_HEIGHT_ASPECT 1.5

class Paint_mask : public QWidget
{
	Q_OBJECT
public:
	qint32 mask;
	Paint_mask(QWidget * parent = 0);

private:
	QWidget *wid;
	int block_width;
	int block_height;

protected:
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *event);

signals:
	void bitSelected(qint8 bit);
};

#endif // PAINT_MASK_H
