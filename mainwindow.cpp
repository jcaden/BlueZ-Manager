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
	adjustSize();
	delete view;
}

void MainWindow::adapterAdded(QString path)
{
	AdapterView *adapterView = new AdapterView(path, this);

	layout()->addWidget(adapterView);
	adjustSize();
	adapters.append(adapterView);
}
