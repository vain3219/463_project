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

    updateTable("select * from Customer;");

    ui->DataTable->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->DataTable, SIGNAL(customContextMenuRequested(QPoint)), SLOT(customMenuRequested(QPoint)));
}

DashBoard::~DashBoard()
{
    delete ui;
}

bool DashBoard::databaseInit()
{
    // Establish connection with SQLite Database
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("AntaresRDB.db");
//    db.setDatabaseName("C://Users//Grant//Downloads//AntaresRDB.db");
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
// Capability 7
{
    guestEdit = true;
    resEdit = false;
    hkEdit = false;
    // Set the stacked widget to display the additional search GUI
    ui->stackedWidgetSR->setCurrentWidget(ui->SearchPage);
}

void DashBoard::on_DailyButton_clicked()
{
    guestEdit = true;
    resEdit = false;
    hkEdit = false;
    // Hide unecessary GUI elements
    setBlankPage();
    updateTable("select * from Customer;");
}

void DashBoard::on_GuestsButton_clicked()
{
    guestEdit = true;
    resEdit = false;
    hkEdit = false;
    // Hide unecessary GUI elements
    setBlankPage();
    updateTable("SELECT * FROM Customer");
}

void DashBoard::on_HousekeepingButton_clicked()
{
    guestEdit = false;
    resEdit = false;
    hkEdit = true;
    // Hide unecessary GUI elements
    setBlankPage();
    updateTable("SELECT * FROM Rooms");
}

void DashBoard::on_InfoButton_clicked()
{
    guestEdit = false;
    resEdit = false;
    hkEdit = false;
    // Hide unecessary GUI elements
    setBlankPage();
    updateTable("SELECT * FROM Customer");
}

void DashBoard::on_ReservationButton_clicked()
{
    guestEdit = false;
    resEdit = true;
    hkEdit = false;
    // Hide unecessary GUI elements
    setBlankPage();
    // Set the stacked widget to display the additional reservation GUI
    ui->stackedWidgetSR->setCurrentWidget(ui->ReservationPage);
        updateTable("SELECT * FROM Reservations");
}

void DashBoard::on_RoomsButton_clicked()
{
    guestEdit = false;
    resEdit = false;
    hkEdit = false;
    // Hide unecessary GUI elements
    setBlankPage();
    // Set the stacked widget to display the room buttons
    setRoomStatusButtons();
    ui->stackedWidgetRDB->setCurrentIndex(0);
}

void DashBoard::on_WeeklyButton_clicked()  // capability 2 FILL THIS IN
{
    guestEdit = false;
    resEdit = false;
    hkEdit = false;
    // Hide unecessary GUI elements
    setBlankPage();
    ui->stackedWidgetSR->setCurrentIndex(3);
    QDate cd = QDate::currentDate();
    QString current = cd.toString(Qt::ISODate);

    QHeaderView *vertHeader = new QHeaderView(Qt::Vertical, ui->DataTable);

    updateTable("SELECT "
    "CASE WHEN Reservations.CheckIn = '" + current + "' THEN 'Room: ' || Rooms.RoomID || ' ' || Customer.LName || ', ' || Customer.FName ELSE 'Room: ' || Rooms.RoomID END '" + current +"', "
    "CASE WHEN Reservations.CheckIn = '" + cd.addDays(1).toString(Qt::ISODate) + "' THEN 'Room: ' || Rooms.RoomID || ' ' || Customer.LName || ', ' || Customer.FName ELSE 'Room: ' || Rooms.RoomID  END '" + cd.addDays(1).toString(Qt::ISODate) + "', "
    "CASE WHEN Reservations.CheckIn = '" + cd.addDays(2).toString(Qt::ISODate) + "' THEN 'Room: ' || Rooms.RoomID || ' ' || Customer.LName || ', ' || Customer.FName ELSE 'Room: ' || Rooms.RoomID  END '" + cd.addDays(2).toString(Qt::ISODate) + "', "
    "CASE WHEN Reservations.CheckIn = '" + cd.addDays(3).toString(Qt::ISODate) + "' THEN 'Room: ' || Rooms.RoomID || ' ' || Customer.LName || ', ' || Customer.FName ELSE 'Room: ' || Rooms.RoomID  END '" + cd.addDays(3).toString(Qt::ISODate) + "', "
    "CASE WHEN Reservations.CheckIn = '" + cd.addDays(4).toString(Qt::ISODate) + "' THEN 'Room: ' || Rooms.RoomID || ' ' || Customer.LName || ', ' || Customer.FName ELSE 'Room: ' || Rooms.RoomID  END '" + cd.addDays(4).toString(Qt::ISODate) + "', "
    "CASE WHEN Reservations.CheckIn = '" + cd.addDays(5).toString(Qt::ISODate) + "' THEN 'Room: ' || Rooms.RoomID || ' ' || Customer.LName || ', ' || Customer.FName ELSE 'Room: ' || Rooms.RoomID  END '" + cd.addDays(5).toString(Qt::ISODate) + "', "
    "CASE WHEN Reservations.CheckIn = '" + cd.addDays(6).toString(Qt::ISODate) + "' THEN 'Room: ' || Rooms.RoomID || ' ' || Customer.LName || ', ' || Customer.FName ELSE 'Room: ' || Rooms.RoomID  END '" + cd.addDays(6).toString(Qt::ISODate) + "' "
    "FROM Rooms LEFT JOIN Reservations ON Rooms.RoomID = Reservations.RoomID "
    "LEFT JOIN Customer ON Reservations.CusID = Customer.CusID");
    for(int i = 0; i < 7; i++) {
        ui->DataTable->setColumnWidth(i, 150);
    }
    ui->DataTable->setVerticalHeader(vertHeader);
    ui->Day1->setText(current);
    ui->Day2->setText(cd.addDays(1).toString(Qt::ISODate));
    ui->Day3->setText(cd.addDays(2).toString(Qt::ISODate));
    ui->Day4->setText(cd.addDays(3).toString(Qt::ISODate));
    ui->Day5->setText(cd.addDays(4).toString(Qt::ISODate));
    ui->Day6->setText(cd.addDays(5).toString(Qt::ISODate));
    ui->Day7->setText(cd.addDays(6).toString(Qt::ISODate));

}

void DashBoard::on_SubmitButon_clicked()
{
    QString inputStr = ui->SearchField->text(), statement;
    QVector<QStringRef> args = inputStr.splitRef(" ");
    QSqlQuery* qry = new QSqlQuery(db);
    int cusID = 0;

    qDebug() << QString::number(args.count()) + " arguements given.";

    switch(args.count())
    {
    case 0:
        ui->SearchField->placeholderText() = "Please enter a first and/or last name";
        break;

    case 1:
        statement = "SELECT CusID FROM Customer WHERE (FName = '" + args.at(0) + "' OR LName = '" + args.at(0) + "' )";
        qDebug() << args.at(0);
        break;


    case 2:
        statement = "SELECT CusID FROM Customer WHERE (FName = '" + args.at(0) + "' OR LName = '" + args.at(1) + "' )";
        qDebug() << args.at(0);
        qDebug() << args.at(1);
        break;
    }

    if( qry->prepare(statement) && args.count() > 0 )
    {
        qry->exec();
        qry->first();
        qDebug() << "Customer found.";
        cusID = qry->value(0).toInt();
        // add "Reservations.roomNum" to the query
        updateTable("SELECT Customer.FName, Customer.LName, Customer.Phone, Customer.Address, Reservations.CheckIn, Reservations.Checkout "
            "FROM Reservations INNER JOIN Customer ON Reservations.CusID = Customer.CusID WHERE Reservations.CusID = " + QString::number(cusID));
    } else {
        QSqlError error = qry->lastError();
        qDebug() << "Failed to prepare query.";
        qDebug() << "Database says: " + error.databaseText();
    }
}

void DashBoard::on_SearchField_returnPressed()
{
    on_SubmitButon_clicked();
}

void DashBoard::on_SearchField_editingFinished()
{
    on_SubmitButon_clicked();
}

void DashBoard::on_MakeResButton_clicked()
{
   guestEdit = false;
   resEdit = false;
   hkEdit = false;
   // Create new form object and display the window
   Reservations* loadMe = new Reservations(&db);
   // Disable window resizing
   loadMe->setFixedSize(loadMe->size());
   loadMe->setModal(1);
   loadMe->show();
}

void DashBoard::setBlankPage() {
    // Sets the stacked widget to display the blankPage when additional GUI
    //  elements are unecessary
    ui->changeAvailable->hide();
    ui->doNothing->hide();
    ui->makeRes->hide();
    if(ui->stackedWidgetSR->currentIndex() != 0)
    {
        ui->stackedWidgetSR->setCurrentWidget(ui->BlankPage);
    }
    if(ui->stackedWidgetRDB->currentIndex() == 0)
    {
        ui->stackedWidgetRDB->setCurrentIndex(1);
    }
}

void DashBoard::setRoomButton(int roomNumber, QPushButton* button)          // CAPABILITY 1
// void DashBoard::setRoomButton(int roomNumber, QPushButton* button, roomStatus status)
/*
 * We can use a database query to retrieve the value for the room status and append it to the strin as
 * I have commented out below.  This would allow dynamic button text and color.
 */
{
    // query string status here
    int status = 0;
    QSqlQuery* qry = new QSqlQuery(db);
    if( qry->prepare("SELECT Status FROM Rooms WHERE RoomID IS " + QString::number(roomNumber) + ";"))
    {
       qry->exec();
       qry->first();
       status = qry->value(0).toInt();
       qDebug() << " successfully returned.";
    } else {
       QSqlError error = qry->lastError();
       qDebug() << "Failed to prepare query.";
       qDebug() << "Database says: " + error.databaseText();
    }
    QString* buttonText = new QString("Room " + QString::number(roomNumber) + " Status: " + getStatusString(status));// + getStringStatus(Query));
    button->setText(*buttonText);
    // Random coloring for testing
    //int statusTemp = rand() % 4 + 0;        // query for status
    //
    setColor(roomStatus(status), button);
}

void DashBoard::setRoomButtonDaily(int roomNumber, QString cd, QPushButton* button) {

    QSqlQuery* qry = new QSqlQuery(db);
    if(qry->prepare("SELECT RoomID FROM Reservations WHERE CheckIn IS '" + cd + "' AND RoomID IS " + QString::number(roomNumber) + ";")) {
        qry->exec();
        qDebug() << cd;
        if(qry->first())
        {
            qDebug() << qry->value(0).toInt();
            QString* buttonText = new QString("Room " + QString::number(roomNumber) + " Status: Reserved");
            button->setText(*buttonText);
            setColor(roomStatus(1), button);
        } else {
            QString* buttonText = new QString("Room " + QString::number(roomNumber) + " Status: Available");
            button->setText(*buttonText);
            setColor(roomStatus(AVAILABLE), button);
        }

        qDebug() << " did it.";
    } else {
        QSqlError error = qry->lastError();
        qDebug() << "Nope";
    }
    //QString* buttonText = new QString("Room " + QString::number(roomNumber) + " Status: " + getStatusString(status));
   // button->setText(*buttonText);
   // setColor(roomStatus(status), button);
}

QString DashBoard::getStatusString(int status)
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
        srand (time(NULL));     // get rid of
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
    ui->changeAvailable->hide();
    ui->doNothing->hide();
    ui->makeRes->hide();
    int status = 0;
    QString details = "<body><style>#boxes {content: "";display: table;clear: both;}"
        "div {float: left;height: 470px;width: 23%;padding: 0 10px;}</style>"
        "<main id=\"boxes\">"
        ""
        "<div><h1>Room ";
    QSqlQuery* qry = new QSqlQuery(db);
    if( qry->prepare("SELECT Status FROM Rooms WHERE RoomID IS " + QString::number(roomNumber) + ";"))
    {
       qry->exec();
       qry->first();
       status = qry->value(0).toInt();
       qDebug() << " successfully returned.";
    } else {
       QSqlError error = qry->lastError();
       qDebug() << "Failed to prepare query.";
       qDebug() << "Database says: " + error.databaseText();
    }

    if(status == AVAILABLE && selectedDay != QDate::currentDate().toString())
    {
        // CAPABILITY 6 BUTTON PRESSED
        ui->makeRes->show();
    }
    else if(status == OCCUPIED)
    {
        // CAPABILITY 6 BUTTON PRESSED
    }
    else if(status == DIRTY)
    {
        details += QString::number(roomNumber)+ " - DIRTY </h1>\n"     // CAPABILITY 1
        "<p>This room is currently dirty.</p>"
        "<p>Do you want to make the room available?</p>"
        "</div></main></body>";
        ui->changeAvailable->show();
        ui->doNothing->show();
    }
    else if(status == MAINTENANCE)
    {
        details += QString::number(roomNumber)+ " - DIRTY </h1>\n"     // CAPABILITY 1
        "<p>This room is currently under maintenance.</p>"
        "<p>Do you want to make the room available?</p>"
        "</div></main></body>";
        ui->changeAvailable->show();
        ui->doNothing->show();
    }

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
     ui->DataTable->resizeColumnsToContents();
}

