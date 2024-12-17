#include "user_menu.h"
#include "ui_user_menu.h"

User_Menu::User_Menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::User_Menu)
{

    ui->setupUi(this);
    ui->rent_a_car->setStyleSheet(
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
    ui->return_car->setStyleSheet(
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
    ui->view_car->setStyleSheet(
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

User_Menu::~User_Menu()
{
    delete ui;
}

void User_Menu::on_view_car_clicked()
{
    user_view_car = new User_View_car(this);
    user_view_car->show();
}


void User_Menu::on_rent_a_car_clicked()
{
    user_rent_car = new User_Rent_car(this);
    user_rent_car->show();
}


void User_Menu::on_return_car_clicked()
{
    user_return_car= new User_Return_car(this);
    user_return_car->show();
}

