#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include "DbManager.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DashBoard; }
QT_END_NAMESPACE

class DashBoard : public QMainWindow
{
    Q_OBJECT

public:
    DashBoard(QWidget *parent = nullptr);
    ~DashBoard();

private slots:
    void on_LogoutButton_clicked();

    void on_SearchButton_clicked();

    void on_DailyButton_clicked();

    void on_GuestsButton_clicked();

    void on_HousekeepingButton_clicked();

    void on_InfoButton_clicked();

    void on_ReservationButton_clicked();

    void on_RoomsButton_clicked();

    void on_WeeklyButton_clicked();

    void on_SubmitButon_clicked();

private:
    Ui::DashBoard *ui;

    // Populate the DataTable with data from database
    //  Return false on invalid query
    bool PopulateDataTable(DbManager db);

    void setDisplayPage();
};
#endif // DASHBOARD_H
