#include <QApplication>
#include <QMessageBox>
#include "mainwindow.h"
#include "database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Sprawdź dostępność sterownika MySQL
    if (!QSqlDatabase::drivers().contains("QMYSQL")) {
        QMessageBox::critical(nullptr, "Database Error",
                              "MySQL driver not found!");
        return 1;
    }

    // Połącz z bazą danych
    if (!Database::getInstance().connectToDatabase()) {
        QMessageBox::critical(nullptr, "Database Error",
                              "Could not connect to database!");
        return 1;
    }

    MainWindow w;
    w.show();
    return a.exec();
}
