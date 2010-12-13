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

#include <QtGui>
#include <kuniqueapplication.h>
#include <kcmdlineargs.h>
#include <kaboutdata.h>

#include "mainwindow.h"

int main(int argc, char *argv[])
{
	KAboutData aboutData( "bluezManager", NULL,
		ki18n("BlueZ Manager"), "1.0",
		ki18n("A Bluetooth Manager for KDE."),
		KAboutData::License_GPL_V3,
		ki18n("Copyright (c) 2010 José Antonio Santos Cadenas"));
	KCmdLineArgs::init(argc, argv, &aboutData);

	aboutData.addAuthor(ki18n("José Antonio Santos Cadenas"),
				ki18n("Developer and Project founder"),
				"santoscadenas@gmail.com");
	aboutData.setProgramIconName("preferences-system-bluetooth");
	KUniqueApplication app;
	app.setQuitOnLastWindowClosed(false);
	MainWindow window;
	return app.exec();
}
