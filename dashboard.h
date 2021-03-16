#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>


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

private:
    Ui::DashBoard *ui;

    // Populate the DataTable with data from database
    //  Return false on invalid query
    bool PopulateDataTable();
};
#endif // DASHBOARD_H
