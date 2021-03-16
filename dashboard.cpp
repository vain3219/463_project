#include "dashboard.h"
#include "ui_dashboard.h"
#include "loginauth.h"

DashBoard::DashBoard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DashBoard)
{
    ui->setupUi(this);
}

DashBoard::~DashBoard()
{
    delete ui;
}


void DashBoard::on_LogoutButton_clicked()
{
    LoginAuth *LoginLoader = new LoginAuth;
    LoginLoader->show();
    this->close();
}
