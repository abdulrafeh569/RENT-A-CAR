#ifndef SELECT_ROLE_H
#define SELECT_ROLE_H
#include "admin_login.h"
#include "user_choice.h"
#include <QWidget>

namespace Ui {
class Select_Role;
}

class Select_Role : public QWidget
{
    Q_OBJECT

public:
    explicit Select_Role(QWidget *parent = nullptr);
    ~Select_Role();

private slots:
    void on_Admin_clicked();

    void on_User_clicked();

private:
    Ui::Select_Role *ui;
    Admin_Login *admin_login;
    User_Choice *user_choice;
};

#endif // SELECT_ROLE_H
