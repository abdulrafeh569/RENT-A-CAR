#include "admin_login.h"
#include "ui_admin_login.h"
#include <QMessageBox>

Admin_Login::Admin_Login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Admin_Login)
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

Admin_Login::~Admin_Login()
{
    delete ui;
}

void Admin_Login::on_login_clicked()
{
    const QString adminUsername = "ADMIN";
    const QString adminPassword = "BAHRIA@123";

    QString enteredUsername = ui->user_edit->text();
    QString enteredPassword = ui->pass_edit->text();

    if (enteredUsername == adminUsername && enteredPassword == adminPassword)
    {
        showStyledMessageBox(QMessageBox::Information, "Success", "Admin login successful!");
        ui->pass_edit->clear();
        ui->user_edit->clear();
        admin_menu = new Admin_Menu(this);
        admin_menu->show();

    } else
    {
        showStyledMessageBox(QMessageBox::Warning, "Error", "Invalid username or password.");
        ui->pass_edit->clear();
        ui->user_edit->clear();
        return;
    }
}

void Admin_Login::showStyledMessageBox(QMessageBox::Icon icon, const QString &title, const QString &message)
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
