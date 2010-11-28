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

#include "deviceswindow.h"
#include "ui_deviceswindow.h"

#include "adapterview.h"
#include "devicesearchview.h"

DevicesWindow::DevicesWindow(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::DevicesWindow)
{
	ui->setupUi(this);

	connect(ui->addDevice, SIGNAL(clicked()), this, SLOT(addDevice()));
}

DevicesWindow::~DevicesWindow()
{
	delete ui;
}

void DevicesWindow::addWidget(QWidget *widget)
{
	ui->devices->addWidget(widget);
}

void DevicesWindow::removeWidget(QWidget *widget)
{
	ui->devices->removeWidget(widget);
}

void DevicesWindow::addDevice()
{
	if (!parent()->inherits("AdapterView"))
		return;
	AdapterView *adapter = (AdapterView *)parent();
	DeviceSearchView *search= new DeviceSearchView(this);

	connect(adapter->getAdapter(), SIGNAL(DeviceDisappeared(QString)),
				search, SLOT(DeviceDisappeared(QString)));
	connect(adapter->getAdapter(), SIGNAL(DeviceFound(QString,QVariantMap)),
				search, SLOT(DeviceFound(QString,QVariantMap)));
	connect(adapter->getAdapter(),
			SIGNAL(PropertyChanged(QString,QDBusVariant)),
			search, SLOT(propertyChanged(QString,QDBusVariant)));

	search->show();
	adapter->getAdapter()->StartDiscovery();
}
