#include "mainwindow.h"
#include "adapterview.h"

#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
	setWindowTitle(tr("Bluetooth Manager"));

	QGridLayout *gridLayout = new QGridLayout(this);

	QStringList paths = manager.getAdapters();
	foreach (QString path, paths) {
		AdapterView *adapterView = new AdapterView(path, this);

		gridLayout->addWidget(adapterView, adapters.count(), 0);
		adapters.append(adapterView);
	}

	setLayout(gridLayout);
}
