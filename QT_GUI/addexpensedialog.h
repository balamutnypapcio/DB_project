#ifndef ADDEXPENSEDIALOG_H
#define ADDEXPENSEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QDialogButtonBox>
#include <QVBoxLayout>

class AddExpenseDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddExpenseDialog(QWidget *parent = nullptr);
    QString getDescription() const;
    double getAmount() const;

private:
    QLineEdit *descriptionEdit;
    QDoubleSpinBox *amountSpinBox;
};

#endif // ADDEXPENSEDIALOG_H
