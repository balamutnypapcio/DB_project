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
    // Połączenia dla strony logowania
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::handleSignInButton);

    // Połączenia dla strony grup
    connect(ui->pushButton_2, &QPushButton::clicked, this, [this]() {
        handleGroupSelection("Beer Night");
    });
    connect(ui->pushButton_3, &QPushButton::clicked, this, [this]() {
        handleGroupSelection("Vacations");
    });
    connect(ui->pushButton_4, &QPushButton::clicked, this, [this]() {
        handleGroupSelection("Apartment Expenses");
    });

    connect(ui->createButton, &QPushButton::clicked, this, &MainWindow::handleAddGroupButton);
    connect(ui->buttonReturn, &QPushButton::clicked, this, &MainWindow::handleReturnButton);
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
    QString password = ui->passwordInsert->text();

    if (username.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Login Error", "Please enter username and password");
        return;
    }

    if (Database::getInstance().validateUser(username, password)) {
        currentUser = username;
        ui->stackedWidget->setCurrentIndex(1);
        updateDateTime();
    } else {
        QMessageBox::warning(this, "Login Error", "Invalid username or password");
        ui->passwordInsert->clear();
        ui->passwordInsert->setFocus();
    }
}

void MainWindow::handleGroupSelection(const QString& groupName)
{
    ui->labelExpenseName->setText(groupName);
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::handleAddGroupButton()
{
    QMessageBox::information(this, "Add Group",
                             QString("Adding new group for user: %1").arg(currentUser));
}

void MainWindow::handleReturnButton()
{
    ui->stackedWidget->setCurrentIndex(1);
}
