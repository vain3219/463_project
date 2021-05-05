#include "guestinfo.h"
#include "ui_guestinfo.h"

GuestInfo::GuestInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GuestInfo)
{
    ui->setupUi(this);
}

GuestInfo::GuestInfo(QSqlDatabase* db, int id) :
    ui(new Ui::GuestInfo)
{
    ui->setupUi(this);
    // Change the window title
    this->setWindowTitle("Guest Profile Information");

    // Console output
    qDebug() << "Customer id: " + QString::number(id);

    // Fills the text fields with their appropriate data
    setTextFields(db, id);

    dbRef = db;
    cusId = id;
}

GuestInfo::~GuestInfo()
{
    delete ui;
}

void GuestInfo::on_submit_clicked()
{
    Alert* loadMeUp = new Alert("Are you sure you wish to make changes to this customers profile?\nChanges can't be undone.");
    loadMeUp->setModal(1);
    // Disable window resizing
    loadMeUp->setFixedSize(loadMeUp->size());
    loadMeUp->exec();

    QString FName = "\"" + ui->FName->text() + "\"";
    QString LName = "\"" + ui->LName->text() + "\"";
    QString IDNum = "\"" + ui->IDNum->text() + "\"";
    QString IDState = "\"" + ui->IDState->text() + "\"";
    QString LicensePlate = "\"" + ui->LicensePlate->text() + "\"";
    QString Address = "\"" + ui->Address->text() + "\"";
    QString Phone = "\"" + ui->Phone->text() + "\"";
    QString Email = "\"" + ui->Email->text() + "\"";

    if(loadMeUp->isAccepted()) {
        QSqlQuery* qry = new QSqlQuery(*dbRef);
        /*
         * Submit query here to edit the information
         */
        // QSqlQuery* qry = new QSqlQuery(*dbRef);
        QString rawString = "UPDATE Customer SET FName = " + FName + ", LName = " + LName + ", IDNum = " + IDNum + ", IDState = " + IDState + ", LicensePlate = " + LicensePlate + ", Address = " + Address + ", Phone = " + Phone + ", Email = " + Email + "WHERE CusID = " + QString::number(cusId);
        qDebug() << "cusId = " << cusId;
        if(qry->prepare(rawString)) {
            qry->exec();

            qDebug() << "Query successful.";
        } else {
            QSqlError error = qry->lastError();
            qDebug() << "Failed to prepare query.";
            qDebug() << "Databvase says: " + error.databaseText();
        }

        qDebug() << "Change submitted.";
    } else {
        qDebug() << "No changes were made.";
    }

    loadMeUp->close();
    delete loadMeUp;
    this->close();
}

void GuestInfo::on_back_clicked()
{
    qDebug() << "No changes were made.";
    this->close();
}

void GuestInfo::setTextFields(QSqlDatabase* db, int id)
{
    QSqlQuery* qry = new QSqlQuery(*db);
    if( qry->prepare("SELECT * FROM Customer WHERE CusID = " + QString::number(id)) )
    {
       qry->exec();
       qry->first();
       qDebug() << "Returned row for Customer " +QString::number(id);

       // Set text fields
       ui->FName->setText(qry->value(1).toString());
       ui->LName->setText(qry->value(2).toString());
       ui->IDNum->setText(qry->value(3).toString());
       ui->IDState->setText(qry->value(4).toString());
       ui->LicensePlate->setText(qry->value(5).toString());
       ui->Address->setText(qry->value(6).toString());
       ui->Phone->setText(qry->value(7).toString());
       ui->Email->setText(qry->value(8).toString());
    } else {
       QSqlError error = qry->lastError();
       qDebug() << "Failed to prepare query.";
       qDebug() << "Database says: " + error.databaseText();
    }
}

