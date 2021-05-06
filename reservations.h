#ifndef RESERVATIONS_H
#define RESERVATIONS_H

#include <QDialog>
#include <QSqlQuery>
#include <qDebug>
#include <QSqlError>
#include <QRandomGenerator>
#include <QDate>


namespace Ui {
class Reservations;
}

class Reservations : public QDialog
{
    Q_OBJECT

public:
    explicit Reservations(QWidget *parent = nullptr);

    Reservations(QSqlDatabase*, int);
    Reservations(QSqlDatabase*);
    Reservations(QSqlDatabase*, QString date);
    ~Reservations();

    int FindAvailableRoomOfType(int type);

private slots:
    void on_ConfirmButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::Reservations *ui;
    int curRoom;            //Current room number for the reservation
    QSqlDatabase ref;
};

#endif // RESERVATIONS_H