// Room status buttons for Capabillity one
void DashBoard::on_RoomButton_10_clicked()
{
    roomNum = 10;
    roomPtr = ui->RoomButton_10;
    setRoomDetails(10, ui->RoomButton_10);
}

void DashBoard::on_RoomButton_11_clicked()
{
    roomNum = 11;
    roomPtr = ui->RoomButton_11;
    setRoomDetails(11, ui->RoomButton_11);
}

void DashBoard::on_RoomButton_12_clicked()
{
    roomNum = 12;
    roomPtr = ui->RoomButton_12;
    setRoomDetails(12, ui->RoomButton_12);
}

void DashBoard::on_RoomButton_13_clicked()
{
    roomNum = 13;
    roomPtr = ui->RoomButton_13;
    setRoomDetails(13, ui->RoomButton_13);
}

void DashBoard::on_RoomButton_14_clicked()
{
    roomNum = 14;
    roomPtr = ui->RoomButton_14;
    setRoomDetails(14, ui->RoomButton_14);
}

void DashBoard::on_RoomButton_15_clicked()
{
    roomNum = 15;
    roomPtr = ui->RoomButton_15;
    setRoomDetails(15, ui->RoomButton_15);
}

void DashBoard::on_RoomButton_16_clicked()
{
    roomNum = 16;
    roomPtr = ui->RoomButton_16;
    setRoomDetails(16, ui->RoomButton_16);
}

