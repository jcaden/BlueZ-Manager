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
	con(QDBusConnection::systemBus())
{
	this->path = new QString(path);
	setSignals();
}

Adapter::Adapter(Adapter &adapter) :
		QObject(),
		con(QDBusConnection::systemBus())
{
	path = new QString(*adapter.path);
	setSignals();
}

Adapter::~Adapter()
{
	delete this->path;
}

QMap<QString, QVariant> Adapter::getProperties()
{
	QDBusMessage msg, reply;
	QDBusConnection con = QDBusConnection::systemBus();
	QMap<QString, QVariant> props;

	msg = QDBusMessage::createMethodCall("org.bluez", path->toAscii().data(),
					"org.bluez.Adapter", "GetProperties");
	reply = con.call(msg, QDBus::Block, -1);

	if (reply.type() == QDBusMessage::ErrorMessage) {
		qWarning() << "Error reply received: " << reply.errorMessage();
		return props;
	}

	if (reply.arguments().count() != 1) {
		qWarning() << "Unspected reply received";
		return props;
	}

	if (reply.signature() != "a{sv}") {
		qWarning() << "Unspected reply signature";
		return props;
	}

	QVariant v = reply.arguments().at(0);

	if (v.type() < QVariant::UserType) {
		qWarning() << "Unspected reply received";
		return props;
	}

	props = qdbus_cast<QVariantMap>(reply.arguments()[0]);
	return props;
}

void Adapter::setSignals()
{
//	con.connect("org.bluez", "/", "org.bluez.Adapter", "AdapterRemoved",
//		    this, SLOT(slotAdapterRemoved(QDBusObjectPath)));
//	con.connect("org.bluez", "/", "org.bluez.Manager", "AdapterAdded",
//		    this, SLOT(slotAdapterAdded(QDBusObjectPath)));
}
