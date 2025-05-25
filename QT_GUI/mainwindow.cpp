
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDateTime>
#include <QTimer>
#include <QInputDialog>
#include "addgroupdialog.h"


                                                                                           /**
 * @brief Konstruktor klasy MainWindow
 * @param parent Wskaźnik na widget rodzica
 *
 * Inicjalizuje interfejs użytkownika, konfiguruje połączenia sygnałów i slotów,
 * ustawia początkowy widok na ekran logowania oraz inicjalizuje timer do aktualizacji czasu.
 */
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , dateTimeTimer(new QTimer(this))
{
{
ui->setupUi(this);
setupConnections();

// Rozpocznij od strony logowania
ui->stackedWidget->setCurrentIndex(0);

// Konfiguracja timera dla aktualizacji daty/czasu
connect(dateTimeTimer, &QTimer::timeout, this, &MainWindow::updateDateTime);
dateTimeTimer->start(1000); // Aktualizuj co sekundę
updateDateTime(); // Początkowa aktualizacja
connect(ui->backButton, &QPushButton::clicked, this, &MainWindow::backButton1_clicked);
connect(ui->backButton_2, &QPushButton::clicked, this, &MainWindow::backButton2_clicked);
connect(ui->backButton_3, &QPushButton::clicked, this, &MainWindow::backButton3_clicked);
// Usuwamy tę linię:
// connect(ui->createButton, &QPushButton::clicked, this, &MainWindow::createButton_clicked);
}
}

/**
 * @brief Destruktor klasy MainWindow
 *
 * Zwalnia zasoby interfejsu użytkownika.
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief Konfiguruje połączenia sygnałów i slotów dla przycisków interfejsu
 *
 * Łączy sygnały kliknięć przycisków z odpowiednimi slotami, które realizują
 * funkcjonalności aplikacji, takie jak logowanie, nawigacja między widokami itp.
 */


void MainWindow::setupConnections()
{
    // Zmiana z InButton na handleSignInButton
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::handleSignInButton);

    connect(ui->buttonReturn, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(1);  // Powrót do listy grup
    });

    // Połącz przycisk Expenses z pokazywaniem wydatków
    connect(ui->buttonExpences, &QPushButton::clicked, this, [this]() {
        ui->StackedWidgetBalancesOrExpences->setCurrentIndex(1);
    });

    connect(ui->buttonBalances, &QPushButton::clicked, this, [this]() {
        ui->StackedWidgetBalancesOrExpences->setCurrentIndex(0);
    });

    // Połącz przycisk tworzenia grupy
    connect(ui->createButton, &QPushButton::clicked, this, &MainWindow::handleAddGroupButton);

    Database& db = Database::getInstance();
    connect(&db, &Database::groupsChanged, this, &MainWindow::onGroupsChanged);
    connect(&db, &Database::expensesChanged, this, &MainWindow::onExpensesChanged);
    connect(&db, &Database::expenseDetailsChanged, this, &MainWindow::onExpenseDetailsChanged);

    connect(ui->backButton_3, &QPushButton::clicked, this, &MainWindow::handleBackFromDetails);
}



/**
 * @brief Slot obsługujący powrót do strony z grupami
 */
void MainWindow::backButton1_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->groupsPage);
}

/**
 * @brief Slot obsługujący powrót do strony z grupami
 */
void MainWindow::backButton2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->groupsPage);
}

/**
 * @brief Slot obsługujący powrót do strony z grupami
 */
void MainWindow::backButton3_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->groupsPage);
}

/**
 * @brief Slot obsługujący powrót do strony z grupami
 */
void MainWindow::createButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->createGroupPage);
}


/**
 * @brief Ładuje listę grup użytkownika i wyświetla je jako przyciski
 *
 * Pobiera grupy z bazy danych dla zalogowanego użytkownika, usuwa istniejące przyciski
 * i tworzy nowe dla każdej grupy. Każdy przycisk jest połączony z funkcją obsługującą
 * wybór grupy.
 */
