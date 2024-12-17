#ifndef USER_RETURN_CAR_H
#define USER_RETURN_CAR_H

#include <QWidget>

namespace Ui {
class User_Return_car;
}

class User_Return_car : public QWidget
{
    Q_OBJECT

public:
    explicit User_Return_car(QWidget *parent = nullptr);
    ~User_Return_car();

private slots:
    void on_returnn_clicked();

    void on_name_edit_editingFinished();

private:
    Ui::User_Return_car *ui;
    void updateCarsData();
    void removeCheckedCars();
    void generateReceipt();
};

#endif // USER_RETURN_CAR_H
