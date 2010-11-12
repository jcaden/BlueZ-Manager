#ifndef ADAPTERVIEW_H
#define ADAPTERVIEW_H

#include <QWidget>

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

private slots:
    void setNameClicked();
    void poweredClicked();
    void propertyChanged(const QString key, const QVariant value);

private:
    void setAddress(QString address);

    Ui::AdapterView *ui;
    Adapter adapter;
};

#endif // ADAPTERVIEW_H
