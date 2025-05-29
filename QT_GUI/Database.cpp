#include "Database.h"
#include "QMessageBox"

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

/**
 * @brief Dodaje grupe i uczestnikow do BD za pomoca procedury
 * @param name Nazwa grupy
 * @param users Użytkownicy, którzy zostaną dodani do grupy
 * @param createdBy Przez kogo utworzone
 * @return 0
 */
int Database::createGroup(QString& name, int createdBy, QString& users){


    QSqlQuery query;
    query.prepare("CALL create_group(:group_name, :created_by, :users)");
    query.bindValue(":group_name", name);
    query.bindValue(":created_by", createdBy);
    query.bindValue(":users", users);

    if (!query.exec()) {
        qDebug() << "Błąd wykonania procedury:" << query.lastError().text();
    } else {
        qDebug() << "Grupa utworzona poprawnie!";
    }

    return 0;

}

QVector<Database::expenseSharesData> Database::getExpenseShares(int expenseId){

    QVector<Database::expenseSharesData> result;

    QSqlQuery query;
    query.prepare(R"(
        SELECT es.expense_id, u.id AS user_id, u.username, es.share
        FROM expense_shares es
        JOIN users u ON es.user_id = u.id
        WHERE es.expense_id = :id
    )");
    query.bindValue(":id", expenseId);

    if (query.exec()) {
        while (query.next()) {
            expenseSharesData data;
            data.expesneId = query.value("expense_id").toInt();
            data.userId = query.value("user_id").toInt();
            data.userName = query.value("username").toString();
            data.userShare = query.value("share").toDouble();
            result.push_back(data);
        }
    } else {
        qDebug() << "Błąd zapytania:" << query.lastError().text();
    }

    return result;

}


void Database::addExpenseToGroup(int groupId, QString& paidBy, double amount,
                                 const QString& description,
                                 const QString& participantsShares)
{
    QSqlQuery query;

    query.prepare("CALL add_expense_to_group(:group_id, :paid_by, :amount, :description, :shares)");
    query.bindValue(":group_id", groupId);
    query.bindValue(":paid_by", paidBy);
    query.bindValue(":amount", amount);
    query.bindValue(":description", description);
    query.bindValue(":shares", participantsShares);

    if (!query.exec()) {
        qDebug() << "Błąd wykonania procedury:" << query.lastError().text();
    } else {
        qDebug() << "Wydatek dodany poprawnie!";
    }
}

void Database::deleteExpenseById(int expenseId)
{
    QSqlQuery query;

    query.prepare("CALL delete_expense_by_id(:expense_id)");
    query.bindValue(":expense_id", expenseId);

    if (!query.exec()) {
        qDebug() << "Błąd usuwania wydatku po ID:" << query.lastError().text();
    } else {
        qDebug() << "Wydatek o ID" << expenseId << "usunięty poprawnie!";
    }
}



void Database::deleteGroupById(int groupId)
{
    QSqlQuery query;
    query.prepare("CALL delete_group_by_id(:group_id)");
    query.bindValue(":group_id", groupId);

    if (!query.exec()) {
        qDebug() << "Błąd usuwania grupy:" << query.lastError().text();
        QMessageBox::critical(nullptr, "Błąd", "Nie udało się usunąć grupy z bazy danych.");
    } else {
        qDebug() << "Grupa o ID" << groupId << "usunięta pomyślnie.";
        QMessageBox::information(nullptr, "Sukces", "Grupa została usunięta.");
    }
}





