#ifndef ADDEXPENSEDIALOG_H
#define ADDEXPENSEDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>

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

    // Metoda pomocnicza do tworzenia styled message boxów
    QMessageBox* createStyledMessageBox(QMessageBox::Icon icon,
                                        const QString& title,
                                        const QString& text);

    void setupUI();
    void setupStyles();
};

#endif // ADDEXPENSEDIALOG_H
