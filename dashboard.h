#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <QMainWindow>
#include "DbManager.h"
#include "reservations.h"
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui { class DashBoard; }
QT_END_NAMESPACE

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

private:
    Ui::DashBoard *ui;

    // Populate the DataTable with data from database
    //  Return false on invalid query
    bool PopulateDataTable(DbManager db);

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
};
#endif // DASHBOARD_H
