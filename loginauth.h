#ifndef LOGINAUTH_H
#define LOGINAUTH_H

#include <QDialog>
#include <QAbstractButton>
#include "dashboard.h"

namespace Ui {
class LoginAuth;
}

class LoginAuth : public QDialog
{
    Q_OBJECT

public:
    explicit LoginAuth(QWidget *parent = nullptr);
    ~LoginAuth();

private slots:
    void on_LoginButton_clicked(QAbstractButton *button);

private:
    Ui::LoginAuth *ui;
    DashBoard *loadMeDaddy;
};

#endif // LOGINAUTH_H
