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
    void handleAddGroupButton();
    void handleReturnButton();
    void loadUserGroups();
    void loadExpenses();
    void handleExpenseClick(int expenseId);

private:
    Ui::MainWindow *ui;
    QString currentUser;
    int currentUserId;
    int currentGroupId;  // Do przechowywania ID aktualnej grupy
    QTimer* dateTimeTimer;
    void setupConnections();
    void updateDateTime();
    QVector<QPair<int, QString>> userGroups;  // first: groupId, second: groupName
};

#endif // MAINWINDOW_H
