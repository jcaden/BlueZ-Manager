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
#include "bluez/device.h"
#include "pincodedialog.h"

#include <QDebug>
#include <QDBusConnection>

#include <knotification.h>
#include <klocalizedstring.h>

ManagerAgent::ManagerAgent(const QString &path, QObject *parent) :
	QObject(parent),
	path(path)
{
	pinCode = NULL;
}

ManagerAgent::~ManagerAgent()
{
	if (pinCode)
		delete pinCode;
}

void ManagerAgent::setPinCode(QString &pin)
{
	pinCode = new QString(pin);
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
	QDBusConnection::systemBus().unregisterObject(path);
	delete this;
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

QString ManagerAgent::RequestPinCode(const QDBusObjectPath &device,
						const QDBusMessage &message)
{
	if (pinCode)
		return *pinCode;

	OrgBluezDeviceInterface dev("org.bluez", device.path(),
						QDBusConnection::systemBus());
	QDBusPendingReply<QVariantMap>reply = dev.GetProperties();
	reply.waitForFinished();
	reply.reply();

	if (!reply.isValid()) {
		qCritical() << "Received unvalid reply";
		return "";
	}

	QVariantMap properties = reply.value();
	KNotification *notification= new KNotification("requestPinCode",
				KNotification::CloseWhenWidgetActivated);
	notification->setTitle(i18n("Enter PIN code"));
	notification->setText(i18n("Enter PIN code for device %1",
					properties["Alias"].toString()));
	notification->setActions(QStringList(tr("Show window")));

	message.setDelayedReply(true);
	QDBusMessage rep = message.createReply();
	PinCodeDialog *dialog = new PinCodeDialog(rep);
	dialog->show();

	notification->setWidget(dialog);
	// TODO: Connect action signal to show the window
	notification->sendEvent();


	return QString();
}
