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
    // Create new login form object, show the new window, and close the dashboard window
    LoginAuth *LoginLoader = new LoginAuth;
    LoginLoader->show();
    this->close();
}

void DashBoard::on_SearchButton_clicked()
{
    // Set the stacked widget to display the additional search GUI
    ui->stackedWidget->setCurrentWidget(ui->SearchPage);  
}

void DashBoard::on_DailyButton_clicked()
{
    // Hide unecessary GUI elements
    setBlankPage();
}

void DashBoard::on_GuestsButton_clicked()
{
    // Hide unecessary GUI elements
    setBlankPage();
}

void DashBoard::on_HousekeepingButton_clicked()
{
    // Hide unecessary GUI elements
    setBlankPage();
}

void DashBoard::on_InfoButton_clicked()
{
    // Hide unecessary GUI elements
    setBlankPage();
}

void DashBoard::on_ReservationButton_clicked()
{
    // Set the stacked widget to display the additional reservation GUI
    ui->stackedWidget->setCurrentWidget(ui->ReservationPage);
}

void DashBoard::on_RoomsButton_clicked()
{
    // Hide unecessary GUI elements
    setBlankPage();
}

void DashBoard::on_WeeklyButton_clicked()
{
    // Hide unecessary GUI elements
    setBlankPage();
}

void DashBoard::on_SubmitButon_clicked()
{
    // Execute SQL search query here
}

void DashBoard::on_MakeResButton_clicked()
{
   // Create new form object and display the window
   Reservations* loadMe = new Reservations;
   loadMe->show();
}

bool DashBoard::PopulateDataTable(DbManager db)
{
    // Populates the data table with the given query
    // Returns false if query fails
    return db.isOpen();
}

void DashBoard::setBlankPage() {
    // Sets the stacked widget to display the blankPage when additional GUI
    //  elements are unecessary
    if(ui->stackedWidget->currentIndex() != 0) {
            ui->stackedWidget->setCurrentWidget(ui->BlankPage);
    }
}

