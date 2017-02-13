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

#ifndef IP_H
#define IP_H

#include <QMainWindow>

class QCloseEvent;

namespace Ui {
class ip_mod;
}

class QSystemTrayIcon;

class ip_window : public QMainWindow
{
    Q_OBJECT

public:
    explicit ip_window(QWidget *parent = 0);
    ~ip_window();
    void move_to_corner();

private:
    Ui::ip_mod *ui;

protected:
    void closeEvent(QCloseEvent *e);
};

#endif // IP_H
