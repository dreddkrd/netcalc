#ifndef IPMASK_H
#define IPMASK_H

#include <QString>

class Ipmask
{
public:
	Ipmask();
	bool setIp(QString in_ip);
	bool setIp(qint32 in_ip);
	bool setMask(QString in_mask);
	bool setMask(qint32 in_mask);
	bool setCidr(qint8 in_cidr);
	QString getIpStr();

private:
	qint32 ip;
	qint32 mask;
	bool atoi(QString addr, qint32 &result);
	QString itoa(qint32 addr);
};

#endif // IPMASK_H