void DashBoard::on_RoomButton_17_clicked()
{
    roomNum = 17;
    roomPtr = ui->RoomButton_17;
    setRoomDetails(17, ui->RoomButton_17);
}

void DashBoard::on_RoomButton_18_clicked()
{
    roomNum = 18;
    roomPtr = ui->RoomButton_18;
    setRoomDetails(18, ui->RoomButton_18);
}

void DashBoard::on_RoomButton_19_clicked()
{
    roomNum = 19;
    roomPtr = ui->RoomButton_19;
    setRoomDetails(19, ui->RoomButton_19);
}

void DashBoard::on_RoomButton_20_clicked()
{
    roomNum = 20;
    roomPtr = ui->RoomButton_20;
    setRoomDetails(20, ui->RoomButton_20);
}

void DashBoard::on_RoomButton_21_clicked()
{
    roomNum = 21;
    roomPtr = ui->RoomButton_21;
    setRoomDetails(21, ui->RoomButton_21);
}

void DashBoard::on_RoomButton_22_clicked()
{
    roomNum = 22;
    roomPtr = ui->RoomButton_22;
    setRoomDetails(22, ui->RoomButton_22);
}

void DashBoard::on_RoomButton_23_clicked()
{
    roomNum = 23;
    roomPtr = ui->RoomButton_23;
    setRoomDetails(23, ui->RoomButton_23);
}

