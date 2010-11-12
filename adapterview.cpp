#include "adapterview.h"
#include "ui_adapterview.h"

#include "bluez/adapter.h"

AdapterView::AdapterView(const QString path, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdapterView),
    adapter(path)
{
    ui->setupUi(this);

    QVariantMap props = adapter.getProperties();

    ui->nameEdit->setText(props.take("Name").toString());

    ui->powered->setChecked(props.take("Powered").toBool());

    setAddress(props.take("Address").toString());

    connect(ui->nameButtom, SIGNAL(clicked()), this,
	    SLOT(setNameClicked()));

    connect(ui->powered, SIGNAL(clicked()), this, SLOT(poweredClicked()));

    connect(&adapter, SIGNAL(propertyChanged(QString,QVariant)),
	    this, SLOT(propertyChanged(QString, QVariant)));
}

AdapterView::~AdapterView()
{
    delete ui;
}

void AdapterView::propertyChanged(const QString key, const QVariant value)
{
	if (key == "Name")
		ui->nameEdit->setText(value.toString());
	else if (key == "Powered") {
		ui->powered->setChecked(value.toBool());
	} else if (key == "Address") {
		setAddress(value.toString());
	}
}

void AdapterView::setNameClicked()
{
	QString name = ui->nameEdit->text();

	adapter.setProperty("Name", name);
}

void AdapterView::poweredClicked()
{
	adapter.setProperty("Powered", ui->powered->isChecked());
}

void AdapterView::setAddress(QString address)
{
	ui->header->setTitle("Adapter (" + address + ")");
}
