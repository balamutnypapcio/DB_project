#include "addexpensedialog.h"

AddExpenseDialog::AddExpenseDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Dodaj nowy wydatek");

    auto layout = new QVBoxLayout(this);

    descriptionEdit = new QLineEdit(this);
    descriptionEdit->setPlaceholderText("Opis wydatku");
    layout->addWidget(descriptionEdit);

    amountSpinBox = new QDoubleSpinBox(this);
    amountSpinBox->setRange(0.01, 1000000.00);
    amountSpinBox->setDecimals(2);
    amountSpinBox->setSuffix(" PLN");
    amountSpinBox->setValue(0.01);
    layout->addWidget(amountSpinBox);

    auto buttonBox = new QDialogButtonBox(
        QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
        Qt::Horizontal,
        this
        );

    connect(buttonBox, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &QDialog::reject);

    layout->addWidget(buttonBox);
}

QString AddExpenseDialog::getDescription() const
{
    return descriptionEdit->text();
}

double AddExpenseDialog::getAmount() const
{
    return amountSpinBox->value();
}
