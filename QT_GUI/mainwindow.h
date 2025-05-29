#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "Database.h"
#include "expensebutton.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void handleSignInButton();
    void handleGroupSelection(int groupId, const QString& groupName);
    void handleCreateGroupButton();
    void handleReturnButton();
    void loadUserGroups();
    void loadExpenses();
    void handleExpenseClick(int expenseId, const QString& paidBy, double amount);
    void handleAddExpenseClick();
    void handleDeleteExpenseClick();
    void handleDeleteGroup();


private slots:
    /**
     * @name Sloty obsługi przycisków nawigacji
     * @{
     */
    void backButton1_clicked();
    void backButton2_clicked();
    void backButton3_clicked();
    void createButton_clicked();
    void on_createGroupButton_clicked();
    void on_buttonAddNewExpense_clicked();

    void on_buttonCreateExpense_clicked();

    void on_buttonDeleteExpense_clicked();

    void on_pushButton_5_clicked();

private:

    Ui::MainWindow *ui;
    QString currentUser;
    int currentUserId;
    int currentGroupId;  // Do przechowywania ID aktualnej grupy
    int currentExpenseId;  // Do przechowywania aktualnego wydatku (np w celu usuniecia)
    QTimer* dateTimeTimer;
    void setupConnections();
    void updateDateTime();
    QVector<QPair<int, QString>> userGroups;  // first: groupId, second: groupName

    struct ParticipantData {
        QString username;
        double share;
        bool isPaid;
    };
};

#endif // MAINWINDOW_H
