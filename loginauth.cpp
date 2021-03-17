#include "loginauth.h"
#include "ui_loginauth.h"
#include "dashboard.h"

LoginAuth::LoginAuth(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginAuth)
{
    // Nothing before this line
    ui->setupUi(this);
    // Change the window title
    this->setWindowTitle("Login Authentication");
    // Hide the failed Authentication text until at least one attempt has been made
    ui->FailedAuth->hide();

    // QPalette is used to change the color of the text in FailedAuth label to RED
    QPalette palette = ui->FailedAuth->palette();
    palette.setColor(ui->FailedAuth->backgroundRole(), Qt::red);
    palette.setColor(ui->FailedAuth->foregroundRole(), Qt::red);
    ui->FailedAuth->setPalette(palette);
    //
}

LoginAuth::~LoginAuth()
{
    delete ui;
}

void LoginAuth::on_LoginButton_clicked()
{
    /*
     * This function is responsible for authenticating the presented Username and Password.
     * This is a "Clicked" event -- The event will be generated on mouse press & release.
     * After succesful authentication, this function shall call on the dashboard.ui to present the
     * User with their dashboard.
     */

    // Extract input text and clear the text fields
    QString username = ui->UsernameField->text();
    QString password = ui->PasswordField->text();
    ui->PasswordField->clear();
    ui->UsernameField->clear();

    /*
     *  Hard coded values for easy development logins
     *  Developmental login info : Username "dev" & Password "dev"
     *  For developmental logins only
     *  Remove for release
     *  Do we want a database for username/password??
     */

    if(username == "dev" && password == "dev") {
        // Create QWidget for the DashBoard window
        DashBoard *loadMeDaddy = new DashBoard;
        // Load dashboard and hide login window
        loadMeDaddy->show();
        // Close this window ;; If this is the only window, the program will terminate
        this->close();
    } else {
        // Show Failed Authentication text
        ui->FailedAuth->show();
    }
}

void LoginAuth::on_ExitButton_clicked()
{
    this->close();
}
