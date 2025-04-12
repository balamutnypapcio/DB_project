#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

class GroupsWindow;

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

    private slots:
        void onLoginButtonClicked();

private:
    QLineEdit *usernameField;
    QLineEdit *passwordField;
    QPushButton *loginButton;
    QLabel *titleLabel;
};

#endif // LOGINWINDOW_H