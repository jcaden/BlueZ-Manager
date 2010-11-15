#ifndef ADAPTERVIEW_H
#define ADAPTERVIEW_H

#include <QtGui>

#include <deviceview.h>
#include <deviceswindow.h>
#include <bluez/adapter.h>

namespace Ui {
    class AdapterView;
}

class AdapterView : public QWidget
{
    Q_OBJECT

public:
    explicit AdapterView(const QString path, QWidget *parent = 0);
    ~AdapterView();

    QString adapterPath();

private slots:
    void applyClicked();
    void poweredClicked();
    void propertyChanged(const QString key, const QVariant value);
    void sliderChanged(int value);
    void comboChanged(int value);
    void deviceRemoved(QString path);
    void deviceAdded(QString path);
    void showDevicesClicked(bool checked);

private:
    void setAddress(QString address);
    void setVisibility(bool visible, int timeout);
    void createDevicesView(QStringList devicesPaths, QString name);
    DeviceView *getDeviceView(const QString path);

    Ui::AdapterView *ui;
    Adapter adapter;
    QList<DeviceView *> devices;
    DevicesWindow *devicesWindow;
    QSpacerItem *spacer;
};

#endif // ADAPTERVIEW_H
