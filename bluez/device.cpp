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

#include "device.h"

Device::Device(QString path) :
	QObject(),
	device("org.bluez", path,
		"org.bluez.Device", QDBusConnection::systemBus())
{
	setSignals();
}

Device::Device(Device &device) :
		QObject(),
		device("org.bluez", device.device.path(),
			"org.bluez.Device", QDBusConnection::systemBus())
{
	setSignals();
}

Device::~Device()
{
	qDebug() << "Destroying device" << device.path();
}

QVariantMap Device::getProperties()
{
	QDBusMessage reply = device.call("GetProperties");

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

void Device::setSignals()
{
//	con.connect("org.bluez", "/", "org.bluez.Adapter", "AdapterRemoved",
//		    this, SLOT(slotAdapterRemoved(QDBusObjectPath)));
//	con.connect("org.bluez", "/", "org.bluez.Manager", "AdapterAdded",
//		    this, SLOT(slotAdapterAdded(QDBusObjectPath)));
}
