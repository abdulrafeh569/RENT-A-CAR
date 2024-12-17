#ifndef ADMIN_MENU_H
#define ADMIN_MENU_H
#include "admin_add_car.h"
#include "admin_remove_car.h"
#include "admin_view_car.h"
#include <QWidget>

namespace Ui {
class Admin_Menu;
}

class Admin_Menu : public QWidget
{
    Q_OBJECT

public:
    explicit Admin_Menu(QWidget *parent = nullptr);
    ~Admin_Menu();

private slots:
    void on_add_car_clicked();

    void on_remove_car_clicked();

    void on_view_car_clicked();

private:
    Ui::Admin_Menu *ui;
    Admin_add_car *admin_add_car;
    Admin_Remove_car *admin_remove_car;
    Admin_View_car *admin_view_car;
};

#endif // ADMIN_MENU_H
