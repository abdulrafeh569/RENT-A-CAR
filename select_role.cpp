#include "select_role.h"
#include "ui_select_role.h"

Select_Role::Select_Role(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Select_Role)
{
    setWindowFlags(Qt::Window);
    ui->setupUi(this);
    ui->User->setStyleSheet(
        "QPushButton {"

        "    color: #FFFFFF;""    background-color: rgba(0, 0, 0, 0.7);"
        "    border: 2px solid black;"
        "    border-radius: 10px;"  // Curved border
        "    padding: 5px 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: rgba(0, 0, 0, 0.8);"
        "    color: #E0E0E0;"  // Slightly lighter text color
        "}"
        "QPushButton:pressed {"
        "    background-color: #1C1C1C;"  // Darker grey
        "    border: 2px solid #444444;"  // Darker border on press
        "}"
        );

    ui->Admin->setStyleSheet(
        "QPushButton {"

        "    color: #FFFFFF;""    background-color: rgba(0, 0, 0, 0.7);"
        "    border: 2px solid black;"
        "    border-radius: 10px;"  // Curved border
        "    padding: 5px 10px;"
        "}"
        "QPushButton:hover {"
        "    background-color: rgba(0, 0, 0, 0.8);"
        "    color: #E0E0E0;"  // Slightly lighter text color
        "}"
        "QPushButton:pressed {"
        "    background-color: #1C1C1C;"  // Darker grey
        "    border: 2px solid #444444;"  // Darker border on press
        "}"
        );

}

Select_Role::~Select_Role()
{
    delete ui;
}

void Select_Role::on_Admin_clicked()
{
    admin_login = new Admin_Login(this);
    admin_login->show();
}


void Select_Role::on_User_clicked()
{
    user_choice = new User_Choice(this);
    user_choice->show();
}

