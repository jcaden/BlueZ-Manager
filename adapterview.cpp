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

void AdapterView::setAdapter(const QString path)
{
	Adapter adapter(path);
	QVariantMap props = adapter.getProperties();

	if (this->path)
		delete this->path;

	this->path = new QString(path);

	ui->nameEdit->setText(props.take("Name").toString());

	connect(ui->nameButtom, SIGNAL(clicked()), this,
		SLOT(setNameClicked()));
}

void AdapterView::adapterRemoved(const QString path)
{
	if (!this->path || (path != this->path))
		return;

	delete this->path;
	this->path = NULL;

	ui->nameEdit->setText("");
	this->disconnect(ui->nameButtom, SIGNAL(clicked()), this,
			 SLOT(setNameClicked()));
}

void AdapterView::setNameClicked()
{
	if (!path)
		return;

	QString name = ui->nameEdit->text();

	Adapter adapter(*path);
	adapter.setProperty("Name", name);
}
