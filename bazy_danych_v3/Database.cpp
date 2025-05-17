#include "Database.h"

Database::Database() : connected(false)
{
    connected = connectToDatabase();
}

Database::~Database()
{
    if(db.isOpen()) {
        db.close();
    }
}

Database& Database::getInstance()
{
    static Database instance;
    return instance;
}

bool Database::connectToDatabase()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(DATABASE_HOST);
    db.setDatabaseName(DATABASE_NAME);
    db.setUserName(DATABASE_USER);
    db.setPassword(DATABASE_PASSWORD);

    if (!db.open()) {
        qDebug() << "Database Error:" << db.lastError().text();
        return false;
    }

    qDebug() << "Database connected successfully!";
    return true;
}

bool Database::isConnected() const
{
    return connected && db.isOpen();
}

QSqlDatabase Database::getDatabase() const
{
    return db;
}

// Dodaj implementację validateUser
bool Database::validateUser(const QString& username)
{
    QSqlQuery query(db);
    query.prepare("SELECT id FROM users WHERE username = :username AND is_deleted = FALSE");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Query Error:" << query.lastError().text();
        return false;
    }

    return query.next();
}

// Implementacja getUserGroups
QVector<QPair<int, QString>> Database::getUserGroups(int userId)
{
    QVector<QPair<int, QString>> groups;
    QSqlQuery query(db);

    query.prepare(
        "SELECT g.id, g.name "
        "FROM group_table g "
        "INNER JOIN group_members gm ON g.id = gm.group_id "
        "WHERE gm.user_id = :userId "
        "ORDER BY g.created_at DESC"
        );

    query.bindValue(":userId", userId);

    if (!query.exec()) {
        qDebug() << "Error fetching user groups:" << query.lastError().text();
        return groups;
    }

    while (query.next()) {
        groups.append({query.value("id").toInt(), query.value("name").toString()});
    }

    return groups;
}


int Database::getUserId(const QString& username)
{
    QSqlQuery query(db);
    query.prepare("SELECT id FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (!query.exec()) {
        qDebug() << "Query Error:" << query.lastError().text();
        return -1;
    }

    if (query.next()) {
        return query.value("id").toInt();
    }

    return -1;
}



QVector<Database::ExpenseData> Database::getExpensesForGroup(int groupId)
{
    QVector<ExpenseData> expenses;
    QSqlQuery query(db);

    // Pobierz wydatki wraz z nazwą użytkownika który zapłacił
    query.prepare(
        "SELECT e.id, e.date, e.description, u.username, e.amount "
        "FROM expenses e "
        "INNER JOIN users u ON e.paid_by = u.id "
        "WHERE e.group_id = :groupId "
        "ORDER BY e.date DESC"  // Sortowanie od najnowszych
        );

    query.bindValue(":groupId", groupId);

    if (!query.exec()) {
        qDebug() << "Error fetching expenses:" << query.lastError().text();
        return expenses;
    }

    while (query.next()) {
        ExpenseData expense;
        expense.id = query.value("id").toInt();
        expense.date = query.value("date").toDateTime();
        expense.description = query.value("description").toString();
        expense.paidByUsername = query.value("username").toString();
        expense.amount = query.value("amount").toDouble();
        expenses.append(expense);
    }

    return expenses;
}
