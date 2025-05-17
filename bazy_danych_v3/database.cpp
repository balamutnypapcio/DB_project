#include "database.h"
#include <QCryptographicHash>

Database::Database(QObject *parent) : QObject(parent)
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("DB_tricount");
    db.setUserName("admin");
    db.setPassword("123");
    db.setPort(3306);
}

Database::~Database()
{
    if (db.isOpen())
        db.close();
}

Database& Database::getInstance()
{
    static Database instance;
    return instance;
}

bool Database::connectToDatabase()
{
    if (!db.open()) {
        qDebug() << "Database connection error:" << db.lastError().text();
        return false;
    }
    return initializeTables();
}

bool Database::initializeTables()
{
    QSqlQuery query;

    // Tworzenie tabeli users
    if (!query.exec("CREATE TABLE IF NOT EXISTS users ("
                    "username VARCHAR(50) PRIMARY KEY,"
                    "password VARCHAR(64) NOT NULL,"
                    "created_at DATETIME DEFAULT CURRENT_TIMESTAMP"
                    ")")) {
        qDebug() << "Error creating users table:" << query.lastError().text();
        return false;
    }

    return createInitialUser();
}

QString hashPassword(const QString& password)
{
    QByteArray hash = QCryptographicHash::hash(
        password.toUtf8(),
        QCryptographicHash::Sha256
        );
    return QString(hash.toHex());
}

bool Database::validateUser(const QString& username, const QString& password)
{
    QSqlQuery query;
    query.prepare("SELECT username FROM users WHERE username = ? AND password = ?");
    query.addBindValue(username);
    query.addBindValue(hashPassword(password));

    return query.exec() && query.next();
}

bool Database::registerUser(const QString& username, const QString& password)
{
    if (userExists(username)) {
        return false;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO users (username, password) VALUES (?, ?)");
    query.addBindValue(username);
    query.addBindValue(hashPassword(password));

    return query.exec();
}

bool Database::userExists(const QString& username)
{
    QSqlQuery query;
    query.prepare("SELECT username FROM users WHERE username = ?");
    query.addBindValue(username);

    return query.exec() && query.next();
}

bool Database::createInitialUser()
{
    if (!userExists("balamutnypapcio")) {
        return registerUser("balamutnypapcio", "testpass");
    }
    return true;
}
