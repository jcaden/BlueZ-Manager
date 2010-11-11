#include "adapterview.h"
#include "ui_adapterview.h"

#include "bluez/adapter.h"

AdapterView::AdapterView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdapterView)
{
    ui->setupUi(this);

    adapter = NULL;
}

AdapterView::~AdapterView()
{
    delete ui;
    if (adapter)
	    delete adapter;
}

void AdapterView::setAdapter(const QString path)
{
	if (adapter)
		delete adapter;

	adapter = new Adapter(path);
	QVariantMap props = adapter->getProperties();

	ui->nameEdit->setText(props.take("Name").toString());

	ui->powered->setChecked(props.take("Powered").toBool());

	connect(ui->nameButtom, SIGNAL(clicked()), this,
		SLOT(setNameClicked()));

	connect(ui->powered, SIGNAL(clicked()), this, SLOT(poweredClicked()));

	connect(adapter, SIGNAL(propertyChanged(QString,QString,QVariant)),
		this, SLOT(propertyChanged(QString, QString, QVariant)));
}

void AdapterView::propertyChanged(const QString apath, const QString key,
					    const QVariant value)
{
	if (key == "Name")
		ui->nameEdit->setText(value.toString());
	else if (key == "Powered") {
		ui->powered->setChecked(value.toBool());
	}
}

void AdapterView::adapterRemoved(const QString path)
{
	if (!adapter || (path != adapter->getPath()))
		return;

	delete adapter;
	adapter = NULL;

	ui->nameEdit->setText("");
	this->disconnect(ui->nameButtom, SIGNAL(clicked()), this,
			 SLOT(setNameClicked()));
}

void AdapterView::setNameClicked()
{
	if (!adapter)
		return;

	QString name = ui->nameEdit->text();

	adapter->setProperty("Name", name);
}

void AdapterView::poweredClicked()
{
	if (!adapter)
		return;

	adapter->setProperty("Powered", ui->powered->isChecked());
}
