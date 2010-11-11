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
	QVariantMap getProperties();
	QStringList listDevices();
	void setProperty(QString key, QVariant value);

	QString getPath();

signals:
	void deviceAdded(QString adapPath, QString devPath);
	void deviceRemoved(QString adapPath, QString devPath);
	void propertyChanged(QString adapPath, QString key, QVariant value);

private slots:
	void slotDeviceRemoved(QDBusObjectPath path);
	void slotDeviceAdded(QDBusObjectPath path);
	void slotPropertyChanged(QString name, QDBusVariant value);

private:
	void setSignals();

	QDBusInterface adapter;
};

#endif // ADAPTER_H
