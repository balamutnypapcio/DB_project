#include "addgroupdialog.h"

AddGroupDialog::AddGroupDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
    setupStyles();
}


void AddGroupDialog::setupUI()
{
    setWindowTitle("Dodaj nową grupę");
    setFixedSize(450, 250); // Ustaw stały rozmiar okna

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);        // Zwiększ odstępy między elementami
    mainLayout->setContentsMargins(40, 40, 40, 40); // Zwiększ marginesy

    // Sekcja nazwy grupy
    auto nameLabel = new QLabel("Nazwa grupy:", this);
    nameLabel->setStyleSheet("color: #000000; font-size: 16pt;"); // Zwiększ rozmiar czcionki
    mainLayout->addWidget(nameLabel);

    groupNameEdit = new QLineEdit(this);
    groupNameEdit->setPlaceholderText("Wprowadź nazwę grupy");
    groupNameEdit->setMinimumHeight(40); // Zwiększ wysokość pola tekstowego
    mainLayout->addWidget(groupNameEdit);

    // Spacer dla lepszego układu
    mainLayout->addSpacing(30);

    // Przyciski
    auto buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal,
        this
        );

    buttonBox->button(QDialogButtonBox::Ok)->setText("Utwórz");
    buttonBox->button(QDialogButtonBox::Cancel)->setText("Anuluj");

    // Ustaw minimalną szerokość przycisków
    buttonBox->button(QDialogButtonBox::Ok)->setMinimumWidth(120);
    buttonBox->button(QDialogButtonBox::Cancel)->setMinimumWidth(120);

    mainLayout->addWidget(buttonBox);
}



void AddGroupDialog::setupStyles()
{
    setStyleSheet(
        "QDialog {"
        "    background-color: #FFFFFF;"
        "}"
        "QLabel {"
        "    color: #000000;"
        "    font-size: 14pt;"
        "    margin-bottom: 8px;"
        "}"
        "QLineEdit {"
        "    height: 35px;"
        "    padding: 0 12px;"
        "    border: 2px solid #4169E1;"
        "    border-radius: 8px;"
        "    color: #000000;"
        "    font-size: 13pt;"
        "    background-color: #FFFFFF;"
        "}"
        "QPushButton {"
        "    min-width: 120px;"
        "    min-height: 35px;"
        "    background-color: #4169E1;"
        "    border-radius: 10px;"
        "    color: white;"
        "    font-size: 13pt;"
        "    font-weight: bold;"
        "    padding: 5px 15px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #5a7ee5;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #0d1b3f;"
        "}"
        );
}

QMessageBox* AddGroupDialog::createStyledMessageBox(
    QMessageBox::Icon icon,
    const QString& title,
    const QString& text)
{
    QMessageBox* msgBox = new QMessageBox(this);
    msgBox->setIcon(icon);
    msgBox->setWindowTitle(title);
    msgBox->setText(text);
    msgBox->setStyleSheet(
        "QMessageBox {"
        "    background-color: #FFFFFF;"
        "}"
        "QMessageBox QLabel {"
        "    color: #000000;"
        "    font-size: 13pt;"
        "    min-width: 300px;"
        "}"
        "QPushButton {"
        "    min-width: 120px;"
        "    min-height: 35px;"
        "    background-color: #4169E1;"
        "    border-radius: 10px;"
        "    color: white;"
        "    font-size: 13pt;"
        "    font-weight: bold;"
        "    padding: 5px 15px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #5a7ee5;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #0d1b3f;"
        "}"
        );
    return msgBox;
}

QString AddGroupDialog::getGroupName() const
{
    return groupNameEdit->text();
}
