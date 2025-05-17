#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDateTime>
#include <QTimer>

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
}

MainWindow::~MainWindow()
{
    delete ui;
}

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
}


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
            "font-size: 12pt;"
            "color: #000000;"
            "background-color: #FFFFFF;"
            );

        // Przekazujemy ID i nazwę grupy w lambdzie
        connect(button, &QPushButton::clicked, this, [this, groupId = group.first, groupName = group.second]() {
            handleGroupSelection(groupId, groupName);
        });

        layout->addWidget(button);
    }

    // Dodaj spacer na końcu
    layout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));
}

void MainWindow::updateDateTime()
{
    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");
    qDebug() << "Current Date and Time (UTC - YYYY-MM-DD HH:MM:SS formatted):" << currentDateTime;
    qDebug() << "Current User's Login:" << (currentUser.isEmpty() ? "Not logged in" : currentUser);
}

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


// void MainWindow::handleGroupSelection(const QString& groupName)
// {
//     ui->labelExpenseName->setText(groupName);
//     ui->stackedWidget->setCurrentIndex(2);
// }

void MainWindow::handleAddGroupButton()
{
    QMessageBox::information(this, "Add Group",
                             QString("Adding new group for user: %1").arg(currentUser));
}

void MainWindow::handleReturnButton()
{
    ui->stackedWidget->setCurrentIndex(1);
}



void MainWindow::handleGroupSelection(int groupId, const QString& groupName)
{
    currentGroupId = groupId;
    ui->labelExpenseName->setText(groupName);
    loadExpenses();
    ui->stackedWidget->setCurrentIndex(2);  // Przejście do strony z wydatkami
}

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

void MainWindow::handleExpenseClick(int expenseId)
{
    // Tu dodasz obsługę kliknięcia w wydatek
    qDebug() << "Clicked expense with ID:" << expenseId;
}
