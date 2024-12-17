#ifndef USER_VIEW_CAR_H
#define USER_VIEW_CAR_H

#include <QWidget>

namespace Ui {
class User_View_car;
}

class User_View_car : public QWidget
{
    Q_OBJECT

public:
    explicit User_View_car(QWidget *parent = nullptr);
    ~User_View_car();

private:
    Ui::User_View_car *ui;
    void loadData();
};

#endif // USER_VIEW_CAR_H
