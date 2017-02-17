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
