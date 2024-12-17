#include "user_return_car.h"
#include "ui_user_return_car.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QCheckBox>
#include <QTableWidgetItem>
#include <QHBoxLayout>
User_Return_car::User_Return_car(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::User_Return_car)
{
    setWindowFlags(Qt::Window);
    ui->setupUi(this);
    ui->table->hide();
    ui->returnn->hide();
    ui->frame->hide();
    ui->thanks->hide();
    ui->thankss->hide();
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

}

User_Return_car::~User_Return_car()
{
    delete ui;
}


void User_Return_car::on_returnn_clicked()
{
    updateCarsData();
    removeCheckedCars();
    generateReceipt();
}


void User_Return_car::updateCarsData()
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

    QSet<QString> checkedCars;
    for (int row = 0; row < ui->table->rowCount(); ++row)
    {
        QWidget* widget = ui->table->cellWidget(row, 5);
        QCheckBox* checkbox = widget ? widget->findChild<QCheckBox*>() : nullptr;

        if (checkbox)
        {
            if (checkbox->isChecked())
            {
                QTableWidgetItem* nameItem = ui->table->item(row, 0);
                if (nameItem)
                {
                    QString carName = nameItem->text().trimmed();
                    if (!carName.isEmpty())
                    {
                        checkedCars.insert(carName);
                    }
                }
            }
        }
    }

    QString name, company, model, price, availability;

    while (!in.atEnd())
    {
        QString line = in.readLine();

        if (line.startsWith("Name: "))
        {
            name = line.section(": ", 1).trimmed();
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

        if (line == "----------")
        {
            if (checkedCars.contains(name))
            {
                availability = "Yes";
            }

            // Write the car data to the temp file
            out << "Name: " << name << "\n";
            out << "Company: " << company << "\n";
            out << "Model: " << model << "\n";
            out << "Price: " << price << "\n";
            out << "Availability: " << availability << "\n";
            out << "----------\n";

            name.clear();
            company.clear();
            model.clear();
            price.clear();
            availability.clear();
        }
    }


    carsFile.close();
    tempFile.close();

    carsFile.remove();
    tempFile.rename("Cars_data.txt");

    QMessageBox::information(this, "Success", "Car availability has been updated successfully.");
}

void User_Return_car::removeCheckedCars()
{
    QString customerFileName = ui->name_edit->text().trimmed() + ".txt";
    QFile customerFile(customerFileName);

    if (!customerFile.exists())
    {
        QMessageBox::warning(this, "File Error", "No file found for the entered name.");
        return;
    }

    if (!customerFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "File Error", "Could not open the file.");
        return;
    }

    QFile tempFile("Temp_" + customerFileName);
    if (!tempFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "File Error", "Could not create a temporary file.");
        return;
    }

    QTextStream in(&customerFile);
    QTextStream out(&tempFile);

    QString name, company, model, price, days;
    bool dataRemaining = false;

    while (!in.atEnd())
    {
        QString line = in.readLine();

        if (line.startsWith("Name: "))
            name = line.section(": ", 1).trimmed();
        else if (line.startsWith("Company: "))
            company = line.section(": ", 1).trimmed();
        else if (line.startsWith("Model: "))
            model = line.section(": ", 1).trimmed();
        else if (line.startsWith("Price: "))
            price = line.section(": ", 1).trimmed();
        else if (line.startsWith("Days: "))
            days = line.section(": ", 1).trimmed();

        if (line == "----------")
        {
            bool carChecked = false;

            for (int row = 0; row < ui->table->rowCount(); ++row)
            {
                QWidget *widget = ui->table->cellWidget(row, 5);
                QCheckBox *checkbox = widget ? widget->findChild<QCheckBox *>() : nullptr;

                if (checkbox && checkbox->isChecked())
                {
                    QString tableName = ui->table->item(row, 0)->text();
                    QString tableCompany = ui->table->item(row, 1)->text();
                    QString tableModel = ui->table->item(row, 2)->text();
                    QString tablePrice = ui->table->item(row, 3)->text();

                    if (name == tableName && company == tableCompany && model == tableModel && price == tablePrice)
                    {
                        carChecked = true;
                        break;
                    }
                }
            }

            if (!carChecked)
            {
                out << "Name: " << name << "\n";
                out << "Company: " << company << "\n";
                out << "Model: " << model << "\n";
                out << "Price: " << price << "\n";
                out << "Days: " << days << "\n";
                out << "----------\n";
                dataRemaining = true;
            }
        }
    }

    customerFile.close();
    tempFile.close();

    if (dataRemaining)
    {
        customerFile.remove();
        tempFile.rename(customerFileName);
    }
    else
    {
        customerFile.remove();
        tempFile.remove();
        QMessageBox::information(this, "File Deleted", "All car records for this customer have been returned. File deleted.");
    }
}

