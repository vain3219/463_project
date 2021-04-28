#ifndef GUESTINFO_H
#define GUESTINFO_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <qDebug>

#include "alert.h"

namespace Ui {
class GuestInfo;
}

class GuestInfo : public QDialog
{
    Q_OBJECT

public:
    explicit GuestInfo(QWidget *parent = nullptr);
    GuestInfo(QSqlDatabase* db, int id);
    ~GuestInfo();

private slots:
    void on_submit_clicked();

    void on_back_clicked();

private:
    Ui::GuestInfo *ui;

    void setTextFields(QSqlDatabase* db, int id);
};

#endif // GUESTINFO_H
