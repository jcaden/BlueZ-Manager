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

#include "manager.h"

Manager::Manager() :
	QObject(),
	con(QDBusConnection::systemBus())
{
	con.connect("org.bluez", "/", "org.bluez.Manager", "AdapterRemoved",
		    this, SLOT(slotAdapterRemoved(QDBusObjectPath)));
	con.connect("org.bluez", "/", "org.bluez.Manager", "AdapterAdded",
		    this, SLOT(slotAdapterAdded(QDBusObjectPath)));
}

QList<QString> Manager::getAdapters()
{
	QDBusMessage msg, reply;
	QDBusConnection con = QDBusConnection::systemBus();
	QList<QString> adapters;

	msg = QDBusMessage::createMethodCall("org.bluez", "/",
					"org.bluez.Manager", "ListAdapters");
	reply = con.call(msg, QDBus::Block, -1);

	if (reply.type() == QDBusMessage::ErrorMessage) {
		qWarning() << "Error reply received: " << reply.errorMessage();
		return adapters;
	}

	if (reply.arguments().count() != 1) {
		qWarning() << "Unspected reply received";
		return adapters;
	}

	if (reply.signature() != "ao") {
		qWarning() << "Unspected reply signature";
		return adapters;
	}

	return qdbus_cast<QStringList>(reply.arguments()[0]);
}

void Manager::slotAdapterRemoved(QDBusObjectPath path)
{
	emit adapterRemoved(path.path());
}

void Manager::slotAdapterAdded(QDBusObjectPath path)
{
	emit adapterAdded(path.path());
}
