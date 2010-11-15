#include "mainwindow.h"
#include "adapterview.h"

#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
	setWindowTitle(tr("Bluetooth Manager"));

	QVBoxLayout *vLayout = new QVBoxLayout(this);

	QStringList paths = manager.getAdapters();
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
