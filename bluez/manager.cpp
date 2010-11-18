/*
 * Qt BlueZ Manager
 *
 * Copyright (C) 2010 Jose Antonio Santos-Cadenas <santoscadenas at gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <QtDBus/QtDBus>
#include <QDebug>

#include "manager.h"

Manager::Manager() :
	QObject(),
	manager("org.bluez", "/", "org.bluez.Manager",
						QDBusConnection::systemBus())
{
	QDBusConnection::systemBus().connect("org.bluez", "/",
			"org.bluez.Manager", "AdapterRemoved", this,
			SLOT(slotAdapterRemoved(QDBusObjectPath)));
	QDBusConnection::systemBus().connect("org.bluez", "/",
			"org.bluez.Manager", "AdapterAdded", this,
			SLOT(slotAdapterAdded(QDBusObjectPath)));
}

QVariantMap Manager::getProperties()
{
	QDBusMessage reply = manager.call("GetProperties");

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

void Manager::slotAdapterRemoved(QDBusObjectPath path)
{
	emit adapterRemoved(path.path());
}

void Manager::slotAdapterAdded(QDBusObjectPath path)
{
	emit adapterAdded(path.path());
}
