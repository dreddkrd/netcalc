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

bool Ipmask::get_info(SInfo *info)
	{
	quint32 ipa = (quint32)ip;
	if(ipa == 0) {info->small = "0.0.0.0/32"; info->large = "В сокетах с состоянием «listening» обозначает любые IP отправителя или любые сети получателя на текущем хосте."; return true;}
	if(ipa > 0 && ipa <= 16777215) {info->small = "0.0.0.0/8"; info->large = "Адреса источников пакетов «этой» («своей») сети."; return true;}
	if(ipa >= 167772160 && ipa <= 184549375) {info->small = "10.0.0.0/8"; info->large = "Для использования в частных сетях."; return true;}
	if(ipa >= 1681915904 && ipa <= 1686110207) {info->small = "100.64.0.0/10"; info->large = "Shared Address Space. RFC 6598. Для использования в сетях сервис-провайдера."; return true;}
	if(ipa >= 2130706432 && ipa <= 2147483647) {info->small = "127.0.0.0/8"; info->large = "Подсеть для коммуникаций внутри хоста (localhost). Используется сетевая подсистема, но в действительности такие пакеты не проходят через сетевую карту."; return true;}
	if(ipa >= 2851995648 && ipa <= 2852061183) {info->small = "169.254.0.0/16"; info->large = "Канальные адреса (Link local). Подсеть используется для автоматического назначения IP операционной системой в случае, если настроено получение адреса по DHCP, но ни один сервер не отвечает."; return true;}
	if(ipa >= 2886729728 && ipa <= 2887778303) {info->small = "172.16.0.0/12"; info->large = "Для использования в частных сетях."; return true;}
	if(ipa >= 3221225472 && ipa <= 3221225727) {info->small = "192.0.0.0/24"; info->large = "IETF Protocol Assignments"; return true;}
	if(ipa >= 3221225984 && ipa <= 3221226239) {info->small = "192.0.2.0/24"; info->large = "Для примеров в документации."; return true;}
	if(ipa == 3227017985) {info->small = "192.88.99.1/32"; info->large = "Применяется в качестве ретранслятора при инкапсуляции IPv6 в IPv4 (6to4). Его анонсируют многие компании. Пакет на этот адрес пойдёт до ближайшего хоста с этим IP, который распакует пакет и отправит его дальше по IPv6 маршрутизации."; return true;}
	if(ipa >= 3227017984 && ipa <= 3227018239) {info->small = "192.88.99.0/24"; info->large = "Используются для рассылки ближайшему узлу (Anycast)."; return true;}
	if(ipa >= 3232235520 && ipa <= 3232301055) {info->small = "192.168.0.0/16"; info->large = "Для использования в частных сетях."; return true;}
	if(ipa >= 3325256704 && ipa <= 3325256959) {info->small = "198.51.100.0/24"; info->large = "Для примеров в документации."; return true;}
	if(ipa >= 3323068416 && ipa <= 3323199487) {info->small = "198.18.0.0/15"; info->large = "Для стендов тестирования производительности."; return true;}
	if(ipa >= 3405803776 && ipa <= 3405804031) {info->small = "203.0.113.0/24"; info->large = "Для примеров в документации."; return true;}
	if(ipa == 3758096385) {info->small = "224.0.0.1"; info->large = "The All Hosts multicast group that contains all systems on the same network segment"; return true;}
	if(ipa == 3758096386) {info->small = "224.0.0.1"; info->large = "The All Routers multicast group that contains all routers on the same network segment"; return true;}
	if(ipa == 3758096389) {info->small = "224.0.0.5"; info->large = "AllSPFRouters address. Используется для отправки Hello-сообщений всем OSPF-маршрутизаторам."; return true;}
	if(ipa == 3758096390) {info->small = "224.0.0.6"; info->large = "AllDRouters address. Используется для отправки OSPF-сообщений выделенным маршрутизаторам OSPF."; return true;}
	if(ipa == 3758096393) {info->small = "224.0.0.9"; info->large = "RIP версии 2"; return true;}
	if(ipa == 3758096394) {info->small = "224.0.0.10"; info->large = "EIGRP-маршрутизаторы"; return true;}
	if(ipa == 3758096402) {info->small = "224.0.0.18"; info->large = "VRRP"; return true;}
	if(ipa == 3758096406) {info->small = "224.0.0.22"; info->large = "IGMP версии 3"; return true;}
	if(ipa == 3758096486) {info->small = "224.0.0.102"; info->large = "HSRP версии 2"; return true;}
	if(ipa == 3758096635) {info->small = "224.0.0.251"; info->large = "Multicast DNS address"; return true;}
	if(ipa >= 3758096640 && ipa <= 4009754623) {info->small = "224.0.1.0 - 238.255.255.255"; info->large = "Globally Scoped Addresses"; return true;}
	if(ipa == 4026531834) {info->small = "239.255.255.250"; info->large = "SSDP"; return true;}
	if(ipa >= 4009754624 && ipa <= 4026531839) {info->small = "239.0.0.0/8"; info->large = "Для частных мультикаст-доменов/организаций (пользовательские адреса). Могут динамически использоваться протоколами."; return true;}
	if(ipa >= 3758096384 && ipa <= 4026531839) {info->small = "224.0.0.0/4"; info->large = "Используются для многоадресной рассылки (Multicast)."; return true;}
	if(ipa >= 4026531840 && ipa < 4294967295) {info->small = "240.0.0.0/4"; info->large = "Зарезервировано для использования в будущем. Существует мнение, что эта подсеть больше никогда не будет использована, так как есть множество оборудования, не способного посылать пакеты в эту сеть."; return true;}
	if(ipa == 4294967295) {info->small = "255.255.255.255"; info->large = "Ограниченный широковещательный адрес. Чаще всего используется как адрес назначения при поиске DHCP серверов."; return true;}
	return false;
	}

QChar Ipmask::get_class()
	{
	if((ip & 0xF0000000) == 0xF0000000) return 'E';
	if((ip & 0xF0000000) == 0xE0000000) return 'D';
	qint8 cidr = getCidr8();
	if((ip & 0xE0000000) == 0xC0000000 && cidr == 24) return 'C';
	if((ip & 0xC0000000) == 0x80000000 && cidr == 16) return 'B';
	if((ip & 0x80000000) == 0x00000000 && cidr == 8) return 'A';
	return ' ';
	}

