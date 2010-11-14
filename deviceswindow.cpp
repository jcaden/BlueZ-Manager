#include "deviceswindow.h"
#include "ui_deviceswindow.h"

DevicesWindow::DevicesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DevicesWindow)
{
    ui->setupUi(this);
}

DevicesWindow::~DevicesWindow()
{
    delete ui;
}

void DevicesWindow::addWidget(QWidget *widget)
{
	ui->gridLayout->addWidget(widget);
}