void DashBoard::on_RoomButton_24_clicked()
{
    roomNum = 24;
    roomPtr = ui->RoomButton_24;
    setRoomDetails(24, ui->RoomButton_24);
}

void DashBoard::on_changeAvailable_clicked()
{
    // update query
    QSqlQuery* qry = new QSqlQuery(db);
    if( qry->prepare("UPDATE Rooms SET Status = 0 WHERE RoomID = " + QString::number(roomNum) + ";"))
    {
       qry->exec();
       qDebug() << " successfully returned.";
    } else {
       QSqlError error = qry->lastError();
       qDebug() << "Failed to prepare query.";
       qDebug() << "Database says: " + error.databaseText();
    }

    setRoomButton(roomNum, roomPtr);
    setRoomDetails(roomNum, roomPtr);

}

void DashBoard::dailyButtonUpdate(QString cd) {
    setRoomButtonDaily(10, cd, ui->RoomButton_10);
    setRoomButtonDaily(11, cd, ui->RoomButton_11);
    setRoomButtonDaily(12, cd, ui->RoomButton_12);
    setRoomButtonDaily(13, cd, ui->RoomButton_13);
    setRoomButtonDaily(14, cd, ui->RoomButton_14);
    setRoomButtonDaily(15, cd, ui->RoomButton_15);
    setRoomButtonDaily(16, cd, ui->RoomButton_16);
    setRoomButtonDaily(17, cd, ui->RoomButton_17);
    setRoomButtonDaily(18, cd, ui->RoomButton_18);
    setRoomButtonDaily(19, cd, ui->RoomButton_19);
    setRoomButtonDaily(20, cd, ui->RoomButton_20);
    setRoomButtonDaily(21, cd, ui->RoomButton_21);
    setRoomButtonDaily(22, cd, ui->RoomButton_22);
    setRoomButtonDaily(23, cd, ui->RoomButton_23);
    setRoomButtonDaily(24, cd, ui->RoomButton_24);
}

