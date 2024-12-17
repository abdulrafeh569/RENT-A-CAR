#ifndef USER_MENU_H
#define USER_MENU_H
#include "user_view_car.h"
#include "user_rent_car.h"
#include "user_return_car.h"
#include <QWidget>

namespace Ui {
class User_Menu;
}

class User_Menu : public QWidget
{
    Q_OBJECT

public:
    explicit User_Menu(QWidget *parent = nullptr);
    ~User_Menu();

private slots:
    void on_view_car_clicked();

    void on_rent_a_car_clicked();

    void on_return_car_clicked();

private:
    Ui::User_Menu *ui;
    User_Rent_car *user_rent_car;
    User_Return_car *user_return_car;
    User_View_car *user_view_car;
};

#endif // USER_MENU_H
