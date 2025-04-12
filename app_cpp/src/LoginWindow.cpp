#include "LoginWindow.h"
#include "GroupsWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QFrame>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlError>

LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Ustawienia okna
    setWindowTitle("Logowanie do systemu");
    resize(800, 600);

    // Główny widget i layout
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Ustawienie tła na jasno-szary kolor
    centralWidget->setStyleSheet("background-color: #f0f0f0;");

    QHBoxLayout *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Kontener na formularz logowania
    QFrame *loginFrame = new QFrame();
    loginFrame->setFrameShape(QFrame::StyledPanel);
    loginFrame->setStyleSheet("background-color: white; border-radius: 10px;");
    loginFrame->setMinimumWidth(400);
    loginFrame->setMaximumWidth(500);

    QVBoxLayout *loginLayout = new QVBoxLayout(loginFrame);
    loginLayout->setContentsMargins(40, 40, 40, 40);
    loginLayout->setSpacing(20);

    // Tytuł
    titleLabel = new QLabel("Welcome Back", loginFrame);
    QFont titleFont;
    titleFont.setPointSize(24);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    loginLayout->addWidget(titleLabel);

    // Dodaj przestrzeń
    loginLayout->addSpacing(30);

    // Username label i pole
    QLabel *usernameLabel = new QLabel("Username", loginFrame);
    QFont labelFont;
    labelFont.setPointSize(11);
    usernameLabel->setFont(labelFont);
    loginLayout->addWidget(usernameLabel);

    usernameField = new QLineEdit(loginFrame);
    usernameField->setMinimumHeight(40);
    usernameField->setStyleSheet("border: 1px solid #ccc; border-radius: 5px; padding: 5px;");
    loginLayout->addWidget(usernameField);

    // Password label i pole
    QLabel *passwordLabel = new QLabel("Password", loginFrame);
    passwordLabel->setFont(labelFont);
    loginLayout->addWidget(passwordLabel);

    passwordField = new QLineEdit(loginFrame);
    passwordField->setEchoMode(QLineEdit::Password);
    passwordField->setMinimumHeight(40);
    passwordField->setStyleSheet("border: 1px solid #ccc; border-radius: 5px; padding: 5px;");
    loginLayout->addWidget(passwordField);

    // Dodaj przestrzeń
    loginLayout->addSpacing(20);

    // Przycisk logowania
    loginButton = new QPushButton("Sign In", loginFrame);
    loginButton->setMinimumHeight(50);
    loginButton->setStyleSheet("background-color: #2979ff; color: white; border: none; border-radius: 5px; font-weight: bold; font-size: 16px;");
    loginLayout->addWidget(loginButton);

    // Dodaj elastyczną przestrzeń na dole
    loginLayout->addStretch(1);

    // Dodaj kontener logowania do głównego layoutu
    mainLayout->addWidget(loginFrame, 0, Qt::AlignCenter);

    // Podłączenie sygnału przycisku do slotu
    connect(loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginButtonClicked);
}

LoginWindow::~LoginWindow()
{
    // Destruktor
}

void LoginWindow::onLoginButtonClicked()
{
    // Pobranie danych z formularza
    QString username = usernameField->text();
    QString password = passwordField->text();

    // Walidacja
    if (username.isEmpty())
    {
        QMessageBox::warning(this, "Błąd", "Proszę wprowadzić nazwę użytkownika.");
        return;
    }

    if (password.isEmpty())
    {
        QMessageBox::warning(this, "Błąd", "Proszę wprowadzić hasło.");
        return;
    }

    // W prawdziwej aplikacji tutaj byłoby połączenie z bazą danych
    // Dane konfiguracyjne bazy danych
    QString host = "localhost";
    QString user = "michal";
    QString dbPassword = "1234";
    QString database = "bd_projekt";

    // Próba połączenia z bazą danych
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName(host);
    db.setUserName(user);
    db.setPassword(dbPassword);
    db.setDatabaseName(database);

    if (!db.open()) {
        QMessageBox::critical(this, "Błąd połączenia", "Nie można połączyć z bazą danych: " + db.lastError().text());
        return;
    }

    // Na potrzeby demonstracji:
    // QMessageBox::information(this, "Sukces", "Zalogowano pomyślnie jako " + username);

    // Zamknięcie połączenia
    db.close();

    // Otwórz okno z grupami
    GroupsWindow *groupsWindow = new GroupsWindow();
    groupsWindow->show();

    // Zamknij okno logowania
    this->close();
}