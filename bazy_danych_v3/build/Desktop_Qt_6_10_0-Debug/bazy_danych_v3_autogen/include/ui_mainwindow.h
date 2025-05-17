/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QStackedWidget *stackedWidget;
    QWidget *welcomePage;
    QVBoxLayout *verticalLayout_3;
    QLabel *welcomeLabel;
    QSpacerItem *verticalSpacer_4;
    QLabel *usernameLabel;
    QLineEdit *usernameInsert;
    QLabel *passwordLabel;
    QLineEdit *passwordInsert;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton;
    QSpacerItem *verticalSpacer_3;
    QWidget *groupsPage;
    QVBoxLayout *verticalLayout_4;
    QLabel *groupsLabel;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QVBoxLayout *verticalLayout_6;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_2;
    QSpacerItem *verticalSpacer;
    QPushButton *createButton;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(329, 600);
        MainWindow->setMinimumSize(QSize(0, 500));
        MainWindow->setStyleSheet(QString::fromUtf8("\n"
"background-color: #FFFFFF;"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        centralwidget->setStyleSheet(QString::fromUtf8("background-color: 000000;\n"
""));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName("verticalLayout_2");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        stackedWidget->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        welcomePage = new QWidget();
        welcomePage->setObjectName("welcomePage");
        welcomePage->setStyleSheet(QString::fromUtf8("\n"
"background-color: #FFFFFF;"));
        verticalLayout_3 = new QVBoxLayout(welcomePage);
        verticalLayout_3->setObjectName("verticalLayout_3");
        welcomeLabel = new QLabel(welcomePage);
        welcomeLabel->setObjectName("welcomeLabel");
        QFont font;
        font.setPointSize(31);
        font.setBold(true);
        welcomeLabel->setFont(font);
        welcomeLabel->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        welcomeLabel->setStyleSheet(QString::fromUtf8("\n"
"color: #000000;"));
        welcomeLabel->setTextFormat(Qt::TextFormat::MarkdownText);
        welcomeLabel->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignHCenter);

        verticalLayout_3->addWidget(welcomeLabel);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_4);

        usernameLabel = new QLabel(welcomePage);
        usernameLabel->setObjectName("usernameLabel");
        usernameLabel->setMaximumSize(QSize(16777215, 80));
        usernameLabel->setStyleSheet(QString::fromUtf8("\n"
"color: #000000;"));
        usernameLabel->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft);

        verticalLayout_3->addWidget(usernameLabel);

        usernameInsert = new QLineEdit(welcomePage);
        usernameInsert->setObjectName("usernameInsert");

        verticalLayout_3->addWidget(usernameInsert);

        passwordLabel = new QLabel(welcomePage);
        passwordLabel->setObjectName("passwordLabel");
        passwordLabel->setMinimumSize(QSize(0, 30));
        passwordLabel->setMaximumSize(QSize(16777215, 30));
        passwordLabel->setStyleSheet(QString::fromUtf8("\n"
"color: #000000;"));
        passwordLabel->setAlignment(Qt::AlignmentFlag::AlignBottom|Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft);

        verticalLayout_3->addWidget(passwordLabel);

        passwordInsert = new QLineEdit(welcomePage);
        passwordInsert->setObjectName("passwordInsert");
        passwordInsert->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(passwordInsert->sizePolicy().hasHeightForWidth());
        passwordInsert->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(passwordInsert);

        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_2);

        pushButton = new QPushButton(welcomePage);
        pushButton->setObjectName("pushButton");
        pushButton->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setMinimumSize(QSize(0, 30));
        pushButton->setMaximumSize(QSize(16777215, 16777215));
        pushButton->setStyleSheet(QString::fromUtf8("border: 2px solid #555;\n"
"background-color: #3174e0;\n"
"font-size: 16pt;\n"
"ncolor: #FFFFFF;\n"
"color: #FFFFFF;"));
        pushButton->setAutoDefault(false);

        verticalLayout_3->addWidget(pushButton);

        verticalSpacer_3 = new QSpacerItem(20, 100, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Fixed);

        verticalLayout_3->addItem(verticalSpacer_3);

        stackedWidget->addWidget(welcomePage);
        groupsPage = new QWidget();
        groupsPage->setObjectName("groupsPage");
        verticalLayout_4 = new QVBoxLayout(groupsPage);
        verticalLayout_4->setObjectName("verticalLayout_4");
        groupsLabel = new QLabel(groupsPage);
        groupsLabel->setObjectName("groupsLabel");
        groupsLabel->setMaximumSize(QSize(16777215, 30));
        groupsLabel->setStyleSheet(QString::fromUtf8("\n"
"color: #000000;font-size: 25pt;"));

        verticalLayout_4->addWidget(groupsLabel);

        scrollArea = new QScrollArea(groupsPage);
        scrollArea->setObjectName("scrollArea");
        scrollArea->setStyleSheet(QString::fromUtf8("\n"
"background-color: #FFFFFF;"));
        scrollArea->setWidgetResizable(true);
        scrollArea->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignTop);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName("scrollAreaWidgetContents");
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 303, 461));
        scrollAreaWidgetContents->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        verticalLayout_6 = new QVBoxLayout(scrollAreaWidgetContents);
        verticalLayout_6->setObjectName("verticalLayout_6");
        pushButton_3 = new QPushButton(scrollAreaWidgetContents);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setMinimumSize(QSize(0, 30));
        pushButton_3->setMaximumSize(QSize(16777215, 50));
        pushButton_3->setStyleSheet(QString::fromUtf8("font-size: 12pt;\n"
"color: #000000;\n"
"background-color: #FFFFFF;"));

        verticalLayout_6->addWidget(pushButton_3);

        pushButton_4 = new QPushButton(scrollAreaWidgetContents);
        pushButton_4->setObjectName("pushButton_4");
        pushButton_4->setMinimumSize(QSize(0, 30));
        pushButton_4->setMaximumSize(QSize(16777215, 50));
        pushButton_4->setStyleSheet(QString::fromUtf8("font-size: 12pt;\n"
"color: #000000;\n"
"background-color: #FFFFFF;"));

        verticalLayout_6->addWidget(pushButton_4);

        pushButton_2 = new QPushButton(scrollAreaWidgetContents);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMinimumSize(QSize(0, 30));
        pushButton_2->setMaximumSize(QSize(16777215, 50));
        pushButton_2->setStyleSheet(QString::fromUtf8("font-size: 12pt;\n"
"color: #000000;\n"
"background-color: #FFFFFF;"));

        verticalLayout_6->addWidget(pushButton_2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_4->addWidget(scrollArea);

        createButton = new QPushButton(groupsPage);
        createButton->setObjectName("createButton");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(createButton->sizePolicy().hasHeightForWidth());
        createButton->setSizePolicy(sizePolicy2);
        createButton->setMinimumSize(QSize(54, 54));
        createButton->setMaximumSize(QSize(160000, 50));
        createButton->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        createButton->setStyleSheet(QString::fromUtf8("border: 2px solid #555;\n"
"border-radius: 25px; \n"
"background-color: #3174e0;\n"
"min-width: 50px;\n"
"min-height: 50px;\n"
"font-size: 16pt;\n"
"ncolor: #FFFFFF;\n"
"color: #FFFFFF;"));
        createButton->setAutoDefault(false);

        verticalLayout_4->addWidget(createButton);

        stackedWidget->addWidget(groupsPage);

        verticalLayout_2->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);
        createButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        welcomeLabel->setText(QCoreApplication::translate("MainWindow", "WELCOME", nullptr));
        usernameLabel->setText(QCoreApplication::translate("MainWindow", "USERNAME", nullptr));
        passwordLabel->setText(QCoreApplication::translate("MainWindow", "PASSWORD", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "SIGN IN", nullptr));
        groupsLabel->setText(QCoreApplication::translate("MainWindow", "Your Groups", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Vacations", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Apartment Expenses", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Beer Night", nullptr));
        createButton->setText(QCoreApplication::translate("MainWindow", "Add Group", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
