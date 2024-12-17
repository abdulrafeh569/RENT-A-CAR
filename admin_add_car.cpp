#include "admin_add_car.h"
#include "ui_admin_add_car.h"
#include <QMessageBox>
#include <QFile>
Admin_add_car::Admin_add_car(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Admin_add_car)
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

Admin_add_car::~Admin_add_car()
{
    delete ui;
}

void Admin_add_car::on_login_clicked()
{

    QString company = ui->company_edit->text();
    QString name = ui->name_edit->text();
    QString model = ui->model_edit->text();
    QString price = ui->price_edit->text();

    if (company.isEmpty() || name.isEmpty() || model.isEmpty() || price.isEmpty())
    {
        showStyledMessageBox(QMessageBox::Warning, "Error", "All fields should be filled.");
        return;
    }

    QFile file("Cars_data.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        showStyledMessageBox(QMessageBox::Critical, "Error", "Failed to open the file for writing.");
        return;
    }

    QTextStream out(&file);
    out << "Name: " << name << "\n";
    out << "Company: " << company << "\n";
    out << "Model: " << model << "\n";
    out << "Price: " << price << "\n";
    out << "Availability: Yes\n";
    out << "----------\n";

    file.close();

    ui->company_edit->clear();
    ui->name_edit->clear();
    ui->model_edit->clear();
    ui->price_edit->clear();

    showStyledMessageBox(QMessageBox::Information, "Success", "Car data has been saved successfully.");
}

void Admin_add_car::showStyledMessageBox(QMessageBox::Icon icon, const QString &title, const QString &message)
{
    QMessageBox messageBox(this);
    messageBox.setIcon(icon);
    messageBox.setWindowTitle(title);
    messageBox.setText(message);

    messageBox.setStyleSheet(
        "QMessageBox {"
        "    background-color: rgba(0, 0, 0, 0.7);" // Semi-transparent black background
        "    border: 2px solid black;"               // Thin black border
        "    border-radius: 10px;"                   // Rounded corners
        "    padding: 10px;"                         // Padding inside the message box
        "}"
        "QLabel {"
        "    color: #FFFFFF;"                        // White text for labels (message content)
        "    font-size: 13px;"                       // Larger font size for message content
        "}"
        "QPushButton {"
        "    background-color: rgba(46, 46, 46, 0.9);" // Button background
        "    color: #FFFFFF;"                          // Button text color
        "    border: 1px solid #444444;"               // Button border
        "    border-radius: 5px;"                      // Rounded button corners
        "    padding: 5px 10px;"                       // Button padding
        "}"
        );
    messageBox.exec();
}
