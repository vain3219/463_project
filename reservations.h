#ifndef RESERVATIONS_H
#define RESERVATIONS_H

#include <QDialog>
#include "DbManager.h"

namespace Ui {
class Reservations;
}

class Reservations : public QDialog
{
    Q_OBJECT

public:
    explicit Reservations(QWidget *parent = nullptr);
    ~Reservations();

private slots:
    void on_ConfirmButton_clicked();

    void on_CancelButton_clicked();

private:
    Ui::Reservations *ui;
};

#endif // RESERVATIONS_H
