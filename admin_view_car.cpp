#include "admin_view_car.h"
#include "ui_admin_view_car.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

Admin_View_car::Admin_View_car(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Admin_View_car)
{
    setWindowFlags(Qt::Window);
    ui->setupUi(this);

    ui->table->setColumnCount(5);
    QStringList headers = {"Name", "Company", "Model", "Price", "Availability"};
    ui->table->setHorizontalHeaderLabels(headers);
    loadData();


    ui->table->setStyleSheet(
        "QTableWidget {"
        "    background-color: rgba(0, 0, 0, 0.5);" // Semi-transparent black
        "    color: #FFFFFF;"                        // White text
        "    border: 2px solid black;"               // Thin black border
        "    border-radius: 10px;"                   // Rounded corners
        "    font-size: 16px;"                       // Font size for the cells
        "    gridline-color: #888888;"               // Gridline color
        "    font-weight: bold;"
        "}"

        "QHeaderView::section {"
        "    background-color: rgba(0, 0, 0, 0.5);"  // Semi-transparent black for headers
        "    color: #FFFFFF;"                        // White text for headers
        "    border: 2px solid black;"               // Thin black border
        "    border-radius: 5px;"                    // Rounded corners for headers
        "    font-size: 18px;"                       // Font size for headers
        "    font-weight: bold;"                     // Bold font for headers
        "    padding: 5px;"                          // Padding inside headers
        "    text-align: center;"                    // Center align text in headers
        "}"

        "QTableWidget::item {"
        "    text-align: center;"                    // Center align text in cells
        "}"
        );

    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->table->verticalHeader()->setVisible(false);
    ui->table->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->table->verticalHeader()->setDefaultSectionSize(40);

    for (int row = 0; row < ui->table->rowCount(); ++row)
    {
        for (int col = 0; col < ui->table->columnCount(); ++col)
        {
            QTableWidgetItem* item = ui->table->item(row, col);
            if (item)
            {
                item->setTextAlignment(Qt::AlignCenter);
            }
        }
    }
}

void Admin_View_car::loadData()
{
    QFile file("Cars_data.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "Error", "Could not open file.");
        return;
    }

    QTextStream in(&file);
    QString name, company, model, price, availability;
    int row = 0;
    while (!in.atEnd())
    {
        QString line = in.readLine().trimmed();

        if (line.startsWith("Name: "))
        {
            name = line.remove(0, 6);
        }
        else if (line.startsWith("Company: "))
        {
            company = line.remove(0, 9);
        }
        else if (line.startsWith("Model: "))
        {
            model = line.remove(0, 7);
        }
        else if (line.startsWith("Price: "))
        {
            price = line.remove(0, 7);
        }
        else if (line.startsWith("Availability: "))
        {
            availability = line.remove(0, 14);
        }
        else if (line == "----------")
        {
            if (!name.isEmpty())
            {
                ui->table->insertRow(row);
                ui->table->setItem(row, 0, new QTableWidgetItem(name));
                ui->table->setItem(row, 1, new QTableWidgetItem(company));
                ui->table->setItem(row, 2, new QTableWidgetItem(model));
                ui->table->setItem(row, 3, new QTableWidgetItem(price));
                ui->table->setItem(row, 4, new QTableWidgetItem(availability));

                row++;
            }

            name.clear();
            company.clear();
            model.clear();
            price.clear();
            availability.clear();
        }
    }
    file.close();
}

Admin_View_car::~Admin_View_car()
{
    delete ui;
}
