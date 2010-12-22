#include "pincodedialog.h"
#include "ui_pincodedialog.h"

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

#include <QDBusConnection>

PinCodeDialog::PinCodeDialog(QDBusMessage &reply, QWidget *parent) :
	QDialog(parent),
	ui(new Ui::PinCodeDialog)
{
	init();
	this->reply = new QDBusMessage(reply);
}

PinCodeDialog::PinCodeDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::PinCodeDialog)
{
	init();
	reply = NULL;
}

void PinCodeDialog::init()
{
	ui->setupUi(this);

	connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(accepted()));

	connect(this, SIGNAL(finished(int)), this, SLOT(deleteLater()));
}

PinCodeDialog::~PinCodeDialog()
{
	delete ui;
	if (reply)
		delete reply;
}

void PinCodeDialog::accepted()
{
	QString code = ui->pinCode->text();

	emit accepted(code);
	if (!reply)
		return;

	*reply << code;
	QDBusConnection::systemBus().send(*reply);

	this->deleteLater();
}
