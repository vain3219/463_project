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

    // Establish connection with SQLite Database
    DbManager db("Antares Management Database.db");

    // Attempt to populate the DataTable
    //  If the DataTable can't be populated, display error text
    if( !PopulateDataTable(db) ) {
        ui->DataTable->hide();
        ui->DatabaseLoadError->show();
    }
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

void DashBoard::on_SearchButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->SearchPage);
}

void DashBoard::on_DailyButton_clicked()
{
    setDisplayPage();
}

void DashBoard::on_GuestsButton_clicked()
{
    setDisplayPage();
}

void DashBoard::on_HousekeepingButton_clicked()
{
    setDisplayPage();
}

void DashBoard::on_InfoButton_clicked()
{
    setDisplayPage();
}

void DashBoard::on_ReservationButton_clicked()
{
    setDisplayPage();
}

void DashBoard::on_RoomsButton_clicked()
{
    setDisplayPage();
}

void DashBoard::on_WeeklyButton_clicked()
{
    setDisplayPage();
}

void DashBoard::on_SubmitButon_clicked()
{
    setDisplayPage();
}

bool DashBoard::PopulateDataTable(DbManager db)
{
    return db.isOpen();
}

void DashBoard::setDisplayPage() {
    if(ui->stackedWidget->currentIndex() == 1) {
            ui->stackedWidget->setCurrentWidget(ui->DisplayPage);
    }
}
