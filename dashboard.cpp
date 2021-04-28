#include "dashboard.h"
#include "ui_dashboard.h"
#include "loginauth.h"

DashBoard::DashBoard(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DashBoard)
{
    // Nothing before this line
    ui->setupUi(this);
    // Change the window title
    this->setWindowTitle("User Dashboard");
    // Hide database fail text
    ui->DatabaseLoadError->hide();
    // QPalette is used to change the color of the text in FailedAuth label to RED
    QPalette palette = ui->DatabaseLoadError->palette();
    palette.setColor(ui->DatabaseLoadError->backgroundRole(), Qt::red);
    palette.setColor(ui->DatabaseLoadError->foregroundRole(), Qt::red);
    ui->DatabaseLoadError->setPalette(palette);
    //
    // Set initial GUI enviornment
    ui->stackedWidgetRDB->setCurrentIndex(1);
    setBlankPage();
    //
    databaseInit();
}

DashBoard::~DashBoard()
{
    delete ui;
}

bool DashBoard::databaseInit()
{
    // Establish connection with SQLite Database
    //db = new DbManager("AntaresRDB.db");
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("AntaresRDB.db");
    if (!db.open())
    {
       qDebug() << "Error: connection with database fail";
       return false;
    } else {
       qDebug() << "Database: connection ok";
    }

    // Attempt to populate the DataTable
    //  If the DataTable can't be populated, display error text
    if( !db.isOpen() )
    {
        ui->DataTable->hide();
        ui->DatabaseLoadError->show();
    }

    if( db.isValid()) {
        qDebug() << "Database is valid.";
    }
    return true;
}

void DashBoard::on_LogoutButton_clicked()
{
    // Create new login form object, show the new window, and close the dashboard window
    LoginAuth *LoginLoader = new LoginAuth;
    LoginLoader->show();
    db.close();
    this->close();
}

void DashBoard::on_SearchButton_clicked()
{
    guestEdit = true;
    // Set the stacked widget to display the additional search GUI
    ui->stackedWidgetSR->setCurrentWidget(ui->SearchPage);
}

void DashBoard::on_DailyButton_clicked()
{
    guestEdit = true;
    // Hide unecessary GUI elements
    setBlankPage();
    updateTable("select * from Customer;");
}

void DashBoard::on_GuestsButton_clicked()
{
    guestEdit = true;
    // Hide unecessary GUI elements
    setBlankPage();
    updateTable("SELECT * FROM Customer");
}

void DashBoard::on_HousekeepingButton_clicked()
{
    guestEdit = false;
    // Hide unecessary GUI elements
    setBlankPage();
    updateTable("SELECT * FROM Customer");
}

void DashBoard::on_InfoButton_clicked()
{
    guestEdit = false;
    // Hide unecessary GUI elements
    setBlankPage();
    updateTable("SELECT * FROM Customer");
}

void DashBoard::on_ReservationButton_clicked()
{
    guestEdit = false;
    // Hide unecessary GUI elements
    setBlankPage();
    // Set the stacked widget to display the additional reservation GUI
    ui->stackedWidgetSR->setCurrentWidget(ui->ReservationPage);
}

void DashBoard::on_RoomsButton_clicked()
{
    guestEdit = false;
    // Hide unecessary GUI elements
    setBlankPage();
    // Set the stacked widget to display the room buttons
    setRoomStatusButtons();
    ui->stackedWidgetRDB->setCurrentIndex(0);
}

void DashBoard::on_WeeklyButton_clicked()
{
    guestEdit = false;
    // Hide unecessary GUI elements
    setBlankPage();
    updateTable("SELECT * FROM Customer");
}

void DashBoard::on_SubmitButon_clicked()
{
    // Execute SQL search query here
    updateTable("SELECT * FROM Customer");
}

void DashBoard::on_MakeResButton_clicked()
{
   guestEdit = false;
   // Create new form object and display the window
   Reservations* loadMe = new Reservations;
   // Disable window resizing
   loadMe->setFixedSize(loadMe->size());
   loadMe->setModal(1);
   loadMe->show();
}

void DashBoard::setBlankPage() {
    // Sets the stacked widget to display the blankPage when additional GUI
    //  elements are unecessary
    if(ui->stackedWidgetSR->currentIndex() != 0)
    {
        ui->stackedWidgetSR->setCurrentWidget(ui->BlankPage);
    }
    if(ui->stackedWidgetRDB->currentIndex() == 0)
    {
        ui->stackedWidgetRDB->setCurrentIndex(1);
    }
}

void DashBoard::setRoomButton(int roomNumber, QPushButton* button)
// void DashBoard::setRoomButton(int roomNumber, QPushButton* button, roomStatus status)
/*
 * We can use a database query to retrieve the value for the room status and append it to the strin as
 * I have commented out below.  This would allow dynamic button text and color.
 */
{
    QString* buttonText = new QString("Room " + QString::number(roomNumber) + " - #STATUS HERE#");// + getStringStatus(Query));
    button->setText(*buttonText);
    // Random coloring for testing
    int statusTemp = rand() % 4 + 0;
    //
    setColor(roomStatus(statusTemp), button);
}

QString DashBoard::getStatusString(roomStatus status)
{
    switch(status)
    {
        case AVAILABLE:
            return "Available";
            break;

        case OCCUPIED:
            return "Occupied";
            break;

        case DIRTY:
            return "Dirty";
            break;

        case MAINTENANCE:
            return "Maintenance Needed";
            break;

        default:
            return "Contact Tech Support";
            break;
    }
}