void User_Return_car::generateReceipt()
{
    ui->name_edit->hide();
    ui->returnn->hide();
    ui->table->hide();
    ui->name->hide();

    ui->frame->show();
    ui->frame->setStyleSheet(
        "QFrame {"
        "    background-color: rgba(0, 0, 0, 0.4);"
        "    color: #FFFFFF;"
        "    border: 2px solid black;"
        "    border-radius: 10px;"
        "    padding: 5px;"
        "}"
        "QLabel {"
        "    background-color: rgba(0, 0, 0, 0.7);"
        "    color: #FFFFFF;"
        "    border: 2px solid black;"
        "    border-radius: 10px;"
        "    padding: 5px 10px;"
        "}"
        );

    QString customerName = ui->name_edit->text().trimmed();
    ui->receipt_name->setText(" Dear " + customerName);

    // Initialize variables for car data
    QString car1Name, car2Name, car1Price, car2Price;
    int carCount = 0;
    double totalPrice = 0.0;

    // Loop through table rows to find checked cars
    for (int row = 0; row < ui->table->rowCount(); ++row)
    {
        QWidget *widget = ui->table->cellWidget(row, 5);
        QCheckBox *checkbox = widget ? widget->findChild<QCheckBox *>() : nullptr;

        if (checkbox && checkbox->isChecked())
        {
            QString carName = ui->table->item(row, 0)->text(); // Name of the car

            // Remove the $ sign from the price and convert to double
            QString priceText = ui->table->item(row, 3)->text();
            priceText.remove('$');
            double carPricePerDay = priceText.toDouble();

            int carDays = ui->table->item(row, 4)->text().toInt();
            double carTotalPrice = carPricePerDay * carDays;

            // Assign to car1 or car2 based on count
            if (carCount == 0)
            {
                car1Name = carName;
                car1Price = QString::number(carTotalPrice, 'f', 2);
                totalPrice += carTotalPrice;
                carCount++;
            }
            else if (carCount == 1)
            {
                car2Name = carName;
                car2Price = QString::number(carTotalPrice, 'f', 2);
                totalPrice += carTotalPrice;
                carCount++;
                break; // Only two cars allowed
            }
        }
    }

    // Update the receipt labels
    ui->Car1->setText(car1Name);
    ui->Price1->setText("Price: $" + car1Price);
    ui->Car1->show();
    ui->Price1->show();

    if (carCount > 1)
    {
        ui->Car2->setText(car2Name);
        ui->Price2->setText("Price: $" + car2Price);
        ui->Car2->show();
        ui->Price2->show();
    }
    else
    {
        ui->Car2->hide();
        ui->Price2->hide();
    }

    // Update the total price label
    ui->total_price->setText("Total Price: $" + QString::number(totalPrice, 'f', 2));

    ui->thanks->show();
    ui->thankss->show();
}

void User_Return_car::on_name_edit_editingFinished()
{
    ui->returnn->show();
    QString arg1=ui->name_edit->text();
    if (arg1.trimmed().isEmpty())
    {
        QMessageBox::warning(this, "Input Error", "Please enter a name.");
        return;
    }

    QString fileName = arg1 + ".txt";
    QFile file(fileName);

    if (!file.exists())
    {
        QMessageBox::information(this, "No Records", "No cars rented by this name.");
        return;
    }

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Error", "Unable to open the file.");
        return;
    }

    QTextStream in(&file);
    ui->table->show();
    ui->table->setRowCount(0);


    ui->table->setColumnCount(6);
    ui->table->setHorizontalHeaderLabels({"Name", "Company", "Model", "Price", "Days", "Select"});
    ui->table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    QString name, company, model, price, days;
    int row = 0;

    while (!in.atEnd())
    {
        QString line = in.readLine();


        if (line.startsWith("Name: "))
        {
            name = line.mid(6).trimmed();
        }
        else if (line.startsWith("Company: "))
        {
            company = line.mid(9).trimmed();
        }
        else if (line.startsWith("Model: "))
        {
            model = line.mid(7).trimmed();
        }
        else if (line.startsWith("Price: "))
        {
            price = line.mid(7).trimmed();
        }
        else if (line.startsWith("Days: "))
        {
            days = line.mid(6).trimmed();
        }
        else if (line.startsWith("----------"))
        {
            ui->table->insertRow(row);
            ui->table->setItem(row, 0, new QTableWidgetItem(name));
            ui->table->setItem(row, 1, new QTableWidgetItem(company));
            ui->table->setItem(row, 2, new QTableWidgetItem(model));
            ui->table->setItem(row, 3, new QTableWidgetItem(price));
            ui->table->setItem(row, 4, new QTableWidgetItem(days));

            QCheckBox *checkbox = new QCheckBox(this);
            QWidget *widget = new QWidget(this);
            QHBoxLayout *layout = new QHBoxLayout(widget);
            layout->addWidget(checkbox);
            layout->setAlignment(Qt::AlignCenter);
            layout->setContentsMargins(0, 0, 0, 0);
            widget->setLayout(layout);
            ui->table->setCellWidget(row, 5, widget);
            row++;
        }
    }

    ui->table->verticalHeader()->setVisible(false);
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

    file.close();

    if (row == 0)
    {
        QMessageBox::information(this, "No Records", "No cars found for this name.");
    }
}

