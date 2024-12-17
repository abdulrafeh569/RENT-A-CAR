#include "user_rent_car.h"
#include "ui_user_rent_car.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QLineEdit>
User_Rent_car::User_Rent_car(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::User_Rent_car)
{
    setWindowFlags(Qt::Window);
    ui->setupUi(this);
    ui->confirm->hide();
    this->setStyleSheet(

        "QLabel {"
        "    background-color: rgba(0, 0, 0, 0.7);"
        "    color: #FFFFFF;"            // White text
        "    border: 2px solid black;"   // Thin black border
        "    border-radius: 10px;"       // Rounded corners
        "    padding: 5px 10px;"         // Spacing inside the label
        "}"


        "QLineEdit {"
        "    background-color: rgba(0, 0, 0, 0.5);" // Semi-transparent black
        "    color: #FFFFFF;"                        // White text
        "    border: 2px solid black;"               // Thin black border
        "    border-radius: 10px;"                   // Rounded corners
        "    padding: 5px 10px;"                     // Spacing inside the input field
        "    font-size: 20px;"
        "    font-weight: bold;"
        "}"

        "QLineEdit:hover {"
        "    background-color: rgba(46, 46, 46, 0.5);" // Slightly lighter semi-transparent black
        "    color: #E0E0E0;"                          // Slightly lighter text on hover
        "    border: 2px solid #444444;"               // Slightly lighter border on hover
        "}"

        "QLineEdit:focus {"
        "    background-color: rgba(0, 0, 0, 0.5);"    // Keep semi-transparent black on focus
        "    color: #FFFFFF;"                          // Keep text white
        "    font-size: 16px;"                         // Keep the font size on focus
        "    border: 2px solid #888888;"               // Slightly lighter border on focus
        "}"
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


    ui->table->setColumnCount(5);
    QStringList headers = {"Name", "Company", "Model", "Price", "Select"};
    ui->table->setHorizontalHeaderLabels(headers);


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


    loadData();
}

User_Rent_car::~User_Rent_car()
{
    delete ui;
}

void User_Rent_car::loadData()
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
            if (!name.isEmpty() && availability.toLower() == "yes")
            {
                ui->table->insertRow(row);

                ui->table->setItem(row, 0, new QTableWidgetItem(name));
                ui->table->setItem(row, 1, new QTableWidgetItem(company));
                ui->table->setItem(row, 2, new QTableWidgetItem(model));
                ui->table->setItem(row, 3, new QTableWidgetItem(price));

                QWidget* checkboxWidget = new QWidget();
                QCheckBox* checkbox = new QCheckBox();
                QHBoxLayout* layout = new QHBoxLayout(checkboxWidget);
                layout->addWidget(checkbox);
                layout->setAlignment(Qt::AlignCenter);
                layout->setContentsMargins(0, 0, 0, 0);
                checkboxWidget->setLayout(layout);
                ui->table->setCellWidget(row, 4, checkboxWidget);

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

#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QLineEdit>

void User_Rent_car::on_rent_car_clicked()
{
    QString userName = ui->name_edit->text().trimmed();
    if (userName.isEmpty())
    {
        QMessageBox::warning(this, "Input Error", "Enter your name.");
        return;
    }

    QList<int> checkedRows;
    QList<QList<QString>> selectedCarData;
    for (int row = 0; row < ui->table->rowCount(); ++row)
    {
        QWidget* widget = ui->table->cellWidget(row, 4);
        if (widget)
        {
            QCheckBox* checkbox = widget->findChild<QCheckBox*>();
            if (checkbox && checkbox->isChecked())
            {
                QList<QString> carData = {
                    ui->table->item(row, 0)->text(),
                    ui->table->item(row, 1)->text(),
                    ui->table->item(row, 2)->text(),
                    ui->table->item(row, 3)->text()
                };
                selectedCarData.append(carData);
                checkedRows.append(row);
            }
        }
    }

    if (checkedRows.isEmpty())
    {
        QMessageBox::warning(this, "Selection Error", "Select the car you want to rent.");
        return;
    }

    ui->table->clearContents();
    ui->table->setRowCount(0);

    QStringList newHeaders = {"Name", "Company", "Model", "Price", "Days"};
    ui->table->setHorizontalHeaderLabels(newHeaders);

    int row = 0;
    for (const auto& carData : selectedCarData)
    {
        ui->table->insertRow(row);
        for (int col = 0; col < 4; ++col)
        {
            ui->table->setItem(row, col, new QTableWidgetItem(carData[col]));
            ui->table->item(row, col)->setTextAlignment(Qt::AlignCenter);
        }

        QLineEdit* daysEdit = new QLineEdit();
        daysEdit->setStyleSheet(
            "QLineEdit {"
            "    background-color: rgba(0, 0, 0, 0.5);" // Semi-transparent black
            "    color: #FFFFFF;"                        // White text
            "    border: 2px solid black;"               // Thin black border
            "    border-radius: 10px;"                   // Rounded corners
            "    padding: 5px 10px;"                     // Spacing inside the input field
            "    font-size: 20px;"
            "    font-weight: bold;"
            "}"

            "QLineEdit:hover {"
            "    background-color: rgba(46, 46, 46, 0.5);" // Slightly lighter semi-transparent black
            "    color: #E0E0E0;"                          // Slightly lighter text on hover
            "    border: 2px solid #444444;"               // Slightly lighter border on hover
            "}"

            "QLineEdit:focus {"
            "    background-color: rgba(0, 0, 0, 0.5);"    // Keep semi-transparent black on focus
            "    color: #FFFFFF;"                          // Keep text white
            "    font-size: 16px;"                         // Keep the font size on focus
            "    border: 2px solid #888888;"               // Slightly lighter border on focus
            "}"
            );
        daysEdit->setPlaceholderText("Enter days");
        ui->table->setCellWidget(row, 4, daysEdit);

        ++row;
        ui->rent_car->hide();
        ui->confirm->show();
    }

    QMessageBox::information(this, "Success", "Enter the number of days in the last column.");
}


void User_Rent_car::on_confirm_clicked()
{
    // Get the name from name_edit
    QString userName = ui->name_edit->text().trimmed();

    if (userName.isEmpty())
    {
        QMessageBox::warning(this, "Input Error", "Enter your name.");
        return;
    }

    // Create or open a file named after the user
    QFile file(userName + ".txt");
    QIODevice::OpenMode mode = QIODevice::WriteOnly | QIODevice::Text;

    // Check if the file already exists
    if (file.exists())
    {
        mode = QIODevice::Append | QIODevice::Text; // Set to append mode
    }

    if (!file.open(mode))
    {
        QMessageBox::warning(this, "File Error", "Could not create or open the file.");
        return;
    }

    QTextStream out(&file);

    // Extract data from the table and write it to the file
    for (int row = 0; row < ui->table->rowCount(); ++row)
    {
        QString name = ui->table->item(row, 0)->text();
        QString company = ui->table->item(row, 1)->text();
        QString model = ui->table->item(row, 2)->text();
        QString price = ui->table->item(row, 3)->text();

        // Get the text from the line edit in the "Days" column
        QWidget* widget = ui->table->cellWidget(row, 4);
        QLineEdit* daysEdit = qobject_cast<QLineEdit*>(widget);
        QString days = daysEdit ? daysEdit->text().trimmed() : "";

        if (days.isEmpty())
        {
            QMessageBox::warning(this, "Input Error", "Please enter the number of days for all cars.");
            file.close();
            return;
        }

        // Write the car data to the file
        out << "Name: " << name << "\n";
        out << "Company: " << company << "\n";
        out << "Model: " << model << "\n";
        out << "Price: " << price << "\n";
        out << "Days: " << days << "\n";
        out << "----------\n";
    }

    file.close();
    updateCarsData();
    QMessageBox::information(this, "Success", "Car data has been saved successfully.");
}


void User_Rent_car::updateCarsData()
{
    QFile carsFile("Cars_data.txt");
    if (!carsFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "File Error", "Could not open Cars_data file.");
        return;
    }

    QFile tempFile("Temp_Cars_data.txt");
    if (!tempFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "File Error", "Could not create temporary file.");
        return;
    }

    QTextStream in(&carsFile);
    QTextStream out(&tempFile);

    QString name, company, model, price, availability;
    bool isRecord = false;

    while (!in.atEnd())
    {
        QString line = in.readLine();

        if (line.startsWith("Name: "))
        {
            name = line.section(": ", 1).trimmed();
            isRecord = true;
        }
        else if (line.startsWith("Company: "))
        {
            company = line.section(": ", 1).trimmed();
        }
        else if (line.startsWith("Model: "))
        {
            model = line.section(": ", 1).trimmed();
        }
        else if (line.startsWith("Price: "))
        {
            price = line.section(": ", 1).trimmed();
        }
        else if (line.startsWith("Availability: "))
        {
            availability = line.section(": ", 1).trimmed();
        }
        else if (line == "----------" && isRecord)
        {
            // Check if this car matches any car in the table
            bool carRented = false;
            for (int row = 0; row < ui->table->rowCount(); ++row)
            {
                QString tableName = ui->table->item(row, 0)->text();
                QString tableCompany = ui->table->item(row, 1)->text();
                QString tableModel = ui->table->item(row, 2)->text();
                QString tablePrice = ui->table->item(row, 3)->text();

                if (name == tableName && company == tableCompany && model == tableModel && price == tablePrice)
                {
                    availability = "No"; // Set availability to "No" if rented
                    carRented = true;
                    break;
                }
            }

            // Write this record back to the temp file
            out << "Name: " << name << "\n";
            out << "Company: " << company << "\n";
            out << "Model: " << model << "\n";
            out << "Price: " << price << "\n";
            out << "Availability: " << availability << "\n";
            out << "----------\n";

            isRecord = false; // Reset the record flag
        }
    }

    carsFile.close();
    tempFile.close();

    // Replace the original file with the updated file
    carsFile.remove();
    tempFile.rename("Cars_data.txt");
}

