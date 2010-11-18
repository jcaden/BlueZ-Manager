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
	QWidget(parent)
{
	setWindowTitle(tr("Bluetooth Manager"));

	QVBoxLayout *vLayout = new QVBoxLayout(this);

	QStringList paths = qdbus_cast<QStringList>(
					manager.getProperties()["Adapters"]);
	foreach (QString path, paths) {
		AdapterView *adapterView = new AdapterView(path, this);

		vLayout->addWidget(adapterView);
		adapters.append(adapterView);
	}

	spacer = new QSpacerItem(0, 0, QSizePolicy::MinimumExpanding,
						QSizePolicy::MinimumExpanding);
	vLayout->addItem(spacer);

	connect(&manager, SIGNAL(adapterAdded(QString)), this,
						SLOT(adapterAdded(QString)));
	connect(&manager, SIGNAL(adapterRemoved(QString)), this,
						SLOT(adapterRemoved(QString)));
}

AdapterView *MainWindow::getAdapterView(const QString path)
{
	foreach (AdapterView *view, adapters) {
		if (view->adapterPath() == path)
			return view;
	}

	return NULL;
}

void MainWindow::adapterRemoved(QString path)
{
	AdapterView *view = getAdapterView(path);
	adapters.removeAll(view);
	layout()->removeWidget(view);
	delete view;
}

void MainWindow::adapterAdded(QString path)
{
	AdapterView *adapterView = new AdapterView(path, this);

	layout()->removeItem(spacer);
	layout()->addWidget(adapterView);
	layout()->addItem(spacer);
	adapters.append(adapterView);
}
