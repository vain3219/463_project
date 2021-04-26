#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QString>
#include <QSqlDatabase>
#include <QSqlQuery>
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
       } else {
          qDebug() << "Database: connection ok";
       }
    };

    QSqlQuery* rawQuery(QString rawString)
    {
        return new QSqlQuery(m_db.exec(rawString + ";"));
    }

    void AddReservation();
    void RemoveReservation();

    void AddHouseKeeping();
    void RemoveHouseKeeping();

    bool isOpen()
    {
        return m_db.isOpen();
    };

    bool closeDB()
    {
        m_db.close();
        return isOpen();
    }

    bool openDB()
    {
        if(!isOpen()) {
            m_db.open();
        }
        return isOpen();
    }

    QSqlDatabase m_db;
private:

};

#endif // DBMANAGER_H
