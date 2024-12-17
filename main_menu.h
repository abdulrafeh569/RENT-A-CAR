#ifndef MAIN_MENU_H
#define MAIN_MENU_H
#include "select_role.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class main_menu;
}
QT_END_NAMESPACE

class main_menu : public QMainWindow
{
    Q_OBJECT

public:
    main_menu(QWidget *parent = nullptr);
    ~main_menu();

private slots:
    void on_pushButton_clicked();

private:
    Ui::main_menu *ui;
    Select_Role *select_role;
};
#endif // MAIN_MENU_H
