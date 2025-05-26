#include "Database.h"

Database::Database()
    : QObject(nullptr)  // Dodaj inicjalizację QObject
    , connected(false)
    , currentUserId(-1)
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

/**
 * @brief Pobiera szczegółowe dane wydatku na podstawie jego identyfikatora
 * @param expenseId Identyfikator wydatku
 * @return Struktura z danymi wydatku
 */
Database::ExpenseData Database::getExpenseDetails(int expenseId)
{
    ExpenseData expenseData;
    expenseData.id = expenseId;

    QString queryStr = "SELECT e.date, e.description, u.username, e.amount "
                       "FROM expenses e "
                       "JOIN users u ON e.paid_by = u.id "
                       "WHERE e.id = :expenseId";

    QSqlQuery query(db);
    query.prepare(queryStr);
    query.bindValue(":expenseId", expenseId);

    if (query.exec() && query.next()) {
        expenseData.date = query.value(0).toDateTime();
        expenseData.description = query.value(1).toString();
        expenseData.paidByUsername = query.value(2).toString();
        expenseData.amount = query.value(3).toDouble();
    } else {
        qDebug() << "Failed to get expense details:" << query.lastError().text();
    }

    return expenseData;
}

/**
 * @brief Pobiera listę uczestników dla danego wydatku
 * @param expenseId Identyfikator wydatku
 * @return Wektor struktur z danymi uczestników
 */
QVector<Database::ParticipantData> Database::getExpenseParticipants(int expenseId)
{
    QVector<ParticipantData> participants;

    QString queryStr = "SELECT u.username, ep.share, ep.is_paid "
                       "FROM expense_participants ep "
                       "JOIN users u ON ep.user_id = u.id "
                       "WHERE ep.expense_id = :expenseId";

    QSqlQuery query(db);
    query.prepare(queryStr);
    query.bindValue(":expenseId", expenseId);

    if (query.exec()) {
        while (query.next()) {
            ParticipantData participant;
            participant.username = query.value(0).toString();
            participant.share = query.value(1).toDouble();
            participant.isPaid = query.value(2).toBool();
            participants.append(participant);
        }
    } else {
        qDebug() << "Failed to get expense participants:" << query.lastError().text();
    }

    return participants;
}
bool Database::addGroup(const QString& name)
{
    if (currentUserId == -1) {
        qDebug() << "Error: No user is currently logged in";
        return false;
    }

    QSqlQuery query(db);
    query.prepare("CALL create_group(:name, :userId)");
    query.bindValue(":name", name);
    query.bindValue(":userId", currentUserId);

    bool success = query.exec();
    if (!success) {
        qDebug() << "SQL Error in addGroup:" << query.lastError().text();
        qDebug() << "Parameters - name:" << name << "userId:" << currentUserId;
    } else {
        notifyGroupsChanged();
    }
    return success;
}

bool Database::addExpense(int groupId, const QString& description, double amount)
{
    QSqlQuery query(db);
    query.prepare("CALL add_equal_expense(:groupId, :description, :amount, :userId)");
    query.bindValue(":groupId", groupId);
    query.bindValue(":description", description);
    query.bindValue(":amount", amount);
    query.bindValue(":userId", currentUserId);

    bool success = query.exec();
    if (success) {
        notifyExpensesChanged(groupId);
    }
    return success;
}

void Database::notifyGroupsChanged()
{
    emit groupsChanged();
}

void Database::notifyExpensesChanged(int groupId)
{
    emit expensesChanged(groupId);
}

void Database::notifyExpenseDetailsChanged(int expenseId)
{
    emit expenseDetailsChanged(expenseId);
}


bool Database::userExists(const QString& username)
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

bool Database::addGroupMember(int groupId, const QString& username)
{
    if (!userExists(username)) {
        return false;
    }

    QSqlQuery query(db);
    query.prepare("CALL add_group_member(:groupId, (SELECT id FROM users WHERE username = :username))");
    query.bindValue(":groupId", groupId);
    query.bindValue(":username", username);

    bool success = query.exec();
    if (success) {
        notifyGroupsChanged();
    } else {
        qDebug() << "Failed to add group member:" << query.lastError().text();
    }
    return success;
}

bool Database::removeGroupMember(int groupId, const QString& username)
{
    QSqlQuery query(db);
    query.prepare("DELETE FROM group_members WHERE group_id = :groupId AND user_id = (SELECT id FROM users WHERE username = :username)");
    query.bindValue(":groupId", groupId);
    query.bindValue(":username", username);

    bool success = query.exec();
    if (success) {
        notifyGroupsChanged();
    } else {
        qDebug() << "Failed to remove group member:" << query.lastError().text();
    }
    return success;
}

QVector<QString> Database::getGroupMembers(int groupId)
{
    QVector<QString> members;
    QSqlQuery query(db);
    query.prepare(
        "SELECT u.username "
        "FROM users u "
        "INNER JOIN group_members gm ON u.id = gm.user_id "
        "WHERE gm.group_id = :groupId"
        );
    query.bindValue(":groupId", groupId);

    if (query.exec()) {
        while (query.next()) {
            members.append(query.value("username").toString());
        }
    } else {
        qDebug() << "Failed to get group members:" << query.lastError().text();
    }

    return members;
}


int Database::getLastInsertedGroupId()
{
    QSqlQuery query(db);
    if (query.exec("SELECT LAST_INSERT_ID()") && query.next()) {
        return query.value(0).toInt();
    }
    return -1;
}


bool Database::addUser(const QString& username)
{
    // Najpierw sprawdź czy użytkownik już nie istnieje
    QSqlQuery checkQuery(db);
    checkQuery.prepare("SELECT id FROM users WHERE username = :username AND is_deleted = FALSE");
    checkQuery.bindValue(":username", username);

    if (!checkQuery.exec()) {
        qDebug() << "Query Error (check user):" << checkQuery.lastError().text();
        return false;
    }

    // Jeśli użytkownik już istnieje, zwróć false
    if (checkQuery.next()) {
        return false;
    }

    // Dodaj nowego użytkownika
    QSqlQuery addQuery(db);
    addQuery.prepare("INSERT INTO users (username, created_at) VALUES (:username, NOW())");
    addQuery.bindValue(":username", username);

    if (!addQuery.exec()) {
        qDebug() << "Query Error (add user):" << addQuery.lastError().text();
        return false;
    }

    return true;
}
