#include "adapterview.h"
#include "ui_adapterview.h"

#include "bluez/adapter.h"

AdapterView::AdapterView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdapterView)
{
    ui->setupUi(this);

    path = NULL;
}

AdapterView::~AdapterView()
{
    delete ui;
    if (path)
	    delete path;
}

void AdapterView::setAdapter(const QString path) {
	Adapter adapter(path);
	QVariantMap props = adapter.getProperties();

	this->path = new QString(path);

	ui->nameEdit->setText(props.take("Name").toString());
}
