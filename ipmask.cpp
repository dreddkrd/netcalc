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

#include "ipmask.h"

Ipmask::Ipmask()
	{
	ip = 0;
	mask = 0;
	}

bool Ipmask::setIp(QString in_ip)
	{
	return atoi(in_ip, ip);
	}

bool Ipmask::setIp(qint32 in_ip)
	{
	ip = in_ip;
	return true;
	}

bool Ipmask::setMask(QString in_mask)
	{
	qint32 new_mask;
	bool ok = atoi(in_mask, new_mask);
	if(ok && isContinuos(new_mask))
		{
		mask = new_mask;
		return true;
		}
	return false;
	}

bool Ipmask::setMask(qint32 in_mask)
	{
	if(isContinuos(in_mask))
		{
		mask = in_mask;
		return true;
		}
	else return false;
	}

bool Ipmask::setCidr(QString cidr)
	{
	bool ok;
	qint8 c = cidr.toInt(&ok, 10);
	if(ok)
		return setCidr(c);
	else
		return false;
	}

bool Ipmask::setCidr(qint8 cidr)
	{
	if(cidr >= 0 && cidr <= 32)
		{
		qint32 res = 0;
		for(int i=31;i>=(32-cidr);i--)
			{
			res |= 1<<i;
			}
		mask = res;
		}
	else return false;
	return true;
	}

QString Ipmask::getIpStr()
	{
	return itoa(ip);
	}

qint32 Ipmask::getIp32()
	{
	return ip;
	}

QString Ipmask::getMaskStr()
	{
	return itoa(mask);
	}

qint32 Ipmask::getMask32()
	{
	return mask;
	}

QString Ipmask::getCidrStr()
	{
	qint8 cidr = getCidr8();
	return QString::number(cidr, 10);
	}

qint8 Ipmask::getCidr8()
	{
	int i=31;
	qint8 cidr = 0;
	while(i>=0 && (mask>>i--)&1)
		cidr++;
	return cidr;
	}

bool Ipmask::atoi(QString addr, qint32 &result)
	{
	QString buf[4] = {0,0,0,0};
	int buf_index = 0;
	for(int i=0; i<addr.length(); i++)
		{
		if(addr[i].isDigit())
			{
			if(buf[buf_index].length()>3) // если уже больше 3 цифр без точки (невозможно)
				return false;
			buf[buf_index] += addr[i];
			}
		else if(addr[i] == '.') // находим точку
			{
			if(buf_index < 3) // если уже все 3 октета заполнены
				buf_index++;
			else
				break;
			}
		}
	//qint8 [4] = {0, 0, 0, 0};
	for(int i=0; i<=3; i++) if(!buf[i].length()) buf[i] = "0";
	qint32 ip_out = 0;
	for(int i=0; i<=3; i++) // идём по октетам, если дожили досюда
		{
		bool ok;
		int tmp = buf[i].toInt(&ok, 10);
		if(ok && tmp <= 0xFF)
			ip_out += tmp << ((3-i)*8);
		else
			return false;
		}
	result = ip_out;
	return true;
	}

QString Ipmask::itoa(qint32 addr)
	{
	QString result;
	quint8 oct;
	for(int i=3; i>=0; i--)
		{
		oct = (addr>>(i*8)) & 0xFF;
		result += QString::number(oct, 10);
		if(i) result += '.'; // если не является последним октетом, т.е. нулевым индексом, то ставим точку-разделитель
		}
	return result;
	}

bool Ipmask::isContinuos(qint32 in_mask)
	{
	bool last = (in_mask>>31)&1;
	bool curr;
	int i=31;
	while(i >= 0)
		{
		curr = (in_mask>>i)&1;
		if(curr && !last) // 0 -> 1
			return false;
		last = curr;
		i--;
		}
	return true;
	}

