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

#ifndef DEVICEVIEW_H
#define DEVICEVIEW_H

#include <QWidget>

#include "bluez/device.h"

namespace Ui {
	class DeviceView;
}

class DeviceView : public QWidget
{
	Q_OBJECT

public:
	explicit DeviceView(QString path, QWidget *parent = 0);
	~DeviceView();
	QString devicePath();

signals:
	void deletePairing(const QString &device);

public slots:
	void notifyCreation();
	void notifyDestruction();

private slots:
	void propertyChanged(const QString &name, const QDBusVariant &value);
	void connectedClicked();
	void trustedClicked();
	void contextMenu(const QPoint &);
	void newNameSet(const QString &name);

	/* Context menu slots */
	void deletePairing();
	void changeName();

private:
	Ui::DeviceView *ui;
	OrgBluezDeviceInterface device;
	QVariantMap properties;

	void setConnection(bool connected);
	void setTrusted(bool trusted);
};

#endif // DEVICEVIEW_H
