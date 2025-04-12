#include "LoginWindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    LoginWindow loginWindow;
    loginWindow.show();

    return app.exec();
}