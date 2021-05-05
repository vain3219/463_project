#include "reservations.h"
#include "ui_reservations.h"

Reservations::Reservations(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Reservations)
{
    // Nothing before this line
    ui->setupUi(this);
    // Change the window title
    this->setWindowTitle("Hotel Antares Reservation");
}

Reservations::Reservations(QSqlDatabase* db, int roomNumber) :
    ui(new Ui::Reservations)
{
    // Nothing before this line
    ui->setupUi(this);
    // Change the window title
    dbRef= db;
    curRoom = roomNumber;
    this->setWindowTitle("Hotel Antares Reservation");
    ref = *db;
}

Reservations::~Reservations()
{
    delete ui;
}

void Reservations::on_ConfirmButton_clicked()
{
    // Do text extraction from input fields here
     QString FName = "\"" + ui->FNameField->text() + "\"";
     QString LName = "\"" + ui->LNameField->text() + "\"";
     QString CheckIn = "\"" + ui->CheckInField->text() + "\"";
     QString Checkout = "\"" + ui->CheckoutField->text() + "\"";
     QString Phone = "\"" + ui->PhoneField->text() + "\"";
     QString Address = "\"" + ui->AddressField->text() + "\"";
     QString Email = "\"" + ui->EmailField->text() + "\"";
     QString IDNum = "\"" + ui->IDNumField->text() + "\"";
     QString IDState = "\"" + ui->IDStateField->text() + "\"";
     QString LicensePlate = "\"" + ui->LicensePlateField->text() + "\"";

    // Create query String
    QString insertQuery = "INSERT INTO Customer (FName, LName, IDNum, IDState, LicensePlate, Address, Phone, Email) values (" + FName + "," + LName + "," + IDNum + "," + IDState + "," + LicensePlate + "," + Address + "," + Phone + "," + Email + ")";
    // Execute Query
    QSqlQuery* qry = new QSqlQuery(ref);
    if( qry->prepare(insertQuery))
    {
       qry->exec();
       qry->first();
       qDebug() << " successfully returned.";
    } else {
       QSqlError error = qry->lastError();
       qDebug() << "Failed to prepare query.";
       qDebug() << "Database says: " + error.databaseText();
    }

    insertQuery = "INSERT INTO Reservations (DateMade, CheckIn, Checkout) values (\"" + QDate::currentDate().toString() + "\"," + CheckIn + "," + Checkout + ")";
    // Execute Query
    qry = new QSqlQuery(ref);
    if( qry->prepare(insertQuery))
    {
       qry->exec();
       qry->first();
       qDebug() << " successfully returned.";
    } else {
       QSqlError error = qry->lastError();
       qDebug() << "Failed to prepare query.";
       qDebug() << "Database says: " + error.databaseText();
    }
    // Close the window after successful query
    this->close();
}

void Reservations::on_CancelButton_clicked()
{
    // Close window and return to dashboard
    this->close();
}
