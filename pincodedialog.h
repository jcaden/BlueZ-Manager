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

#ifndef PINCODEDIALOG_H
#define PINCODEDIALOG_H

#include <QDialog>
#include <QDBusMessage>

namespace Ui {
	class PinCodeDialog;
}

class PinCodeDialog : public QDialog
{
	Q_OBJECT

public:
	explicit PinCodeDialog(QDBusMessage &reply, QWidget *parent = 0);
	explicit PinCodeDialog(QWidget *parent = 0);
	~PinCodeDialog();

private slots:
	void accepted();

signals:
	void accepted(QString &value);


private:
	void init();

	Ui::PinCodeDialog *ui;
	QDBusMessage *reply;

};

#endif // PINCODEDIALOG_H
