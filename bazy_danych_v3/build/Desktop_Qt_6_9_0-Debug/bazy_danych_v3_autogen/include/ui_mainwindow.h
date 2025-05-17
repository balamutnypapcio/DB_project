/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
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
    QWidget *expensePage;
    QVBoxLayout *verticalLayout_7;
    QWidget *TopWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *labelExpenseName;
    QPushButton *buttonReturn;
    QWidget *WidgetExpenceBalances;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *buttonBalances;
    QPushButton *buttonExpences;
    QStackedWidget *StackedWidgetBalancesOrExpences;
    QWidget *balancesPage;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QVBoxLayout *verticalLayout_8;
    QLabel *dataBalance1;
    QPushButton *balance1;
    QLabel *dateBalance2;
    QPushButton *balance2;
    QSpacerItem *verticalSpacer_5;
    QWidget *expencesPage;
    QVBoxLayout *verticalLayout_5;
    QScrollArea *scrollArea_3;
    QWidget *scrollAreaWidgetContents_3;
    QVBoxLayout *verticalLayout_9;
    QLabel *dataExpense1;
    QPushButton *expense1;
    QLabel *dataExpense2;
    QPushButton *expense2;
    QSpacerItem *verticalSpacer_6;
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
        usernameInsert->setStyleSheet(QString::fromUtf8("color:rgb(0, 0, 0)"));

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
        passwordInsert->setStyleSheet(QString::fromUtf8("color:black;"));

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
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 176, 126));
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
        expensePage = new QWidget();
        expensePage->setObjectName("expensePage");
        verticalLayout_7 = new QVBoxLayout(expensePage);
        verticalLayout_7->setObjectName("verticalLayout_7");
        TopWidget = new QWidget(expensePage);
        TopWidget->setObjectName("TopWidget");
        horizontalLayout = new QHBoxLayout(TopWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        labelExpenseName = new QLabel(TopWidget);
        labelExpenseName->setObjectName("labelExpenseName");
        labelExpenseName->setStyleSheet(QString::fromUtf8("\n"
"color: #000000;font-size: 25pt;"));

        horizontalLayout->addWidget(labelExpenseName);

        buttonReturn = new QPushButton(TopWidget);
        buttonReturn->setObjectName("buttonReturn");
        buttonReturn->setMinimumSize(QSize(30, 25));
        buttonReturn->setMaximumSize(QSize(30, 25));

        horizontalLayout->addWidget(buttonReturn);


        verticalLayout_7->addWidget(TopWidget);

        WidgetExpenceBalances = new QWidget(expensePage);
        WidgetExpenceBalances->setObjectName("WidgetExpenceBalances");
        horizontalLayout_2 = new QHBoxLayout(WidgetExpenceBalances);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        buttonBalances = new QPushButton(WidgetExpenceBalances);
        buttonBalances->setObjectName("buttonBalances");
        buttonBalances->setStyleSheet(QString::fromUtf8("border: 2px solid #555;\n"
"background-color: #3174e0;\n"
"font-size: 16pt;\n"
"ncolor: #FFFFFF;\n"
"color: #FFFFFF;"));

        horizontalLayout_2->addWidget(buttonBalances);

        buttonExpences = new QPushButton(WidgetExpenceBalances);
        buttonExpences->setObjectName("buttonExpences");
        buttonExpences->setStyleSheet(QString::fromUtf8("border: 2px solid #555;\n"
"background-color: #3174e0;\n"
"font-size: 16pt;\n"
"ncolor: #FFFFFF;\n"
"color: #FFFFFF;"));

        horizontalLayout_2->addWidget(buttonExpences);


        verticalLayout_7->addWidget(WidgetExpenceBalances);

        StackedWidgetBalancesOrExpences = new QStackedWidget(expensePage);
        StackedWidgetBalancesOrExpences->setObjectName("StackedWidgetBalancesOrExpences");
        balancesPage = new QWidget();
        balancesPage->setObjectName("balancesPage");
        verticalLayout = new QVBoxLayout(balancesPage);
        verticalLayout->setObjectName("verticalLayout");
        scrollArea_2 = new QScrollArea(balancesPage);
        scrollArea_2->setObjectName("scrollArea_2");
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName("scrollAreaWidgetContents_2");
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 273, 409));
        verticalLayout_8 = new QVBoxLayout(scrollAreaWidgetContents_2);
        verticalLayout_8->setObjectName("verticalLayout_8");
        dataBalance1 = new QLabel(scrollAreaWidgetContents_2);
        dataBalance1->setObjectName("dataBalance1");

        verticalLayout_8->addWidget(dataBalance1);

        balance1 = new QPushButton(scrollAreaWidgetContents_2);
        balance1->setObjectName("balance1");
        balance1->setFlat(true);

        verticalLayout_8->addWidget(balance1);

        dateBalance2 = new QLabel(scrollAreaWidgetContents_2);
        dateBalance2->setObjectName("dateBalance2");

        verticalLayout_8->addWidget(dateBalance2);

        balance2 = new QPushButton(scrollAreaWidgetContents_2);
        balance2->setObjectName("balance2");
        balance2->setFlat(true);

        verticalLayout_8->addWidget(balance2);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_8->addItem(verticalSpacer_5);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        verticalLayout->addWidget(scrollArea_2);

        StackedWidgetBalancesOrExpences->addWidget(balancesPage);
        expencesPage = new QWidget();
        expencesPage->setObjectName("expencesPage");
        verticalLayout_5 = new QVBoxLayout(expencesPage);
        verticalLayout_5->setObjectName("verticalLayout_5");
        scrollArea_3 = new QScrollArea(expencesPage);
        scrollArea_3->setObjectName("scrollArea_3");
        scrollArea_3->setWidgetResizable(true);
        scrollAreaWidgetContents_3 = new QWidget();
        scrollAreaWidgetContents_3->setObjectName("scrollAreaWidgetContents_3");
        scrollAreaWidgetContents_3->setGeometry(QRect(0, 0, 273, 409));
        verticalLayout_9 = new QVBoxLayout(scrollAreaWidgetContents_3);
        verticalLayout_9->setObjectName("verticalLayout_9");
        dataExpense1 = new QLabel(scrollAreaWidgetContents_3);
        dataExpense1->setObjectName("dataExpense1");

        verticalLayout_9->addWidget(dataExpense1);

        expense1 = new QPushButton(scrollAreaWidgetContents_3);
        expense1->setObjectName("expense1");

        verticalLayout_9->addWidget(expense1);

        dataExpense2 = new QLabel(scrollAreaWidgetContents_3);
        dataExpense2->setObjectName("dataExpense2");

        verticalLayout_9->addWidget(dataExpense2);

        expense2 = new QPushButton(scrollAreaWidgetContents_3);
        expense2->setObjectName("expense2");

        verticalLayout_9->addWidget(expense2);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_9->addItem(verticalSpacer_6);

        scrollArea_3->setWidget(scrollAreaWidgetContents_3);

        verticalLayout_5->addWidget(scrollArea_3);

        StackedWidgetBalancesOrExpences->addWidget(expencesPage);

        verticalLayout_7->addWidget(StackedWidgetBalancesOrExpences);

        stackedWidget->addWidget(expensePage);

        verticalLayout_2->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(2);
        createButton->setDefault(false);
        StackedWidgetBalancesOrExpences->setCurrentIndex(1);


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
        labelExpenseName->setText(QCoreApplication::translate("MainWindow", "Group Name", nullptr));
        buttonReturn->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        buttonBalances->setText(QCoreApplication::translate("MainWindow", "Balances", nullptr));
        buttonExpences->setText(QCoreApplication::translate("MainWindow", "Expenses", nullptr));
        dataBalance1->setText(QCoreApplication::translate("MainWindow", "01.01.2001", nullptr));
        balance1->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        dateBalance2->setText(QCoreApplication::translate("MainWindow", "02.02.2002", nullptr));
        balance2->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        dataExpense1->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        expense1->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
        dataExpense2->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        expense2->setText(QCoreApplication::translate("MainWindow", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
