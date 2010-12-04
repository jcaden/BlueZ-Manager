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

#include "manageragent.h"

#include <QDebug>

ManagerAgent::ManagerAgent(QWidget *parent) :
	QWidget(parent)
{
}

ManagerAgent::~ManagerAgent()
{
}

/* D-Bus Agent slots */
void ManagerAgent::Authorize(const QDBusObjectPath &device, const QString &uuid)
{
	/* TODO: Implement this method */
	qDebug() << "Authorize received. Device: " << device.path() <<
							" Uuid: " << uuid;
}

void ManagerAgent::Cancel()
{
	/* TODO: Implement this method */
	qDebug() << "Cancel received";
}

void ManagerAgent::ConfirmModeChange(const QString &mode)
{
	/* TODO: Implement this method */
	qDebug() << "ConfirmModeChange received. Mode " << mode;
}

void ManagerAgent::DisplayPasskey(const QDBusObjectPath &device, uint passkey)
{
	/* TODO: Implement this method */
	qDebug() << "DisplayPasskey received. Device: " << device.path() <<
				" Passkey: " << QString::number(passkey);
}

void ManagerAgent::Release()
{
	/* TODO: Implement this method */
	qDebug() << "Release received";
}

void ManagerAgent::RequestConfirmation(const QDBusObjectPath &device,
								uint passkey)
{
	/* TODO: Implement this method */
	qDebug() << "RequestConfirmation received. Device: " << device.path() <<
				" Passkey: " << QString::number(passkey);
}

uint ManagerAgent::RequestPasskey(const QDBusObjectPath &device)
{
	/* TODO: Implement this method */
	qDebug() << "RequestPasskey received. Device " << device.path();
	return 0;
}

QString ManagerAgent::RequestPinCode(const QDBusObjectPath &device)
{
	/* TODO: Implement this method */
	qDebug() << "RequestPinCode received. Device: " << device.path();
	return "0000";
}
