#ifndef ADAPTER_H
#define ADAPTER_H

#include <QObject>
#include <QMap>

#include <QtDBus/QtDBus>

class Adapter : public QObject
{
	Q_OBJECT

public:
	Adapter(QString path);
	Adapter(Adapter &adapter);
	~Adapter();
	QMap<QString, QVariant> getProperties();
	QList<QVariant> listDevices();

private:
	void setSignals();

	QString *path;
	QDBusConnection con;

};

#endif // ADAPTER_H
