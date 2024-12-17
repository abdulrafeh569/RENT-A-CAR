#include "user_choice.h"
#include "ui_user_choice.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

User_Choice::User_Choice(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::User_Choice)
{
    setWindowFlags(Qt::Window);
    ui->setupUi(this);

    ui->register_2->setStyleSheet(
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
    ui->login->setStyleSheet(
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

    ui->username->setStyleSheet(
        "QLabel {"
        "    background-color: rgba(0, 0, 0, 0.7);"
        "    color: #FFFFFF;"            // White text
        "    border: 2px solid black;"   // Thin black border
        "    border-radius: 10px;"       // Rounded corners
        "    padding: 5px 10px;"         // Spacing inside the label
        "}"
        );

    ui->password->setStyleSheet(
        "QLabel {"
        "    background-color: rgba(0, 0, 0, 0.7);"
        "    color: #FFFFFF;"            // White text
        "    border: 2px solid black;"   // Thin black border
        "    border-radius: 10px;"       // Rounded corners
        "    padding: 5px 10px;"         // Spacing inside the label
        "}"
        );

    // Apply stylesheet to QLineEdit objects
    ui->user_edit->setStyleSheet(
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

    ui->pass_edit->setStyleSheet(
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

}

User_Choice::~User_Choice()
{
    delete ui;
}

void User_Choice::on_register_2_clicked()
{
    QString username = ui->user_edit->text();
    QString password = ui->pass_edit->text();

    if (username.isEmpty() || password.isEmpty())
    {
        showStyledMessageBox(QMessageBox::Warning, "Error", "Username or password cannot be empty.");
        return;

    }

    QFile file("user_credentials.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text))
    {
        showStyledMessageBox(QMessageBox::Critical, "Error", "Failed to open the file for writing.");
        ui->user_edit->clear();
        ui->pass_edit->clear();
        return;
    }

    QTextStream out(&file);
    out << "Username: " << username << "\n";
    out << "Password: " << password << "\n";
    out << "----------\n";
    file.close();

    ui->user_edit->clear();
    ui->pass_edit->clear();

    showStyledMessageBox(QMessageBox::Information, "Success", "User registered successfully.");
}


void User_Choice::on_login_clicked()
{
    QString enteredUsername = ui->user_edit->text();
    QString enteredPassword = ui->pass_edit->text();

    if (enteredUsername.isEmpty() || enteredPassword.isEmpty())
    {
        showStyledMessageBox(QMessageBox::Warning, "Error", "Username or password cannot be empty.");
        return;

    }

    QFile file("user_credentials.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        showStyledMessageBox(QMessageBox::Critical, "Error", "Failed to open the file for reading.");
        return;

    }

    QTextStream in(&file);
    bool loginSuccessful = false;
    while (!in.atEnd())
    {
        QString line = in.readLine();

        if (line.startsWith("Username: "))
        {
            QString savedUsername = line.mid(QString("Username: ").length()).trimmed();
            QString savedPassword = in.readLine().mid(QString("Password: ").length()).trimmed();

            if (enteredUsername == savedUsername && enteredPassword == savedPassword)
            {
                loginSuccessful = true;
                break;
            }
        }
    }
    file.close();

    if (loginSuccessful)
    {
        showStyledMessageBox(QMessageBox::Information, "Success", "Login successful!");
        ui->user_edit->clear();
        ui->pass_edit->clear();

        user_menu = new User_Menu(this);
        user_menu->show();
    }
    else
    {
        showStyledMessageBox(QMessageBox::Warning, "Error", "Invalid username or password.");
        ui->user_edit->clear();
        ui->pass_edit->clear();
        return;
    }
}


void User_Choice::showStyledMessageBox(QMessageBox::Icon icon, const QString &title, const QString &message)
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