void MainWindow::loadUserGroups()
{
    // Wyczyść istniejące przyciski w scrollArea
    QWidget* scrollContent = ui->scrollAreaWidgetContents;
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(scrollContent->layout());

    // Usuń istniejące przyciski
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }

    // Pobierz grupy z bazy danych
    Database& db = Database::getInstance();
    userGroups = db.getUserGroups(currentUserId);

    // Utworzenie przycisków dla grup
    for (const auto& group : userGroups) {
        QPushButton* button = new QPushButton(group.second, scrollContent);
        button->setMinimumHeight(30);
        button->setMaximumHeight(50);
        button->setStyleSheet(
            "QPushButton {"
            "min-width: 100px;"
            "min-height: 30px;"
            "max-height: 30px;"
            "background-color: #4169E1; /* Royal Blue - jaśniejszy odcień */"
            "border-radius: 10px;"
            "color: white;"
            "font-size: 14pt;"
            "font-weight: bold;"
            "}"

            "QPushButton:checked {"
            "min-width: 90px; /* mniejszy rozmiar gdy aktywny */"
            "max-width: 90px;"
            "min-height: 90px;"
            "max-height: 90px;"
            "background-color: #1e3c8c; /* ciemniejszy odcień niebieskiego */"
            "border-radius: 18px; /* proporcjonalnie mniejszy radius */"
            "font-size: 12pt; /* mniejsza czcionka */"
            "}"

            "QPushButton:hover {"
            "background-color: #5a7ee5; /* jaśniejszy przy hover */"
            "}"

            "QPushButton:pressed {"
            "background-color: #0d1b3f; /* najciemniejszy przy wciśnięciu */"
            "}");

        // Przekazujemy ID i nazwę grupy w lambdzie
        connect(button, &QPushButton::clicked, this, [this, groupId = group.first, groupName = group.second]() {
            handleGroupSelection(groupId, groupName);
        });

        layout->addWidget(button);
    }

    // Dodaj spacer na końcu
    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

/**
 * @brief Aktualizuje wyświetlanie aktualnej daty i czasu
 *
 * Funkcja wywoływana cyklicznie przez timer. Pobiera aktualny czas,
 * formatuje go i wyświetla w konsoli debugowania.
 */
void MainWindow::updateDateTime()
{
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    qDebug() << "Current Date and Time (UTC - YYYY-MM-DD HH:MM:SS formatted):" << currentDateTime;
    qDebug() << "Current User's Login:" << (currentUser.isEmpty() ? "Not logged in" : currentUser);
}

/**
 * @brief Obsługuje kliknięcie przycisku logowania
 *
 * Weryfikuje wprowadzoną nazwę użytkownika, sprawdza ją w bazie danych.
 * Jeśli weryfikacja się powiedzie, przechodzi do widoku list grup użytkownika.
 */
void MainWindow::handleSignInButton()
{
    QString username = ui->usernameInsert->text();

    if (username.isEmpty()) {
        QMessageBox* msgBox = createStyledMessageBox(QMessageBox::Warning,
                                                     "Błąd logowania", "Proszę wprowadzić nazwę użytkownika");
        msgBox->exec();
        delete msgBox;
        return;
    }

    Database& db = Database::getInstance();
    if (db.validateUser(username)) {
        currentUser = username;
        currentUserId = db.getUserId(username);
        qDebug() << "Login successful. Username:" << username << "UserID:" << currentUserId; // dodane logowanie

        if (currentUserId == -1) {
            QMessageBox* msgBox = createStyledMessageBox(QMessageBox::Warning,
                                                         "Błąd logowania", "Nie można pobrać ID użytkownika");
            msgBox->exec();
            delete msgBox;
        } else {
            loadUserGroups();
            ui->stackedWidget->setCurrentIndex(1);  // przejście do widoku grup
        }
    } else {
        QMessageBox* msgBox = createStyledMessageBox(QMessageBox::Warning,
                                                     "Błąd logowania", "Nieprawidłowa nazwa użytkownika");
        msgBox->exec();
        delete msgBox;
        ui->usernameInsert->clear();
        ui->passwordInsert->clear();
    }
}
/**
 * @brief Obsługuje dodawanie nowej grupy
 *
 * Wyświetla informację o dodawaniu nowej grupy dla zalogowanego użytkownika.
 */
