#ifndef MANAGER_H
#define MANAGER_H

#include <QObject>
#include <QtDBus/QtDBus>

class Manager : public QObject
{
	Q_OBJECT

public:
	Manager();
	QList<QString> getAdapters();

signals:
	void adapterRemoved(QString path);
	void adapterAdded(QString path);

private slots:
	void slotAdapterRemoved(QDBusObjectPath path);
	void slotAdapterAdded(QDBusObjectPath path);

private:
	QDBusConnection con;

};

#endif // MANAGER_H
