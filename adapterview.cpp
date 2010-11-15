#include "adapterview.h"
#include "ui_adapterview.h"

#include "bluez/adapter.h"

enum {
	HIDDEN = 0,
	ALWAYS = 1,
	TEMPORAL = 2,
};

AdapterView::AdapterView(const QString path, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AdapterView),
    adapter(path)
{
    ui->setupUi(this);

    QVariantMap props = adapter.getProperties();

    ui->nameEdit->setText(props["Name"].toString());

    ui->powered->setChecked(props["Powered"].toBool());

    setAddress(props["Address"].toString());

    ui->visibility->addItem(tr("Hidden"));
    ui->visibility->addItem(tr("Always visible"));
    ui->visibility->addItem(tr("Temporaly visible"));

    setVisibility(props["Discoverable"].toBool(),
		  props["DiscoverableTimeout"].toInt());

    connect(ui->apply, SIGNAL(clicked()), this,
	    SLOT(applyClicked()));

    connect(ui->powered, SIGNAL(clicked()), this, SLOT(poweredClicked()));

    connect(ui->visibility, SIGNAL(currentIndexChanged(int)), this,
	    SLOT(comboChanged(int)));

    connect(&adapter, SIGNAL(propertyChanged(QString,QVariant)),
	    this, SLOT(propertyChanged(QString, QVariant)));

    connect(ui->timeout, SIGNAL(valueChanged(int)), this,
	    SLOT(sliderChanged(int)));

    connect(&adapter, SIGNAL(deviceRemoved(QString)), this,
	    SLOT(deviceRemoved(QString)));

    connect(&adapter, SIGNAL(deviceAdded(QString)), this,
	    SLOT(deviceAdded(QString)));

    showDevices(qdbus_cast<QStringList>(props["Devices"]),
		props["Name"].toString());
}

AdapterView::~AdapterView()
{
    delete ui;
}

void AdapterView::showDevices(QStringList devicesPaths, QString name)
{
	devicesWindow = new DevicesWindow(this);
	foreach (QString path, devicesPaths) {
		DeviceView *deviceView = new DeviceView(path, this);
		devicesWindow->addWidget(deviceView);
		devices.append(deviceView);
	}
	devicesWindow->setWindowTitle(tr("Devices for adapter ") +
				      name);
	devicesWindow->show();
}

void AdapterView::setVisibility(bool visible, int timeout)
{
	ui->timeout->setValue(timeout);
	sliderChanged(timeout);

	if (visible) {
		if (timeout > 0) {
			ui->visibility->setCurrentIndex(TEMPORAL);
			ui->visibilityLabel->setEnabled(TRUE);
			ui->visibilityTime->setEnabled(TRUE);
			ui->timeout->setEnabled(TRUE);
			return;
		} else {
			ui->visibility->setCurrentIndex(ALWAYS);
		}
	} else {
		ui->visibility->setCurrentIndex(HIDDEN);
	}

	ui->visibilityLabel->setEnabled(FALSE);
	ui->visibilityTime->setEnabled(FALSE);
	ui->timeout->setEnabled(FALSE);
}

void AdapterView::propertyChanged(const QString key, const QVariant value)
{
	if (key == "Name") {
		ui->nameEdit->setText(value.toString());
		devicesWindow->setWindowTitle(tr("Devices for adapter ") +
					      value.toString());
	} else if (key == "Powered") {
		ui->powered->setChecked(value.toBool());
	} else if (key == "Address") {
		setAddress(value.toString());
	} else if (key == "Discoverable") {
		setVisibility(value.toBool(), ui->timeout->value());
	} else if (key == "DiscoverableTimeout") {
		setVisibility(ui->visibility->currentIndex() != HIDDEN,
			      value.toInt());
	}
}

void AdapterView::applyClicked()
{
	QString name = ui->nameEdit->text();

	adapter.setProperty("Name", name);

	bool discoverable = ui->visibility->currentIndex() != HIDDEN;
	adapter.setProperty("Discoverable", discoverable);

	if (ui->visibility->currentIndex() == TEMPORAL)
		adapter.setProperty("DiscoverableTimeout",
				    (unsigned int) ui->timeout->value());
	else
		adapter.setProperty("DiscoverableTimeout", (unsigned int) 0);
}

void AdapterView::poweredClicked()
{
	adapter.setProperty("Powered", ui->powered->isChecked());
}

void AdapterView::setAddress(QString address)
{
	ui->header->setTitle(tr("Adapter") + " (" + address + ")");
}

void AdapterView::sliderChanged(int value)
{
	QString text = QString::number(value);

	if (value == 1)
		text.append(tr("second"));
	else
		text.append(tr("seconds"));

	ui->visibilityTime->setText(text);
}

void AdapterView::comboChanged(int value)
{
	switch (value) {
	case HIDDEN:
	case ALWAYS:
		ui->visibilityLabel->setEnabled(FALSE);
		ui->visibilityTime->setEnabled(FALSE);
		ui->timeout->setEnabled(FALSE);
		break;
	case TEMPORAL:
		ui->visibilityLabel->setEnabled(TRUE);
		ui->visibilityTime->setEnabled(TRUE);
		ui->timeout->setEnabled(TRUE);
		if (ui->timeout->value() <= 1) {
			ui->timeout->setValue(1);
			sliderChanged(1);
		}
		break;
	default:
		break;
	}
}

QString AdapterView::adapterPath()
{
	return adapter.getPath();
}

DeviceView *AdapterView::getDeviceView(const QString path)
{
	foreach (DeviceView *view, devices) {
		if (view->devicePath() == path)
			return view;
	}

	return NULL;
}

void AdapterView::deviceRemoved(QString path)
{
	DeviceView *view = getDeviceView(path);
	devices.removeAll(view);

	devicesWindow->layout()->removeWidget(view);
	adjustSize();
	delete view;
}

void AdapterView::deviceAdded(QString path)
{
	DeviceView *deviceView = new DeviceView(path, this);

	devicesWindow->layout()->addWidget(deviceView);
	devicesWindow->adjustSize();
	devices.append(deviceView);
}
