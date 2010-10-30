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

private:
	void setSignals();

	QString *path;
	QDBusConnection con;

};

#endif // DEVICE_H
