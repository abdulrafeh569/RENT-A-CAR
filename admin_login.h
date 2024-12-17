#ifndef ADMIN_LOGIN_H
#define ADMIN_LOGIN_H
#include "admin_menu.h"

#include <QWidget>
#include <QMessageBox>
namespace Ui {
class Admin_Login;
}

class Admin_Login : public QWidget
{
    Q_OBJECT

public:
    explicit Admin_Login(QWidget *parent = nullptr);
    ~Admin_Login();

private slots:
    void on_login_clicked();

private:
    Ui::Admin_Login *ui;
    Admin_Menu *admin_menu;
    void showStyledMessageBox(QMessageBox::Icon icon, const QString &title, const QString &message);

};

#endif // ADMIN_LOGIN_H
