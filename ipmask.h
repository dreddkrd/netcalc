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

#ifndef IPMASK_H
#define IPMASK_H

#include <QString>

class Ipmask
{
public:
	Ipmask();
	// set
	bool setIp(QString in_ip);
	bool setIp(qint32 in_ip);
	bool setMask(QString in_mask);
	bool setMask(qint32 in_mask);
	bool setCidr(QString cidr);
	bool setCidr(qint8 cidr);

	//get
	QString getIpStr();
	qint32 getIp32();
	QString getMaskStr();
	qint32 getMask32();
	QString getCidrStr();
	qint8 getCidr8();

	bool atoi(QString addr, qint32 &result);
	QString itoa(qint32 addr);

private:
	qint32 ip;
	qint32 mask;

	bool isContinuos(qint32 in_mask);
};

#endif // IPMASK_H
