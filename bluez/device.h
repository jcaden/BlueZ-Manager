#ifndef DEVICE_H
#define DEVICE_H

#include <QObject>

#include <QtDBus/QtDBus>

class Device : public QObject
{
	Q_OBJECT

public:
	Device(QString path);
	Device(Device &device);
	~Device();
	QVariantMap getProperties();
	QString getPath();

private:
	void setSignals();

	QDBusInterface device;

};

#endif // DEVICE_H
