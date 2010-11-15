#include "deviceview.h"
#include "ui_deviceview.h"

DeviceView::DeviceView(QString path, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceView),
    device(path)
{
    ui->setupUi(this);

    QVariantMap props = device.getProperties();

    ui->device->setTitle(props.take("Name").toString());
    ui->address->setText(props.take("Address").toString());
    ui->checkBox->setChecked(props.take("Connected").toBool());
}

DeviceView::~DeviceView()
{
    delete ui;
}

QString DeviceView::devicePath()
{
	return device.getPath();
}
