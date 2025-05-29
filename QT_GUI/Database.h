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
    int createGroup(QString& name, int createdBy, QString& users);

    struct ExpenseData {
        int id;
        QDateTime date;
        QString description;
        QString paidByUsername;
        double amount;
    };

    struct ParticipantData {
        QString username;
        double share;
        bool isPaid;
    };

    struct expenseSharesData{
        int expesneId;
        int userId;
        QString userName;
        double userShare;
    };

    QVector<ExpenseData> getExpensesForGroup(int groupId);
    ExpenseData getExpenseDetails(int expenseId);
    QVector<ParticipantData> getExpenseParticipants(int expenseId);
    QVector<expenseSharesData> getExpenseShares(int expenseId);
    void addExpenseToGroup(int groupId, QString& paidById, double amount,
                                     const QString& description, const QString& participantsShares);
    void deleteExpenseById(int expenseId);
    void deleteGroupById(int groupId);



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
    const QString DATABASE_NAME = "trickount_DB";
    const QString DATABASE_HOST = "localhost";
    const QString DATABASE_USER = "qtuser";
    const QString DATABASE_PASSWORD = "qtpassword";
};
#endif // DATABASE_H
