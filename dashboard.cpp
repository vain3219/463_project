#include "dashboard.h"
#include "ui_dashboard.h"
#include "loginauth.h"

DashBoard::DashBoard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DashBoard)
{
    // Nothing before this line
    ui->setupUi(this);
    // Change the window title
    this->setWindowTitle("User Dashboard");
    // Hide database fail text
    ui->DatabaseLoadError->hide();
    // QPalette is used to change the color of the text in FailedAuth label to RED
    QPalette palette = ui->DatabaseLoadError->palette();
    palette.setColor(ui->DatabaseLoadError->backgroundRole(), Qt::red);
    palette.setColor(ui->DatabaseLoadError->foregroundRole(), Qt::red);
    ui->DatabaseLoadError->setPalette(palette);
    //

    // Attempt to populate the DataTable
    //  If the DataTable can't be populated, display error text
//    if( !PopulateDataTable() ) {
//        ui->DataTable->hide();
//        ui->DatabaseLoadError->show();
//    }
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

bool DashBoard::PopulateDataTable() {
    return false;
}


void DashBoard::on_SearchButton_clicked()
{
    // This function is activated when the SearchButton is pressed & released
}