void DashBoard::on_Day1_clicked()
{
    QDate cd = QDate::currentDate();
    QString current = cd.toString(Qt::ISODate);
    selectedDay = cd.toString();
    ui->stackedWidgetRDB->setCurrentIndex(0);
    dailyButtonUpdate(current);
}

void DashBoard::on_Day2_clicked()
{
    QDate cd = QDate::currentDate();
    QString current = cd.addDays(1).toString(Qt::ISODate);
    selectedDay = cd.addDays(1).toString();
    ui->stackedWidgetRDB->setCurrentIndex(0);
    dailyButtonUpdate(current);
}

void DashBoard::on_Day3_clicked()
{
    QDate cd = QDate::currentDate();
    QString current = cd.addDays(2).toString(Qt::ISODate);
    selectedDay = cd.addDays(2).toString();
    ui->stackedWidgetRDB->setCurrentIndex(0);
    dailyButtonUpdate(current);
}

void DashBoard::on_Day4_clicked()
{
    QDate cd = QDate::currentDate();
    QString current = cd.addDays(3).toString(Qt::ISODate);
    selectedDay = cd.addDays(3).toString();
    ui->stackedWidgetRDB->setCurrentIndex(0);
    dailyButtonUpdate(current);
}

void DashBoard::on_Day5_clicked()
{
    QDate cd = QDate::currentDate();
    QString current = cd.addDays(4).toString(Qt::ISODate);
    selectedDay = cd.addDays(4).toString();
    ui->stackedWidgetRDB->setCurrentIndex(0);
    dailyButtonUpdate(current);
}

