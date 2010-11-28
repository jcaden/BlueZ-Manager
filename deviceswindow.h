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

#ifndef DEVICESWINDOW_H
#define DEVICESWINDOW_H

#include <QDialog>
#include <QVariantMap>

#include "devicesearchview.h"

namespace Ui {
	class DevicesWindow;
}

class DevicesWindow : public QDialog
{
	Q_OBJECT

public:
	explicit DevicesWindow(QWidget *parent = 0);
	~DevicesWindow();
	void addWidget(QWidget *widget);
	void removeWidget(QWidget *widget);

private slots:
	void addDevice();

private:
	Ui::DevicesWindow *ui;
	DeviceSearchView *search;
};

#endif // DEVICESWINDOW_H
