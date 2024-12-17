#ifndef USER_CHOICE_H
#define USER_CHOICE_H
#include "user_menu.h"
#include <QWidget>
#include<QMessageBox>

namespace Ui {
class User_Choice;
}

class User_Choice : public QWidget
{
    Q_OBJECT

public:
    explicit User_Choice(QWidget *parent = nullptr);
    ~User_Choice();

private slots:
    void on_register_2_clicked();

    void on_login_clicked();

private:
    Ui::User_Choice *ui;
    User_Menu *user_menu;
    void showStyledMessageBox(QMessageBox::Icon icon, const QString &title, const QString &message);
};

#endif // USER_CHOICE_H