void DashBoard::on_Day6_clicked()
{
    QDate cd = QDate::currentDate();
    QString current = cd.addDays(5).toString(Qt::ISODate);
    selectedDay = cd.addDays(5).toString();
    ui->stackedWidgetRDB->setCurrentIndex(0);
    dailyButtonUpdate(current);
}

void DashBoard::on_Day7_clicked()
{
    QDate cd = QDate::currentDate();
    QString current = cd.addDays(6).toString(Qt::ISODate);
    selectedDay = cd.addDays(6).toString();
    ui->stackedWidgetRDB->setCurrentIndex(0);
    dailyButtonUpdate(current);
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

void DashBoard::on_DataTable_customContextMenuRequested(const QPoint &pos)
{
         qDebug() << "Right clicked.  Displaying context menu.";
    if( resEdit )
    {
        qDebug() << "Reservation editting menu.";
        QModelIndex index= ui->DataTable->indexAt(pos);

        QMenu *menu=new QMenu(this);
        QAction* del= new QAction("Delete Reservation", this);
        menu->addAction(del);
        del->setStatusTip("Deleted the currently selected row.");
        menu->popup(ui->DataTable->viewport()->mapToGlobal(pos));
        ResID = ui->DataTable->model()->data(ui->DataTable->model()->index(index.row(),0)).toInt();
        connect(del, &QAction::triggered, this, &DashBoard::deleteReservation);
    }
    else if( hkEdit )
    {
        qDebug() << "Housekeeping editting menu.";
        QModelIndex index= ui->DataTable->indexAt(pos);

        QMenu *menu=new QMenu(this);
        QAction* Bathroom= new QAction("Bathroom", this);
        QAction* Towels= new QAction("Towels", this);
        QAction* Vacuum= new QAction("Vacuum", this);
        QAction* Dusting= new QAction("Dusting", this);
        QAction* Electronics= new QAction("Electronics", this);

        menu->addAction(Bathroom);
        Bathroom->setStatusTip("Bathroom cleaning requested");
        Bathroom->setCheckable(true);

        menu->addAction(Towels);
        Towels->setStatusTip("Towels requested");
        Towels->setCheckable(true);

        menu->addAction(Vacuum);
        Vacuum->setStatusTip("Vacuuming requested");
        Vacuum->setCheckable(true);

        menu->addAction(Dusting);
        Dusting->setStatusTip("Dusting requested");
        Dusting->setCheckable(true);

        menu->addAction(Electronics);
        Electronics->setStatusTip("Electronics help requested");
        Electronics->setCheckable(true);

        menu->popup(ui->DataTable->viewport()->mapToGlobal(pos));
        roomID = ui->DataTable->model()->data(ui->DataTable->model()->index(index.row(),0)).toInt();
        connect(Bathroom, &QAction::toggled, this, &DashBoard::bathEdit);
        connect(Towels, &QAction::toggled, this, &DashBoard::towelEdit);
        connect(Vacuum, &QAction::toggled, this, &DashBoard::vacuumEdit);
        connect(Dusting, &QAction::toggled, this, &DashBoard::dustEdit);
        connect(Electronics, &QAction::toggled, this, &DashBoard::elecEdit);

        //  GRANT
        // SQL query here to check if the selected room(defined by variable roomID) is currently available
        QSqlQuery* qry = new QSqlQuery(db);
        int set = 0;
        if(qry->prepare("SELECT Status FROM Rooms WHERE RoomID = " + QString::number(roomID)) )        {
           qry->exec();
           qry->first();
           set = qry->value(0).toInt();
           qDebug() << QString::number(set);
           if(set != 0)
           {
               qDebug() << "Present 'Make room unavaible' option";
               QAction* makeUn= new QAction("Make room unavaible", this);

               menu->addSection("Availability");
               menu->addAction(makeUn);
               makeUn->setStatusTip("Make the selected room unavaible");
               makeUn->setCheckable(true);

               connect(makeUn, &QAction::toggled, this, &DashBoard::makeRoomUnavailable);
           }
           else
           {
              qDebug() << "The selected room is already unavailable";
           }
        }

    }
    else
    {
        qDebug() << "Context menu unavailable.";
    }
}

void DashBoard::deleteReservation()
{
    qDebug() << "Delete selected.";

    Alert* alert = new Alert("Are you sure you want to delete this reservation?\nThis action can't be undone.");
    alert->setModal(1);
    // Disable window resizing
    alert->setFixedSize(alert->size());
    alert->exec();

    if(alert->isAccepted()) {
        QSqlQuery* qry = new QSqlQuery(db);
        if( qry->prepare("DELETE FROM Reservations WHERE ResID = " + QString::number(ResID)) )
        {
           qry->exec();
        } else {
           QSqlError error = qry->lastError();
           qDebug() << "Failed to prepare query.";
           qDebug() << "Database says: " + error.databaseText();
        }

        qDebug() << "Reservation " + QString::number(ResID) + " has been deleted";
    } else {
        qDebug() << "No changes were made.";
    }

    alert->close();
    delete alert;

    updateTable("Select * FROM Reservations");
}

void DashBoard::bathEdit()
{
//df
    //edit here
    QSqlQuery* qry = new QSqlQuery(db);
    int set = 0;
    if(qry->prepare("SELECT Bathroom FROM Rooms WHERE RoomID = " + QString::number(roomID)) )
    {
       qry->exec();
       qry->first();
       set = qry->value(0).toInt();


       if(set == 0) {
           qry->prepare("UPDATE Rooms SET Bathroom = " + QString::number(1) + " WHERE RoomID = " + QString::number(roomID));
           qDebug() << "Room " + QString::number(roomID) + " requires bathroom cleaning";
       }
       else {
           qry->prepare("UPDATE Rooms SET Bathroom = " + QString::number(0) + " WHERE RoomID = " + QString::number(roomID));
           qDebug() << "Room " + QString::number(roomID) + " does not require bathroom cleaning";
       }
       qry->exec();
       updateTable("SELECT * FROM Rooms");

    }
    else
    {
        QSqlError error = qry->lastError();
        qDebug() << "Failed to prepare query.";
        qDebug() << "Database says: " + error.databaseText();
    }
}

void DashBoard::towelEdit()
{
    //edit here
    QSqlQuery* qry = new QSqlQuery(db);
    int set = 0;
    if(qry->prepare("SELECT Towels FROM Rooms WHERE RoomID = " + QString::number(roomID)) )
    {
       qry->exec();
       qry->first();
       set = qry->value(0).toInt();


       if(set == 0) {
           qry->prepare("UPDATE Rooms SET Towels = " + QString::number(1) + " WHERE RoomID = " + QString::number(roomID));
           qDebug() << "Room " + QString::number(roomID) + " requires towels";
       }
       else {
           qry->prepare("UPDATE Rooms SET Towels = " + QString::number(0) + " WHERE RoomID = " + QString::number(roomID));
           qDebug() << "Room " + QString::number(roomID) + " does not require towels";
       }
       qry->exec();
       updateTable("SELECT * FROM Rooms");

    }
    else
    {
        QSqlError error = qry->lastError();
        qDebug() << "Failed to prepare query.";
        qDebug() << "Database says: " + error.databaseText();
    }
}

void DashBoard::vacuumEdit()
{
    QSqlQuery* qry = new QSqlQuery(db);
    int set = 0;
    if(qry->prepare("SELECT Vacuum FROM Rooms WHERE RoomID = " + QString::number(roomID)) )
    {
       qry->exec();
       qry->first();
       set = qry->value(0).toInt();


       if(set == 0) {
           qry->prepare("UPDATE Rooms SET Vacuum = " + QString::number(1) + " WHERE RoomID = " + QString::number(roomID));
           qDebug() << "Room " + QString::number(roomID) + " requires vacuuming";
       }
       else {
           qry->prepare("UPDATE Rooms SET Vacuum = " + QString::number(0) + " WHERE RoomID = " + QString::number(roomID));
           qDebug() << "Room " + QString::number(roomID) + " does not require vacuuming";
       }
       qry->exec();
       updateTable("SELECT * FROM Rooms");

    }
    else
    {
        QSqlError error = qry->lastError();
        qDebug() << "Failed to prepare query.";
        qDebug() << "Database says: " + error.databaseText();
    }
}

void DashBoard::dustEdit()
{
    QSqlQuery* qry = new QSqlQuery(db);
    int set = 0;
    if(qry->prepare("SELECT Dusting FROM Rooms WHERE RoomID = " + QString::number(roomID)) )
    {
       qry->exec();
       qry->first();
       set = qry->value(0).toInt();


       if(set == 0) {
           qry->prepare("UPDATE Rooms SET Dusting = " + QString::number(1) + " WHERE RoomID = " + QString::number(roomID));
           qDebug() << "Room " + QString::number(roomID) + " requires dusting";
       }
       else {
           qry->prepare("UPDATE Rooms SET Dusting = " + QString::number(0) + " WHERE RoomID = " + QString::number(roomID));
           qDebug() << "Room " + QString::number(roomID) + " does not require dusting";
       }
       qry->exec();
       updateTable("SELECT * FROM Rooms");

    }
    else
    {
        QSqlError error = qry->lastError();
        qDebug() << "Failed to prepare query.";
        qDebug() << "Database says: " + error.databaseText();
    }
}

void DashBoard::elecEdit()
{
    QSqlQuery* qry = new QSqlQuery(db);
    int set = 0;
    if(qry->prepare("SELECT Electronics FROM Rooms WHERE RoomID = " + QString::number(roomID)) )
    {
       qry->exec();
       qry->first();
       set = qry->value(0).toInt();


       if(set == 0) {
           qry->prepare("UPDATE Rooms SET Electronics = " + QString::number(1) + " WHERE RoomID = " + QString::number(roomID));
           qDebug() << "Room " + QString::number(roomID) + " requires electronic maintenance";
       }
       else {
           qry->prepare("UPDATE Rooms SET Electronics = " + QString::number(0) + " WHERE RoomID = " + QString::number(roomID));
           qDebug() << "Room " + QString::number(roomID) + " does not require electronic maintenance";
       }
       qry->exec();
       updateTable("SELECT * FROM Rooms");

    }
    else
    {
        QSqlError error = qry->lastError();
        qDebug() << "Failed to prepare query.";
        qDebug() << "Database says: " + error.databaseText();
    }
}

void DashBoard::makeRoomUnavailable()
{
    QSqlQuery* qry = new QSqlQuery(db);
    int set = 0;

    if(qry->prepare("SELECT Status FROM Rooms WHERE RoomID = " + QString::number(roomID)))
    {
       qry->exec();
       qry->first();

       //  GRANT
       // SQL query to make the room unavaiable here
       qry->prepare("UPDATE Rooms SET Status = " + QString::number(0) + " WHERE RoomID = " + QString::number(roomID));

       qry->exec();
       updateTable("SELECT * FROM Rooms");

    }
    else
    {
        QSqlError error = qry->lastError();
        qDebug() << "Failed to prepare query.";
        qDebug() << "Database says: " + error.databaseText();
    }
}

void DashBoard::on_makeRes_clicked()
{
    Reservations* loadMePls = new Reservations(&db, roomNum);
    // Disable window resizing
    loadMePls->setFixedSize(loadMePls->size());
    loadMePls->setModal(1);
    loadMePls->show();
}
