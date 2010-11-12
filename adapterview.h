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

    QString adapterPath();

private slots:
    void applyClicked();
    void poweredClicked();
    void propertyChanged(const QString key, const QVariant value);
    void sliderChanged(int value);
    void comboChanged(int value);

private:
    void setAddress(QString address);
    void setVisibility(bool visible, int timeout);

    Ui::AdapterView *ui;
    Adapter adapter;
};

#endif // ADAPTERVIEW_H
