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

#ifndef ADAPTERVIEW_H
#define ADAPTERVIEW_H

#include <QtGui>

#include <deviceview.h>
#include <deviceswindow.h>
#include <bluez/adapter.h>

namespace Ui {
	class AdapterView;
}

class AdapterView : public QWidget
{
	Q_OBJECT

public:
	explicit AdapterView(const QString path, QWidget *parent = 0);
	~AdapterView();

	QString adapterPath();

private slots:
	void applyClicked();
	void poweredClicked();
	void propertyChanged(const QString key, const QVariant value);
	void sliderChanged(int value);
	void comboChanged(int value);
	void deviceRemoved(QString path);
	void deviceAdded(QString path);
	void showDevicesClicked(bool checked);

private:
	void setAddress(QString address);
	void setVisibility(bool visible, int timeout);
	void createDevicesView(QStringList devicesPaths, QString name);
	DeviceView *getDeviceView(const QString path);

	Ui::AdapterView *ui;
	Adapter adapter;
	QList<DeviceView *> devices;
	DevicesWindow *devicesWindow;
	QSpacerItem *spacer;
};

#endif // ADAPTERVIEW_H
