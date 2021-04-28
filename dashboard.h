#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include "reservations.h"
#include <cmath>
#include <QTableWidget>
#include <QSqlDatabase>
#include <QSqlQueryModel>
#include <QDebug>
#include <QSqlError>
#include "guestinfo.h"

QT_BEGIN_NAMESPACE
namespace Ui { class DashBoard; }
QT_END_NAMESPACE

enum roomType {
    SUITE,
    DOUBLE_QUEEN,
    DOUBLE_QUEEN_KITCHEN,
    KING
};

enum roomStatus {
    AVAILABLE,
    OCCUPIED,
    DIRTY,
    MAINTENANCE
};

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

    void on_MakeResButton_clicked();

    // Room status buttons for Capabillity one
    void on_RoomButton_10_clicked();

    void on_RoomButton_11_clicked();

    void on_RoomButton_12_clicked();

    void on_RoomButton_13_clicked();

    void on_RoomButton_14_clicked();

    void on_RoomButton_15_clicked();

    void on_RoomButton_16_clicked();

    void on_RoomButton_17_clicked();

    void on_RoomButton_18_clicked();

    void on_RoomButton_19_clicked();

    void on_RoomButton_20_clicked();

    void on_RoomButton_21_clicked();

    void on_RoomButton_22_clicked();

    void on_RoomButton_23_clicked();

    void on_RoomButton_24_clicked();
    //

    // Opens the GuestInfo window when a cell is double clicked in the TableView
    //   with the guests information
    void on_DataTable_doubleClicked(const QModelIndex &index);

    void on_SearchField_returnPressed();

    void on_SearchField_editingFinished();

    void on_DataTable_customContextMenuRequested(const QPoint &pos);

private:
    Ui::DashBoard *ui;
    QSqlDatabase db;
    bool guestEdit;
    bool resEdit;
    bool hkEdit;
    int roomNum;
    int ResID;
    int roomID;
    QPushButton* roomPtr;

    // Databse initialization
    bool databaseInit();

    // Used to set the stacked widget to a blank space for all buttons
    //  except for the Reservations button and the search button as these
    //  requirements need additional GUI elements
    void setBlankPage();

    // Used to set the text and color of the QPushButtons for the Room Status display
    void setRoomButton(int roomNumber, QPushButton* button);
    void setRoomButton(int roomNumber, QPushButton* button, roomStatus status);

    // Returns the respective string for the given enum roomStatus value defined
    //  before the DashBoard class
    QString getStatusString(roomStatus status);

    // Sets the color of room status buttons
    void setColor(roomStatus status, QPushButton* button);

    // Sets all room status button text and colors
    void setRoomStatusButtons();

    // Sets the text of the Text Edit field for the respective room button.  This displays
    //  detailed information on the rooms status.
    void setRoomDetails(int roomNumber, QPushButton* button);

    // Use this function to update the tableView widget with the data from your SQL query
    void updateTable(QString);

    // Use this function to delete the selected reservation from the databse using ResID as a key value
    void deleteReservation();

    //Use this function to update the selected rooms bathroom status
    void bathEdit();

    //Use this function to update the selected rooms towel status
    void towelEdit();

    //Use this function to update the selected rooms vacuuming status
    void vacuumEdit();

    //Use this function to update the selected rooms dusting status
    void dustEdit();

    //Use this function to update the selected rooms electronics status
    void elecEdit();
};
#endif // DASHBOARD_H
