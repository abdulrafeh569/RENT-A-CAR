#include "main_menu.h"
#include "ui_main_menu.h"

main_menu::main_menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::main_menu)
{
    ui->setupUi(this);
}

main_menu::~main_menu()
{
    delete ui;
}

void main_menu::on_pushButton_clicked()
{
    select_role = new Select_Role(this);
    hide();
    select_role->show();
}

