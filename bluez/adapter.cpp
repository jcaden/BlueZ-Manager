/**
 *
 *  Copyright (C) 2010 Jose Antonio Santos-Cadenas
 *  Author:
 *  Jose Antonio Santos-Cadenas <santoscadenas at gmail.com>
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#include <QtDBus/QtDBus>
#include <QDebug>

#include "adapter.h"

Adapter::Adapter(QString path) :
	QObject(),
	adapter("org.bluez", path,
		"org.bluez.Adapter", QDBusConnection::systemBus())
{
	setSignals();
}

Adapter::Adapter(Adapter &adapter) :
		QObject(),
		adapter("org.bluez", adapter.adapter.path(),
			"org.bluez.Adapter", QDBusConnection::systemBus())
{
	setSignals();
}

Adapter::~Adapter()
{
	qDebug() << "Destroying adapter" << adapter.path();
}

QMap<QString, QVariant> Adapter::getProperties()
{
	QDBusMessage reply = adapter.call("GetProperties");

	if (reply.type() == QDBusMessage::ErrorMessage) {
		qWarning() << "Error reply received: " << reply.errorMessage();
		return QVariantMap();
	}

	if (reply.arguments().count() != 1) {
		qWarning() << "Unspected reply received";
		return QVariantMap();
	}

	if (reply.signature() != "a{sv}") {
		qWarning() << "Unspected reply signature";
		return QVariantMap();
	}

	return qdbus_cast<QVariantMap>(reply.arguments()[0]);
}

void Adapter::setSignals()
{
	QDBusConnection::systemBus().connect("org.bluez",
			adapter.path(), "org.bluez.Adapter", "DeviceRemoved",
			this, SLOT(slotDeviceRemoved(QDBusObjectPath)));
	QDBusConnection::systemBus().connect("org.bluez", adapter.path(),
			"org.bluez.Adapter", "DeviceCreated",
			this, SLOT(slotDeviceAdded(QDBusObjectPath)));
	QDBusConnection::systemBus().connect("org.bluez", adapter.path(),
			"org.bluez.Adapter", "PropertyChanged",
			this, SLOT(slotPropertyChanged(QString, QDBusVariant)));
}

QStringList Adapter::listDevices()
{
	QDBusMessage reply = adapter.call("ListDevices");

	if (reply.type() == QDBusMessage::ErrorMessage) {
		qWarning() << "Error reply received: " << reply.errorMessage();
		return QStringList();
	}

	if (reply.arguments().count() != 1) {
		qWarning() << "Unspected reply received";
		return QStringList();
	}

	if (reply.signature() != "ao") {
		qWarning() << "Unspected reply signature";
		return QStringList();
	}

	return qdbus_cast<QStringList>(reply.arguments()[0]);
}

void Adapter::slotDeviceRemoved(QDBusObjectPath path)
{
	qDebug() << "Device removed on adapter" << adapter.path() << "with path"
			<< path.path();
	emit deviceRemoved(adapter.path(), path.path());
}

void Adapter::slotDeviceAdded(QDBusObjectPath path)
{
	qDebug() << "Device added on adapter" << adapter.path() << "with path"
			<< path.path();
	emit deviceAdded(adapter.path(), path.path());
}

void Adapter::slotPropertyChanged(QString key, QDBusVariant value)
{
	QVariant variant = value.variant();

	qDebug() << "Property changed:" << key << variant;
	emit propertyChanged(adapter.path(), key, variant);
}

void Adapter::setProperty(QString key, QVariant value)
{
	adapter.call("SetProperty", key,
		     qVariantFromValue(QDBusVariant(value)));
}