void MainWindow::handleAddGroupButton()
{
    AddGroupDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Database& db = Database::getInstance();
        QString groupName = dialog.getGroupName();

        if (!db.addGroup(groupName)) {
            QMessageBox* errorBox = createStyledMessageBox(
                QMessageBox::Warning,
                "Błąd",
                "Nie udało się utworzyć grupy. Sprawdź połączenie z bazą danych."
                );
            errorBox->exec();
            delete errorBox;
        }
    }
}

/**
 * @brief Obsługuje powrót do widoku listy grup
 *
 * Przełącza interfejs na widok listy grup.
 */
void MainWindow::handleReturnButton()
{
    ui->stackedWidget->setCurrentIndex(1);
}

/**
 * @brief Obsługuje wybór grupy przez użytkownika
 * @param groupId Identyfikator wybranej grupy
 * @param groupName Nazwa wybranej grupy
 *
 * Ustawia aktualnie wybraną grupę, ładuje wydatki dla tej grupy
 * i przełącza widok na stronę z wydatkami.
 */
void MainWindow::handleGroupSelection(int groupId, const QString& groupName)
{
    currentGroupId = groupId;
    ui->labelExpenseName->setText(groupName);
    loadExpenses();
    ui->stackedWidget->setCurrentIndex(5);  // Przejście do strony z wydatkami
}

/**
 * @brief Ładuje wydatki dla aktualnie wybranej grupy
 *
 * Pobiera listę wydatków z bazy danych dla bieżącej grupy i tworzy
 * przyciski reprezentujące poszczególne wydatki w interfejsie.
 */
void MainWindow::loadExpenses()
{
    // Pobierz layout ze scroll area wydatków
    QWidget* scrollContent = ui->scrollAreaWidgetContents_3;
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(scrollContent->layout());

    // Wyczyść istniejące przyciski
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }

    // Pobierz wydatki z bazy danych
    Database& db = Database::getInstance();
    QVector<Database::ExpenseData> expenses = db.getExpensesForGroup(currentGroupId);

    // Dodaj przyciski dla każdego wydatku
    for (const auto& expense : expenses) {
        ExpenseButton* button = new ExpenseButton(
            expense.id,
            expense.date,
            expense.description,
            expense.paidByUsername,
            expense.amount,
            scrollContent
            );

        connect(button, &ExpenseButton::clicked, this, [this, id = expense.id]() {
            handleExpenseClick(id);
        });

        layout->addWidget(button);
    }

    // Dodaj spacer na końcu
    layout->addStretch();
}

/**
 * @brief Obsługuje kliknięcie przycisku reprezentującego wydatek
 * @param expenseId Identyfikator klikniętego wydatku
 *
 * Funkcja wywoływana po kliknięciu przycisku wydatku, obecnie tylko loguje
 * informację o kliknięciu w konsoli debugowania.
 */

// W mainwindow.cpp zostawiamy tylko jedną implementację:
void MainWindow::handleExpenseClick(int expenseId)
{
    Database& db = Database::getInstance();
    auto expenseData = db.getExpenseDetails(expenseId);

    // Aktualizacja UI
    ui->expsenseNameLabel->setText("Name: " + expenseData.description);
    ui->expenseNameTextEdit->setPlainText(QString::number(expenseData.amount, 'f', 2) + " PLN");
    ui->createExpenseLabel->setText("Date: " + expenseData.date.toString("yyyy-MM-dd hh:mm"));

    // Przełączenie widoku
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::onGroupsChanged()
{
    // Odśwież listę grup
    loadGroups();
}

void MainWindow::onExpensesChanged(int groupId)
{
    // Odśwież wydatki jeśli jesteśmy w odpowiedniej grupie
    if (currentGroupId == groupId) {
        loadExpenses();
    }
}

void MainWindow::onExpenseDetailsChanged(int expenseId)
{
    // Odśwież szczegóły wydatku jeśli jest aktualnie wyświetlany
    if (currentExpenseId == expenseId) {
        loadExpenseDetails(expenseId);
    }
}

void MainWindow::handleAddExpenseButton()
{
    AddExpenseDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Database& db = Database::getInstance();
        bool success = false;

        int currentUserId = db.getCurrentUserId();

        if (currentUserId > 0) {
            QSqlQuery query(db.getDatabase());
            query.prepare("CALL add_equal_expense(?, ?, ?, ?)");
            query.addBindValue(currentGroupId);
            query.addBindValue(dialog.getDescription());
            query.addBindValue(dialog.getAmount());
            query.addBindValue(currentUserId);

            success = query.exec();
        }

        if (!success) {
            QMessageBox* errorBox = createStyledMessageBox(QMessageBox::Warning,
                                                           "Błąd",
                                                           "Nie udało się dodać wydatku. Sprawdź połączenie z bazą danych.");
            errorBox->exec();
            delete errorBox;
        }
    }
}


