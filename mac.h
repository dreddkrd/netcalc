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

#ifndef MAC_H
#define MAC_H

#include <QMainWindow>
#include <QLineEdit>

namespace Ui {
class mac_mod;
}

class mac_window : public QMainWindow
{
	Q_OBJECT
	QLineEdit *lines[3][2];
public:
	explicit mac_window(QWidget *parent = 0);
	~mac_window();
	void move_to_corner();
	bool main_line_selected;

private:
	Ui::mac_mod *ui;
	bool eventFilter(QObject *obj, QEvent *event);

protected:
	void closeEvent(QCloseEvent *e);

public slots:
	void mac_change(QString str);
};

#endif // MAC_H