void DashBoard::setColor(roomStatus status, QPushButton* button) {
    switch(status)
    {
        case AVAILABLE:
            // Set Green
            button->setStyleSheet("font: bold;background-color : green;");
            break;

        case OCCUPIED:
            // Set Red
            button->setStyleSheet("font: bold;background-color : red");
            break;

        case DIRTY:
            // Set Yellow
            button->setStyleSheet("font: bold;background-color : yellow;");
            break;

        case MAINTENANCE:
            // Set Orange
            button->setStyleSheet("font: bold;background-color : orange;");
            break;

        default:
            // No Change -- defualt Grey
            break;
    }
}

void DashBoard::setRoomStatusButtons()
{
        srand (time(NULL));
        setRoomButton(10, ui->RoomButton_10);
        setRoomButton(11, ui->RoomButton_11);
        setRoomButton(12, ui->RoomButton_12);
        setRoomButton(13, ui->RoomButton_13);
        setRoomButton(14, ui->RoomButton_14);
        setRoomButton(15, ui->RoomButton_15);
        setRoomButton(16, ui->RoomButton_16);
        setRoomButton(17, ui->RoomButton_17);
        setRoomButton(18, ui->RoomButton_18);
        setRoomButton(19, ui->RoomButton_19);
        setRoomButton(20, ui->RoomButton_20);
        setRoomButton(21, ui->RoomButton_21);
        setRoomButton(22, ui->RoomButton_22);
        setRoomButton(23, ui->RoomButton_23);
        setRoomButton(24, ui->RoomButton_24);
}

void DashBoard::setRoomDetails(int roomNumber, QPushButton* button)
{
    QString details =
    "<body><style>#boxes {content: "";display: table;clear: both;}"
    "div {float: left;height: 470px;width: 23%;padding: 0 10px;}</style>"
    "<main id=\"boxes\">"
    ""
    "<div><h1>Room " + QString::number(roomNumber)+ " - #ROOM STATUS HERE# </h1>\n"
    "<p>This is information relevent to the rooms status.</p>"
    "<p>All of this text will be presented on the screen.</p></div>"
    "<p>That's right; look no further! More text!</p>"
    "<p>We can have more text here also! Yay html!</p>"
    "</div></main></body>";

    /*
     * Some SQL Query logic here and create a more detialed report
     */
    ui->textEdit->setText(details);
}

void DashBoard::updateTable(QString rawString)
{
     QSqlQueryModel* model = new QSqlQueryModel;
     QSqlQuery* qry = new QSqlQuery(db);
     if( qry->prepare(rawString) )
     {
        qry->exec();
        model->setQuery(*qry);
        ui->DataTable->setModel(model);
        qDebug() << model->rowCount() << " rows returned.";
     } else {
        QSqlError error = qry->lastError();
        qDebug() << "Failed to prepare query.";
        qDebug() << "Database says: " + error.databaseText();
     }
}

// Room status buttons for Capabillity one
void DashBoard::on_RoomButton_10_clicked()
{
    setRoomDetails(10, ui->RoomButton_10);
}

void DashBoard::on_RoomButton_11_clicked()
{
    setRoomDetails(11, ui->RoomButton_11);
}

void DashBoard::on_RoomButton_12_clicked()
{
    setRoomDetails(12, ui->RoomButton_12);
}

void DashBoard::on_RoomButton_13_clicked()
{
    setRoomDetails(13, ui->RoomButton_13);
}

void DashBoard::on_RoomButton_14_clicked()
{
    setRoomDetails(14, ui->RoomButton_14);
}

void DashBoard::on_RoomButton_15_clicked()
{
    setRoomDetails(15, ui->RoomButton_15);
}

void DashBoard::on_RoomButton_16_clicked()
{
    setRoomDetails(16, ui->RoomButton_16);
}

void DashBoard::on_RoomButton_17_clicked()
{
    setRoomDetails(17, ui->RoomButton_17);
}

void DashBoard::on_RoomButton_18_clicked()
{
    setRoomDetails(18, ui->RoomButton_18);
}

void DashBoard::on_RoomButton_19_clicked()
{
    setRoomDetails(19, ui->RoomButton_19);
}

void DashBoard::on_RoomButton_20_clicked()
{
    setRoomDetails(20, ui->RoomButton_20);
}

void DashBoard::on_RoomButton_21_clicked()
{
    setRoomDetails(21, ui->RoomButton_21);
}

void DashBoard::on_RoomButton_22_clicked()
{
    setRoomDetails(22, ui->RoomButton_22);
}

void DashBoard::on_RoomButton_23_clicked()
{
    setRoomDetails(23, ui->RoomButton_23);
}

void DashBoard::on_RoomButton_24_clicked()
{
    setRoomDetails(24, ui->RoomButton_24);
}



void DashBoard::on_DataTable_doubleClicked(const QModelIndex &index)
{
    if(guestEdit)
    {
        qDebug() << ui->DataTable->model()->data(ui->DataTable->model()->index(index.row(),0)).toInt();
        GuestInfo* loadMeBaby = new GuestInfo(&db, ui->DataTable->model()->data(ui->DataTable->model()->index(index.row(),0)).toInt());
        loadMeBaby->setModal(1);
        // Disable window resizing
        loadMeBaby->setFixedSize(loadMeBaby->size());
        loadMeBaby->show();
    }
    else
    {
        qDebug() << "Guest editting is not permitted at the momment.";
    }
}
