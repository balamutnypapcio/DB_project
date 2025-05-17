#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "database.h"

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
    void handleGroupSelection(const QString& groupName);
    void handleAddGroupButton();
    void handleReturnButton();
    void updateDateTime();

private:
    Ui::MainWindow *ui;
    QString currentUser;
    void setupConnections();
    QTimer* dateTimeTimer;
};

#endif // MAINWINDOW_H
