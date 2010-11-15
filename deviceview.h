#ifndef DEVICEVIEW_H
#define DEVICEVIEW_H

#include <QWidget>

#include "bluez/device.h"

namespace Ui {
    class DeviceView;
}

class DeviceView : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceView(QString path, QWidget *parent = 0);
    ~DeviceView();
    QString devicePath();

private:
    Ui::DeviceView *ui;
    Device device;
};

#endif // DEVICEVIEW_H
