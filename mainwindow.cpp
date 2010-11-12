#include "mainwindow.h"
#include "adapterview.h"

#include <QtGui>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
	setWindowTitle(tr("Bluetooth Manager"));
	AdapterView *adapterView = new AdapterView(this);

	QGridLayout *gridLayout = new QGridLayout(this);

	gridLayout->addWidget(adapterView, 0, 0);
	setLayout(gridLayout);
}
