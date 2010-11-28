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

#ifndef DEVICESEARCHVIEW_H
#define DEVICESEARCHVIEW_H

#include <QDialog>
#include <QVariantMap>
#include <QSet>
#include <QDBusVariant>

namespace Ui {
	class DeviceSearchView;
}

class DeviceSearchView : public QDialog
{
	Q_OBJECT

public:
	explicit DeviceSearchView(QWidget *parent = 0);
	~DeviceSearchView();

public slots:
	void DeviceDisappeared(const QString &address);
	void DeviceFound(const QString &address, const QVariantMap &values);
	void propertyChanged(const QString name, const QDBusVariant value);

private:
	Ui::DeviceSearchView *ui;
};

#endif // DEVICESEARCHVIEW_H
