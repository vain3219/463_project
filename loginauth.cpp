#include "loginauth.h"
#include "ui_loginauth.h"

LoginAuth::LoginAuth(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginAuth),
    loadMeDaddy(new DashBoard)
{
    // Nothing before this line
    ui->setupUi(this);
    ui->FailedAuth->hide();
    //

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

void LoginAuth::on_LoginButton_clicked(QAbstractButton *button)
{
    /*
     * This function is responsible for authenticating the presented Username and Password.
     * This is a "Clicked" event -- The event will be generated on mouse press & release.
     * After succesful authentication, this function shall call on the dashboard.ui to present the
     * User with their dashboard.
     */

    QString username = ui->UsernameField->text();
    QString password = ui->PasswordField->text();
    /*
     *  sql.query(username.password)
     *  password == username.password ?
     *      loadDashboard() ;
     *    else
     *      clear fields && present login failed message
     */

    /*
     *  Hard coded values for easy development logins
     *  Developmental login info : Username "dev" & Password "dev"
     *  For developmental logins only
     *  Remove for release
     */

    if(username == "dev" && password == "dev") {
        // Load dashboard

        ui->PasswordField->clear();
        ui->UsernameField->clear();
        loadMeDaddy->show();
        ui->~LoginAuth();
    } else {
        ui->PasswordField->clear();
        ui->UsernameField->clear();
        ui->FailedAuth->show();
    }
}
