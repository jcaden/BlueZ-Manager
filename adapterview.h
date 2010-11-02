#ifndef ADAPTERVIEW_H
#define ADAPTERVIEW_H

#include <QWidget>

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

private:
    Ui::AdapterView *ui;
    QString *path;
};

#endif // ADAPTERVIEW_H
