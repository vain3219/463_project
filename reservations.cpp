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

Reservations::Reservations(QSqlDatabase* db) :
    ui(new Ui::Reservations)
{
    // Nothing before this line
    ui->setupUi(this);
    // Change the window title
    this->setWindowTitle("Hotel Antares Reservation");
    ref = *db;
    curRoom = -1;

    ui->RoomMenu->setMaxCount(4);
    ui->RoomMenu->insertItem(0, "Suite................................$75.99");
    ui->RoomMenu->insertItem(1, "Double Queen.....................$119.99");
    ui->RoomMenu->insertItem(2, "Double Queen with Kitchen......$149.99");
    ui->RoomMenu->insertItem(3, "King.................................$249.99");
}

Reservations::Reservations(QSqlDatabase* db, int roomNumber) :
    ui(new Ui::Reservations)
{
    // Nothing before this line
    ui->setupUi(this);
    // Change the window title
    curRoom = roomNumber;
    this->setWindowTitle("Hotel Antares Reservation");
    ref = *db;

    ui->RoomMenu->setMaxCount(4);
    ui->RoomMenu->insertItem(0, "Suite................................$75.99");
    ui->RoomMenu->insertItem(1, "Double Queen.....................$119.99");
    ui->RoomMenu->insertItem(2, "Double Queen with Kitchen......$149.99");
    ui->RoomMenu->insertItem(3, "King.................................$249.99");
}

Reservations::Reservations(QSqlDatabase* db, QString date) :
    ui(new Ui::Reservations)
{
    // Nothing before this line
    ui->setupUi(this);
    // Change the window title
    this->setWindowTitle("Hotel Antares Reservation");
    ref = *db;
    curRoom = -1;

    ui->RoomMenu->setMaxCount(4);
    ui->RoomMenu->insertItem(0, "Suite................................$75.99");
    ui->RoomMenu->insertItem(1, "Double Queen.....................$119.99");
    ui->RoomMenu->insertItem(2, "Double Queen with Kitchen......$149.99");
    ui->RoomMenu->insertItem(3, "King.................................$249.99");

    ui->CheckInField->setText(date);
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
    int roomType = ui->RoomMenu->currentIndex();
    QSqlQuery* qry = new QSqlQuery(ref);
    QString insertQuery;
    int CusID = 0;
    QSqlError error;
    QString IDNum1 = ui->IDNumField->text();

    insertQuery = "select CusID from Customer where( IDNum = '" + IDNum1 + "')";
    if(qry->prepare(insertQuery))
    {
        qry->exec();
        qry->first();
        CusID = qry->value(0).toInt();
        // Customer is not in the databse -- add them
        qDebug() << QString::number(qry->numRowsAffected()) + " Customer records found with IDNum " + IDNum1 + " CusID = "+ QString::number(CusID);
        if(qry->numRowsAffected() == 0)
        {
            // Create query String
            insertQuery = "INSERT INTO Customer (FName, LName, IDNum, IDState, LicensePlate, Address, Phone, Email) values (" + FName + "," + LName + "," + IDNum + "," + IDState + "," + LicensePlate + "," + Address + "," + Phone + "," + Email + ")";

            // Insert into Customer Query
            qry = new QSqlQuery(ref);
            if( qry->prepare(insertQuery))
            {
                qry->exec();
                qDebug() << " successfully returned.";
            } else {
                error = qry->lastError();
                qDebug() << "Failed to prepare query.";
                qDebug() << "Database says: " + error.databaseText();
            }

            insertQuery = "select max(CusID) from Customer";

            // Get last CusID in Customer
            qry = new QSqlQuery(ref);
            if( qry->prepare(insertQuery))
            {
                qry->exec();
                qry->first();
                CusID = qry->value(0).toInt();
                qDebug() << " successfully returned.";
            } else {
                QSqlError error = qry->lastError();
                qDebug() << "Failed to prepare query.";
                qDebug() << "Database says: " + error.databaseText();
            }
        }
        else
            // If the customer exists in the database
        {
            CusID = qry->value(0).toInt();
        }
    } else {
        error = qry->lastError();
        qDebug() << "Failed to prepare query.";
        qDebug() << "Database says: " + error.databaseText();
    }

    int roomNum = FindAvailableRoomOfType(roomType);

    qDebug() << "Designated room number: " + QString::number(roomNum);

    insertQuery = "INSERT INTO Reservations (DateMade, CheckIn, Checkout, RoomType, CusID, RoomID) values (\"" + QDate::currentDate().toString(Qt::ISODate) + "\"," + CheckIn + "," + Checkout + "," + QString::number(roomType) + "," + QString::number(CusID) + "," +  QString::number(roomNum) +")";
    // Execute Query
    qry = new QSqlQuery(ref);
    if( qry->prepare(insertQuery))
    {
        qry->exec();
        qDebug() << " successfully returned.";
    } else {
        error = qry->lastError();
        qDebug() << "Failed to prepare query.";
        qDebug() << "Database says: " + error.databaseText();
    }

    // Add payment using dist(checkout.julianDays - checkIn.julianDays)*roomType(price)
    QDate in= QDate::fromString(ui->CheckInField->text(),Qt::ISODate);
    QDate out= QDate::fromString(ui->CheckoutField->text(), Qt::ISODate);

    int days = out.toJulianDay() - in.toJulianDay();
    qDebug() << "Dates: " + out.toString() + "  " + in.toString();
    qDebug() << QString::number(days) + " = " + QString::number(out.toJulianDay()) +  " - " + QString::number(in.toJulianDay());
    double total = 0.0;

    switch (roomType)
    {
    case 0:
        total = days*75.99;
        break;
    case 1:
        total = days*119.99;
        break;
    case 2:
        total = days*149.99;
        break;
    case 3:
        total = days*249.99;
        break;
    }

    int ResID = 0;
    insertQuery = "select max(ResID) from Reservations";

    // Get last CusID in Customer
    qry = new QSqlQuery(ref);
    if( qry->prepare(insertQuery))
    {
        qry->exec();
        qry->first();
        ResID = qry->value(0).toInt();
        qDebug() << " successfully returned.";
    } else {
        QSqlError error = qry->lastError();
        qDebug() << "Failed to prepare query.";
        qDebug() << "Database says: " + error.databaseText();
    }

    insertQuery = "INSERT INTO Payments (ResID, Balance) VALUES(" + QString::number(ResID) + "," + QString::number(total) + ")";
    qry = new QSqlQuery(ref);
    if( qry->prepare(insertQuery))
    {
        qry->exec();
        qDebug() << " successfully returned.";
    } else {
        error = qry->lastError();
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

int Reservations::FindAvailableRoomOfType(int type)
{

    QString query = "SELECT roomID FROM Rooms WHERE type = " + QString::number(type);
    QSqlQuery* qry = new QSqlQuery(ref);

    if( qry->prepare(query))
    {
        qry->exec();
        qry->first();
        qDebug() << " successfully returned.";
    } else {
        QSqlError error = qry->lastError();
        qDebug() << "Failed to prepare query.";
        qDebug() << "Database says: " + error.databaseText();
    }

    int x = QRandomGenerator::global()->bounded(0, qry->numRowsAffected() - 1);
    for(int i = 0; i < x; i++)
        qry->next();
    return qry->value(0).toInt();
}
