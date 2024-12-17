#include "admin_menu.h"
#include "ui_admin_menu.h"

Admin_Menu::Admin_Menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Admin_Menu)
{
    ui->setupUi(this);
    ui->add_car->setStyleSheet(
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
    ui->remove_car->setStyleSheet(
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

Admin_Menu::~Admin_Menu()
{
    delete ui;
}

void Admin_Menu::on_add_car_clicked()
{
    admin_add_car = new Admin_add_car(this);
    admin_add_car->show();
}


void Admin_Menu::on_remove_car_clicked()
{
    admin_remove_car = new Admin_Remove_car(this);
    admin_remove_car->show();
}


void Admin_Menu::on_view_car_clicked()
{
    admin_view_car = new Admin_View_car(this);
    admin_view_car->show();
}

