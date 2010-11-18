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

#include "mainwindow.h"
#include "adapterview.h"

#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
	QWidget(parent),
	manager("org.bluez", "/", QDBusConnection::systemBus())
{
	setWindowTitle(tr("Bluetooth Manager"));

	QVBoxLayout *vLayout = new QVBoxLayout(this);

	QDBusPendingReply<QVariantMap> dprops = manager.GetProperties();
	dprops.waitForFinished();

	if (!dprops.isValid()) {
		qCritical() << "Received unvalid reply";
		return;
	}

	QStringList paths = qdbus_cast<QStringList>(dprops.value()["Adapters"]);
	foreach (QString path, paths) {
		AdapterView *adapterView = new AdapterView(path, this);

		vLayout->addWidget(adapterView);
		adapters.append(adapterView);
	}

	spacer = new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding,
						QSizePolicy::MinimumExpanding);
	vLayout->addItem(spacer);

	connect(&manager, SIGNAL(AdapterAdded(QDBusObjectPath)), this,
					SLOT(adapterAdded(QDBusObjectPath)));
	connect(&manager, SIGNAL(AdapterRemoved(QDBusObjectPath)), this,
					SLOT(adapterRemoved(QDBusObjectPath)));
}

AdapterView *MainWindow::getAdapterView(const QString path)
{
	foreach (AdapterView *view, adapters) {
		if (view->adapterPath() == path)
			return view;
	}

	return NULL;
}

void MainWindow::adapterRemoved(QDBusObjectPath path)
{
	AdapterView *view = getAdapterView(path.path());
	adapters.removeAll(view);
	layout()->removeWidget(view);
	delete view;
}

void MainWindow::adapterAdded(QDBusObjectPath path)
{
	AdapterView *adapterView = new AdapterView(path.path(), this);

	layout()->removeItem(spacer);
	layout()->addWidget(adapterView);
	layout()->addItem(spacer);
	adapters.append(adapterView);
}
