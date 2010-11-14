#ifndef DEVICEVIEW_H
#define DEVICEVIEW_H

#include <QWidget>

namespace Ui {
    class DeviceView;
}

class DeviceView : public QWidget
{
    Q_OBJECT

public:
    explicit DeviceView(QString path, QWidget *parent = 0);
    ~DeviceView();

private:
    Ui::DeviceView *ui;
};

#endif // DEVICEVIEW_H
