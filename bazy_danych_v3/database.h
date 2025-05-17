#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QDateTime>

class Database : public QObject
{
    Q_OBJECT
public:
    static Database& getInstance();
    bool connectToDatabase();

    // Metody autentykacji
    bool validateUser(const QString& username, const QString& password);
    bool registerUser(const QString& username, const QString& password);
    bool userExists(const QString& username);
    bool createInitialUser();

private:
    explicit Database(QObject *parent = nullptr);
    ~Database();
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    QSqlDatabase db;
    bool initializeTables();
};

#endif // DATABASE_H
