#ifndef RESERVATIONS_H
#define RESERVATIONS_H

#include <QDialog>
#include <QSqlQuery>
#include <qDebug>
#include <QSqlError>

namespace Ui {
class Reservations;
}

class Reservations : public QDialog
{
    Q_OBJECT

public:
    explicit Reservations(QWidget *parent = nullptr);

    Reservations(QSqlDatabase*, int);
    ~Reservations();

private slots:
    void on_ConfirmButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::Reservations *ui;
    QSqlDatabase* dbRef;    // Reference to the database for executing queries
    int curRoom;            //Current room number for the reservation
};

#endif // RESERVATIONS_H
