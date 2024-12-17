#ifndef ADMIN_ADD_CAR_H
#define ADMIN_ADD_CAR_H
#include <QMessageBox>
#include <QWidget>

namespace Ui {
class Admin_add_car;
}

class Admin_add_car : public QWidget
{
    Q_OBJECT

public:
    explicit Admin_add_car(QWidget *parent = nullptr);
    ~Admin_add_car();

private slots:
    void on_login_clicked();

private:
    Ui::Admin_add_car *ui;
    void showStyledMessageBox(QMessageBox::Icon icon, const QString &title, const QString &message);
};

#endif // ADMIN_ADD_CAR_H
