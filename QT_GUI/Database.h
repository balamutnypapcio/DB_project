#ifndef DATABASE_H
#define DATABASE_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QString>
#include <QDebug>
#include <QDateTime>
#include <QObject>

class Database : public QObject
{
   Q_OBJECT
signals:
    void groupsChanged();              // Sygnał emitowany gdy zmienią się grupy
    void expensesChanged(int groupId); // Sygnał emitowany gdy zmienią się wydatki w grupie
    void expenseDetailsChanged(int expenseId); // Sygnał emitowany gdy zmienią się szczegóły wydatku

public:
    static Database& getInstance();
    bool isConnected() const;
    QSqlDatabase getDatabase() const;
    int getCurrentUserId() const { return currentUserId; }


    // Metoda do wykonywania zapytań
    QSqlQuery executeQuery(const QString& queryStr);
    QVector<QPair<int, QString>> getUserGroups(int userId);
    bool validateUser(const QString& username);
    int getUserId(const QString& username);

    // Metody do zarządzania członkami grupy
    bool addGroupMember(int groupId, const QString& username);
    bool removeGroupMember(int groupId, const QString& username);
    QVector<QString> getGroupMembers(int groupId);
    bool userExists(const QString& username);
    int getLastInsertedGroupId();


    // Nowe metody do wywoływania przy zmianach
    bool addGroup(const QString& name);
    bool addExpense(int groupId, const QString& description, double amount);
    bool updateExpense(int expenseId, const QString& description, double amount);


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

    QVector<ExpenseData> getExpensesForGroup(int groupId);
    ExpenseData getExpenseDetails(int expenseId);
    QVector<ParticipantData> getExpenseParticipants(int expenseId);

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
    int currentUserId = -1;

    void notifyGroupsChanged();
    void notifyExpensesChanged(int groupId);
    void notifyExpenseDetailsChanged(int expenseId);
};
#endif // DATABASE_H
