#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QDebug>
#include <QDateTime>

class Database
{
public:
    static Database& getInstance();
    bool isConnected() const;
    QSqlDatabase getDatabase() const;

    // Metoda do wykonywania zapytań
    QSqlQuery executeQuery(const QString& queryStr);
    QVector<QPair<int, QString>> getUserGroups(int userId);
    bool validateUser(const QString& username);
    int getUserId(const QString& username);
    struct ExpenseData {
        int id;
        QDateTime date;
        QString description;
        QString paidByUsername;
        double amount;
    };

    QVector<ExpenseData> getExpensesForGroup(int groupId);

private:
    Database(); // Konstruktor prywatny (Singleton)
    ~Database();

    // Zabraniamy kopiowania i przypisania
    Database(const Database&) = delete;
    Database& operator=(const Database&) = delete;

    bool connectToDatabase();
    QSqlDatabase db;
    bool connected;

    // Stałe konfiguracyjne
    const QString DATABASE_NAME = "DB_tricount";
    const QString DATABASE_HOST = "localhost";
    const QString DATABASE_USER = "admin";
    const QString DATABASE_PASSWORD = "123";
};

#endif // DATABASE_H
