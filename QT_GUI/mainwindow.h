#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "Database.h"
#include "expensebutton.h"
#include "addexpensedialog.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void loadGroups();
    int currentExpenseId;



private slots:
    void handleSignInButton();
    void handleGroupSelection(int groupId, const QString& groupName);
    void handleAddGroupButton();
    void handleReturnButton();
    void loadUserGroups();
    void loadExpenses();
    void onGroupsChanged();
    void onExpensesChanged(int groupId);
    void onExpenseDetailsChanged(int expenseId);
    void handleAddMemberButton();
    // void handleRemoveMember(const QString& username);

private slots:
    /**
     * @name Sloty obsługi przycisków nawigacji
     * @{
     */
    void backButton1_clicked();
    void backButton2_clicked();
    void backButton3_clicked();
    void createButton_clicked();
    void handleAddExpenseButton();
    void loadExpenseDetails(int expenseId);
    void handleExpenseClick(int expenseId);
    void handleBackFromDetails();

private:

    Ui::MainWindow *ui;
    QString currentUser;
    int currentUserId;
    int currentGroupId = -1; // Dodaj jeśli nie istnieje
    QTimer* dateTimeTimer;
    void setupConnections();
    void updateDateTime();
    QVector<QPair<int, QString>> userGroups;  // first: groupId, second: groupName
    void updateGroupMembersList();
    QVector<QString> currentGroupMembers;
    struct ParticipantData {
        QString username;
        double share;
        bool isPaid;
    };

    QMessageBox* createStyledMessageBox(QMessageBox::Icon icon,
                                        const QString& title,
                                        const QString& text,
                                        QMessageBox::StandardButtons buttons = QMessageBox::Ok);
#endif // MAINWINDOW_H
