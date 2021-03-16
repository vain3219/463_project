#ifndef LOGINAUTH_H
#define LOGINAUTH_H

#include <QDialog>
#include <QAbstractButton>

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
    void on_LoginButton_clicked();

    void on_ExitButton_clicked();

private:
    Ui::LoginAuth *ui;
};

#endif // LOGINAUTH_H