void MainWindow::loadExpenseDetails(int expenseId)
{
    Database& db = Database::getInstance();
    auto expenseData = db.getExpenseDetails(expenseId);
    auto participants = db.getExpenseParticipants(expenseId);

    // Ustawiamy wartości w UI używając istniejących nazw elementów
    ui->expsenseNameLabel->setText("Name: " + expenseData.description);
    ui->expenseNameTextEdit->setPlainText(QString::number(expenseData.amount, 'f', 2) + " PLN");
    ui->createExpenseLabel->setText("Date: " + expenseData.date.toString("yyyy-MM-dd hh:mm"));

    // Przełączamy widok
    ui->stackedWidget->setCurrentIndex(4);
}


void MainWindow::handleBackFromDetails()
{
    ui->stackedWidget->setCurrentWidget(ui->expencesPage);
}


void MainWindow::loadGroups() {
    QWidget* scrollContent = ui->scrollAreaWidgetContents;
    QVBoxLayout* layout = qobject_cast<QVBoxLayout*>(scrollContent->layout());

    // Wyczyść istniejące przyciski
    QLayoutItem* item;
    while ((item = layout->takeAt(0)) != nullptr) {
        if (QWidget* widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }

    // Pobierz grupy z bazy danych
    Database& db = Database::getInstance();
    QSqlQuery query(db.getDatabase());

    if (query.exec("SELECT id, name FROM groups")) {
        while (query.next()) {
            int groupId = query.value(0).toInt();
            QString groupName = query.value(1).toString();

            // Utwórz przycisk dla grupy
            QPushButton* button = new QPushButton(groupName, scrollContent);
            button->setMinimumHeight(30);
            button->setMaximumHeight(50);
            button->setStyleSheet(
                "QPushButton {"
                "    min-width: 100px;"
                "    min-height: 30px;"
                "    max-height: 30px;"
                "    background-color: #4169E1;"
                "    border-radius: 10px;"
                "    color: white;"
                "    font-size: 14pt;"
                "    font-weight: bold;"
                "}"
                "QPushButton:hover {"
                "    background-color: #5a7ee5;"
                "}"
                "QPushButton:pressed {"
                "    background-color: #0d1b3f;"
                "}"
                );

            // Połącz przycisk z handlerem
            connect(button, &QPushButton::clicked, this, [this, groupId, groupName]() {
                handleGroupSelection(groupId, groupName);
            });

            layout->addWidget(button);
        }

        // Dodaj spacer na końcu
        layout->addStretch();
    } else {
        qDebug() << "Błąd podczas ładowania grup:" << query.lastError().text();
    }
}
QMessageBox* MainWindow::createStyledMessageBox(QMessageBox::Icon icon,
                                                const QString& title,
                                                const QString& text)
{
    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setIcon(icon);
    msgBox->setWindowTitle(title);
    msgBox->setText(text);
    msgBox->setStyleSheet(
        "QMessageBox {"
        "    background-color: #FFFFFF;"
        "}"
        "QMessageBox QLabel {"
        "    color: #000000;"
        "    font-size: 12pt;"
        "    min-width: 200px;"
        "}"
        "QPushButton {"
        "    min-width: 100px;"
        "    min-height: 30px;"
        "    background-color: #4169E1;"
        "    border-radius: 10px;"
        "    color: white;"
        "    font-size: 12pt;"
        "    font-weight: bold;"
        "    padding: 5px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #5a7ee5;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #0d1b3f;"
        "}"
        );
    return msgBox;
}
