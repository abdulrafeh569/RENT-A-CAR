#ifndef ADMIN_VIEW_CAR_H
#define ADMIN_VIEW_CAR_H

#include <QWidget>

namespace Ui {
class Admin_View_car;
}

class Admin_View_car : public QWidget
{
    Q_OBJECT

public:
    explicit Admin_View_car(QWidget *parent = nullptr);
    ~Admin_View_car();

private:
    Ui::Admin_View_car *ui;
    void loadData();
};

#endif // ADMIN_VIEW_CAR_H
