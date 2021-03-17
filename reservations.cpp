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

Reservations::~Reservations()
{
    delete ui;
}

void Reservations::on_ConfirmButton_clicked()
{
    // Do text extraction from input fields here


    // Do query to insert the new reservation here


    // Close the window after successful query
    this->close();
}

void Reservations::on_CancelButton_clicked()
{
    // Close window and return to dashboard
    this->close();
}
