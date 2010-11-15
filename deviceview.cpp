#include "deviceview.h"
#include "ui_deviceview.h"

DeviceView::DeviceView(QString path, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceView),
    device(path)
{
    ui->setupUi(this);

    QVariantMap props = device.getProperties();

    ui->device->setTitle(props["Name"].toString());
    ui->address->setText(props["Address"].toString());
    ui->checkBox->setChecked(props["Connected"].toBool());
}

DeviceView::~DeviceView()
{
    delete ui;
}

QString DeviceView::devicePath()
{
	return device.getPath();
}
