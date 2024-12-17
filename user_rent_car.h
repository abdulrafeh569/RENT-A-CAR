#ifndef USER_RENT_CAR_H
#define USER_RENT_CAR_H

#include <QWidget>

namespace Ui {
class User_Rent_car;
}

class User_Rent_car : public QWidget
{
    Q_OBJECT

public:
    explicit User_Rent_car(QWidget *parent = nullptr);
    ~User_Rent_car();

private slots:
    void on_rent_car_clicked();

    void on_confirm_clicked();

private:
    Ui::User_Rent_car *ui;
    void loadData();
    void updateCarsData();
};

#endif // USER_RENT_CAR_H
