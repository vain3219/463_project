#include "alert.h"
#include "ui_alert.h"

Alert::Alert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Alert)
{
    ui->setupUi(this);
}

Alert::Alert(QString message) :
    ui(new Ui::Alert)
{

    ui->setupUi(this);
    acpt = false;
    setMessage(message);
    QWidget::raise();
    qDebug() << "Alerting user to change.";
}

Alert::~Alert()
{
    delete ui;
}

bool Alert::isAccepted()
{
    return acpt;
}

void Alert::setMessage(QString message)
{
    ui->Message->setText(message);
    ui->Message->setAlignment(Qt::AlignCenter);
}
void Alert::on_Continue_clicked()
{
    acpt = true;
    this->hide();
}

void Alert::on_Cancel_clicked()
{
    this->close();
}
