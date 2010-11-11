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
    explicit AdapterView(QWidget *parent = 0);
    ~AdapterView();

public slots:
    void setAdapter(const QString path);
    void adapterRemoved(const QString path);

private slots:
    void setNameClicked();

private:
    Ui::AdapterView *ui;
    Adapter *adapter;
};

#endif // ADAPTERVIEW_H
