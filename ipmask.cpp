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
	return atoi(in_mask, mask);
	}

bool Ipmask::setMask(qint32 in_mask)
	{
	mask = in_mask;
	return true;
	}

bool Ipmask::setCidr(qint8 in_cidr)    /*=-=-=-=-=-=-=-= TODO =-=-=-=-=-=-=-=*/
	{
	return true;
	}

QString Ipmask::getIpStr()
	{
	return itoa(ip);
	}

bool Ipmask::atoi(QString addr, qint32 &result)
	{
	QString buf[4];
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
	qint8 oct;
	for(int i=3; i>=0; i--)
		{
		oct = (addr>>(i*8)) & 0xFF;
		result += QString::number(oct, 10);
		if(i) result += '.'; // если не является последним октетом, т.е. нулевым индексом, то ставим точку-разделитель
		}
	return result;
	}
