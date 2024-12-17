#ifndef ADMIN_REMOVE_CAR_H
#define ADMIN_REMOVE_CAR_H

#include <QWidget>

namespace Ui {
class Admin_Remove_car;
}

class Admin_Remove_car : public QWidget
{
    Q_OBJECT

public:
    explicit Admin_Remove_car(QWidget *parent = nullptr);
    ~Admin_Remove_car();

private slots:


    void on_remove_car_clicked();

private:
    Ui::Admin_Remove_car *ui;
};

#endif // ADMIN_REMOVE_CAR_H
