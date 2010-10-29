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
	con.connect("org.bluez", "/", "org.bluez.Adapter", "AdapterRemoved",
		    this, SLOT(slotAdapterRemoved(QDBusObjectPath)));
	con.connect("org.bluez", "/", "org.bluez.Manager", "AdapterAdded",
		    this, SLOT(slotAdapterAdded(QDBusObjectPath)));
}

Adapter::Adapter(Adapter &adapter) :
		QObject(),
		con(QDBusConnection::systemBus())
{
	path = new QString(*adapter.path);
}

Adapter::~Adapter()
{
	delete this->path;
}
