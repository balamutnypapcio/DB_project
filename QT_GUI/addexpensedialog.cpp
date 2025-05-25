#include "addexpensedialog.h"

AddExpenseDialog::AddExpenseDialog(QWidget *parent)
    : QDialog(parent)
{
    setupUI();
    setupStyles();
}

void AddExpenseDialog::setupUI()
{
    setWindowTitle("Dodaj nowy wydatek");
    setMinimumWidth(300);

    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(10);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Sekcja opisu
    auto descriptionLabel = new QLabel("Opis wydatku:", this);
    mainLayout->addWidget(descriptionLabel);

    descriptionEdit = new QLineEdit(this);
    descriptionEdit->setPlaceholderText("Wprowadź opis wydatku");
    mainLayout->addWidget(descriptionEdit);

    // Sekcja kwoty
    auto amountLabel = new QLabel("Kwota:", this);
    mainLayout->addWidget(amountLabel);

    amountSpinBox = new QDoubleSpinBox(this);
    amountSpinBox->setRange(0.01, 1000000.00);
    amountSpinBox->setDecimals(2);
    amountSpinBox->setSuffix(" PLN");
    amountSpinBox->setValue(0.01);
    mainLayout->addWidget(amountSpinBox);

    // Przyciski
    auto buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal,
        this
        );

    buttonBox->button(QDialogButtonBox::Ok)->setText("Dodaj");
    buttonBox->button(QDialogButtonBox::Cancel)->setText("Anuluj");

    connect(buttonBox, &QDialogButtonBox::accepted, this, [this]() {
        if (descriptionEdit->text().isEmpty()) {
            QMessageBox* msgBox = createStyledMessageBox(
                QMessageBox::Warning,
                "Błąd",
                "Proszę wprowadzić opis wydatku"
                );
            msgBox->exec();
            delete msgBox;
            return;
        }
        accept();
    });

    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    mainLayout->addWidget(buttonBox);
}

void AddExpenseDialog::setupStyles()
{
    setStyleSheet(
        "QDialog {"
        "    background-color: #FFFFFF;"
        "}"
        "QLabel {"
        "    color: #000000;"
        "    font-size: 12pt;"
        "    margin-bottom: 5px;"
        "}"
        "QLineEdit {"
        "    height: 30px;"
        "    padding: 0 8px;"
        "    border: 1px solid #ccc;"
        "    border-radius: 6px;"
        "    color: #000000;"
        "    font-size: 12pt;"
        "    background-color: #FFFFFF;"
        "}"
        "QDoubleSpinBox {"
        "    height: 30px;"
        "    padding: 0 8px;"
        "    border: 1px solid #ccc;"
        "    border-radius: 6px;"
        "    color: #000000;"
        "    font-size: 12pt;"
        "    background-color: #FFFFFF;"
        "}"
        "QPushButton {"
        "    min-width: 100px;"
        "    min-height: 30px;"
        "    background-color: #4169E1;"
        "    border-radius: 10px;"
        "    color: white;"
        "    font-size: 12pt;"
        "    font-weight: bold;"
        "    padding: 5px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #5a7ee5;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #0d1b3f;"
        "}"
        );
}

QMessageBox* AddExpenseDialog::createStyledMessageBox(
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
        "    font-size: 12pt;"
        "    min-width: 200px;"
        "}"
        "QPushButton {"
        "    min-width: 100px;"
        "    min-height: 30px;"
        "    background-color: #4169E1;"
        "    border-radius: 10px;"
        "    color: white;"
        "    font-size: 12pt;"
        "    font-weight: bold;"
        "    padding: 5px;"
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

QString AddExpenseDialog::getDescription() const
{
    return descriptionEdit->text();
}

double AddExpenseDialog::getAmount() const
{
    return amountSpinBox->value();
}
