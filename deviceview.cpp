#include "deviceview.h"
#include "ui_deviceview.h"

DeviceView::DeviceView(QString path, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DeviceView)
{
    ui->setupUi(this);

    ui->address->setText(path);
}

DeviceView::~DeviceView()
{
    delete ui;
}
