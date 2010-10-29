#ifndef ADAPTER_H
#define ADAPTER_H

#include <QObject>
#include <QtDBus/QtDBus>

class Adapter : public QObject
{
	Q_OBJECT

public:
	Adapter(QString path);
	Adapter(Adapter &adapter);
	~Adapter();
	QList<QVariant> listDevices();

private:
	QString *path;
	QDBusConnection con;

};

#endif // ADAPTER_H
