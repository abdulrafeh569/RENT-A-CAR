#include "admin_remove_car.h"
#include "ui_admin_remove_car.h"
#include <QFile>
#include <QDataStream>
#include <QMessageBox>

Admin_Remove_car::Admin_Remove_car(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Admin_Remove_car)
{
    setWindowFlags(Qt::Window);
    ui->setupUi(this);
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

Admin_Remove_car::~Admin_Remove_car()
{
    delete ui;
}



void Admin_Remove_car::on_remove_car_clicked()
{
    // Retrieve the car name from the line edit
    QString carName = ui->name_edit->text();

    // Check if the input field is empty
    if (carName.isEmpty())
    {
        QMessageBox::warning(this, "Error", "Enter the name to remove the car.");
        return;
    }

    QFile file("Cars_data.txt");
    QFile tempFile("Cars_data_temp.txt");

    // Open the original file for reading and a temporary file for writing
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Error", "Failed to open the file for reading.");
        return;
    }

    if (!tempFile.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::critical(this, "Error", "Failed to create a temporary file for writing.");
        file.close();
        return;
    }

    QTextStream in(&file);
    QTextStream out(&tempFile);
    bool carFound = false;

    // Iterate through the lines of the file
    while (!in.atEnd())
    {
        QString line = in.readLine();

        // Check if the current line contains the car name
        if (line == QString("Name: ") + carName)
        {
            carFound = true;

            // Skip the next 5 lines (including the separator line)
            for (int i = 0; i < 5 && !in.atEnd(); ++i)
            {
                in.readLine();
            }
        }
        else
        {
            // Write the line to the temporary file
            out << line << "\n";
        }
    }

    // Close both files
    file.close();
    tempFile.close();

    // If the car was found, replace the original file with the temporary file
    if (carFound)
    {
        file.remove();
        tempFile.rename("Cars_data.txt");
        QMessageBox::information(this, "Success", "Car data has been removed successfully.");
    }
    else
    {
        tempFile.remove();
        QMessageBox::warning(this, "Error", "Car not found in the file.");
    }

    // Clear the input field
    ui->name_edit->clear();
}

