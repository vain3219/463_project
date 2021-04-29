#ifndef ALERT_H
#define ALERT_H

#include <QDialog>
#include <qDebug>

namespace Ui {
class Alert;
}

class Alert : public QDialog
{
    Q_OBJECT

public:
    explicit Alert(QWidget *parent = nullptr);
    Alert(QString meassge);
    ~Alert();

    bool isAccepted();

private slots:
    void on_Continue_clicked();

    void on_Cancel_clicked();

private:
    Ui::Alert *ui;
    bool acpt;

    void setMessage(QString meassge);
};

#endif // ALERT_H
