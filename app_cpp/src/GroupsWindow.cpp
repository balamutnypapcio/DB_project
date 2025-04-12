#include "GroupsWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QFrame>
#include <QScrollArea>
#include <QIcon>

GroupsWindow::GroupsWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Ustawienia okna
    setWindowTitle("Grupy");
    resize(800, 600);

    // Główny widget i layout
    centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    // Ustawienie tła na jasno-szary kolor
    centralWidget->setStyleSheet("background-color: #f0f0f0;");

    QHBoxLayout *outerLayout = new QHBoxLayout(centralWidget);
    outerLayout->setContentsMargins(20, 20, 20, 20);

    // Kontener na grupy
    QFrame *groupsFrame = new QFrame();
    groupsFrame->setFrameShape(QFrame::StyledPanel);
    groupsFrame->setStyleSheet("background-color: white; border-radius: 10px;");
    groupsFrame->setMinimumWidth(400);
    groupsFrame->setMaximumWidth(500);

    mainLayout = new QVBoxLayout(groupsFrame);
    mainLayout->setContentsMargins(40, 40, 40, 40);
    mainLayout->setSpacing(20);

    // Tytuł
    titleLabel = new QLabel("Your Groups", groupsFrame);
    QFont titleFont;
    titleFont.setPointSize(24);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignLeft);
    mainLayout->addWidget(titleLabel);

    // Dodaj przestrzeń
    mainLayout->addSpacing(20);

    // Dodaj widgety grup
    mainLayout->addWidget(createGroupWidget("Apartment Expenses", 3, "5 days ago"));
    mainLayout->addWidget(createGroupWidget("Apartment Expenses", 3, "5 days ago"));
    mainLayout->addWidget(createGroupWidget("Birthday Party", 6, "1 week ago"));

    // Elastyczny spacer przed przyciskiem "Create New"
    mainLayout->addStretch(1);

    // Przycisk "Create New"
    QHBoxLayout *createNewLayout = new QHBoxLayout();
    createNewButton = new QPushButton("", groupsFrame);
    createNewButton->setIcon(QIcon::fromTheme("list-add"));
    createNewButton->setIconSize(QSize(24, 24));
    createNewButton->setStyleSheet(
        "QPushButton {"
        "  background-color: #00b0ff;"
        "  color: white;"
        "  border: none;"
        "  border-radius: 25px;"
        "  min-width: 50px;"
        "  min-height: 50px;"
        "  font-weight: bold;"
        "  font-size: 16px;"
        "}"
    );

    QLabel *createNewLabel = new QLabel("Create New", groupsFrame);
    QFont createNewFont;
    createNewFont.setPointSize(14);
    createNewFont.setBold(true);
    createNewLabel->setFont(createNewFont);

    createNewLayout->addStretch(1);
    createNewLayout->addWidget(createNewButton);
    createNewLayout->addWidget(createNewLabel);
    createNewLayout->addStretch(1);

    mainLayout->addLayout(createNewLayout);

    // Dodaj kontener grup do głównego layoutu
    outerLayout->addWidget(groupsFrame, 0, Qt::AlignCenter);

    // Podłączenie sygnału przycisku do slotu
    connect(createNewButton, &QPushButton::clicked, this, &GroupsWindow::onCreateNewGroupClicked);
}

GroupsWindow::~GroupsWindow()
{
    // Destruktor
}

void GroupsWindow::onCreateNewGroupClicked()
{
    QMessageBox::information(this, "Nowa grupa", "Tutaj będzie formtularz tworzenia nowej grupy");
}

QWidget* GroupsWindow::createGroupWidget(const QString &name, int members, const QString &lastUpdated)
{
    QFrame *groupFrame = new QFrame();
    groupFrame->setFrameShape(QFrame::StyledPanel);
    groupFrame->setStyleSheet("border: 1px solid #e0e0e0; border-radius: 5px;");
    groupFrame->setMinimumHeight(70);

    QVBoxLayout *layout = new QVBoxLayout(groupFrame);
    layout->setContentsMargins(15, 15, 15, 15);
    layout->setSpacing(5);

    // Nazwa grupy
    QLabel *nameLabel = new QLabel(name, groupFrame);
    QFont nameFont;
    nameFont.setPointSize(12);
    nameFont.setBold(true);
    nameLabel->setFont(nameFont);
    layout->addWidget(nameLabel);

    // Informacje o grupie
    QLabel *infoLabel = new QLabel(QString("%1 members • Last updated: %2").arg(members).arg(lastUpdated), groupFrame);
    infoLabel->setStyleSheet("color: #757575;");
    layout->addWidget(infoLabel);

    return groupFrame;
}