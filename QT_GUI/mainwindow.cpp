
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDateTime>
#include <QTimer>

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
    connect(ui->createButton, &QPushButton::clicked, this, &MainWindow::createButton_clicked);
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
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::handleSignInButton);
    connect(ui->buttonReturn, &QPushButton::clicked, this, [this]() {
        ui->stackedWidget->setCurrentIndex(1);  // Powrót do listy grup
    });

    // Połącz przycisk Expenses z pokazywaniem wydatków
    connect(ui->buttonExpences, &QPushButton::clicked, this, [this]() {
        ui->StackedWidgetBalancesOrExpences->setCurrentIndex(1);
        //loadExpenses();
    });
    connect(ui->buttonBalances, &QPushButton::clicked, this, [this]() {
        ui->StackedWidgetBalancesOrExpences->setCurrentIndex(0);
    });

    Database& db = Database::getInstance();
    connect(&db, &Database::groupsChanged, this, &MainWindow::onGroupsChanged);
    connect(&db, &Database::expensesChanged, this, &MainWindow::onExpensesChanged);
    connect(&db, &Database::expenseDetailsChanged, this, &MainWindow::onExpenseDetailsChanged);
    connect(ui->addExpenseButton, &QPushButton::clicked,
            this, &MainWindow::handleAddExpenseButton);

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
        QMessageBox::warning(this, "Login Error", "Please enter username");
        return;
    }

    Database& db = Database::getInstance();
    if (db.validateUser(username)) {
        currentUser = username;
        currentUserId = db.getUserId(username);  // Pobierz ID użytkownika

        if (currentUserId != -1) {
            // Załaduj grupy użytkownika
            loadUserGroups();

            // Przejdź do strony z grupami
            ui->stackedWidget->setCurrentIndex(1);
        } else {
            QMessageBox::warning(this, "Login Error", "Could not get user ID");
        }
    } else {
        QMessageBox::warning(this, "Login Error", "Invalid username");
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
    QMessageBox::information(this, "Add Group",
                             QString("Adding new group for user: %1").arg(currentUser));
    bool ok;
    QString name = QInputDialog::getText(this, "Add Group",
                                         "Enter group name:", QLineEdit::Normal,
                                         "", &ok);
    if (ok && !name.isEmpty()) {
        Database& db = Database::getInstance();
        if (db.addGroup(name)) {
            // Nie musimy ręcznie odświeżać - sygnał groupsChanged zrobi to za nas
        } else {
            QMessageBox::warning(this, "Error", "Failed to create group");
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
void MainWindow::handleExpenseClick(int expenseId)
{
    ui->stackedWidget->setCurrentIndex(4);  // Zakładam, że strona szczegółów ma indeks 6

    qDebug() << "Showing details for expense with ID:" << expenseId;
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
        if (db.addExpense(currentGroupId, dialog.getDescription(), dialog.getAmount())) {
            // Nie musimy ręcznie odświeżać - sygnał expensesChanged zrobi to za nas
        } else {
            QMessageBox::warning(this, "Error", "Failed to add expense");
        }
    }
}


void MainWindow::handleAddExpenseButton()
{
    AddExpenseDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        Database& db = Database::getInstance();
        bool success = false;

        // Pobierz ID aktualnie zalogowanego użytkownika
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

        if (success) {
            loadExpenses(); // Odśwież listę wydatków
        } else {
            QMessageBox::warning(
                this,
                "Błąd",
                "Nie udało się dodać wydatku. Sprawdź połączenie z bazą danych."
                );
        }
    }
}
