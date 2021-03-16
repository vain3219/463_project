#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QDebug>

class DbManager
{
public:
    DbManager(const QString& path) {
       m_db = QSqlDatabase::addDatabase("QSQLITE");
       m_db.setDatabaseName(path);

       if (!m_db.open())
       {
          qDebug() << "Error: connection with database fail";
       }
       else
       {
          qDebug() << "Database: connection ok";
       }
    };

    void AddReservation();
    void RemoveReservation();

    void AddHouseKeeping();
    void RemoveHouseKeeping();

    bool isOpen() {
        return m_db.isOpen();
    };

private:
    QSqlDatabase m_db;
};

#endif // DBMANAGER_H
