#ifndef DEVICESWINDOW_H
#define DEVICESWINDOW_H

#include <QDialog>

namespace Ui {
    class DevicesWindow;
}

class DevicesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit DevicesWindow(QWidget *parent = 0);
    ~DevicesWindow();
    void addWidget(QWidget *widget);

private:
    Ui::DevicesWindow *ui;
};

#endif // DEVICESWINDOW_H
