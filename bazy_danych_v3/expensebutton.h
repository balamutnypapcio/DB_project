#ifndef EXPENSEBUTTON_H
#define EXPENSEBUTTON_H

#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDateTime>

class ExpenseButton : public QPushButton
{
    Q_OBJECT

public:
    explicit ExpenseButton(int expenseId,
                           const QDateTime& date,
                           const QString& description,
                           const QString& paidByUsername,
                           double amount,
                           QWidget *parent = nullptr) : QPushButton(parent), m_expenseId(expenseId)
    {
        setFlat(true);

        // Główny layout
        QHBoxLayout* mainLayout = new QHBoxLayout(this);

        // Data
        QLabel* dateLabel = new QLabel(date.toString("dd.MM.yyyy"), this);
        dateLabel->setStyleSheet("color: #666666; font-size: 12px;");

        // Środkowa część (opis i użytkownik)
        QWidget* centerWidget = new QWidget(this);
        QVBoxLayout* centerLayout = new QVBoxLayout(centerWidget);
        centerLayout->setContentsMargins(0, 0, 0, 0);

        QLabel* descLabel = new QLabel(description, centerWidget);
        QLabel* userLabel = new QLabel("by " + paidByUsername, centerWidget);

        descLabel->setStyleSheet("color: #000000; font-size: 14px; font-weight: bold;");
        userLabel->setStyleSheet("color: #666666; font-size: 12px;");

        centerLayout->addWidget(descLabel);
        centerLayout->addWidget(userLabel);

        // Kwota
        QLabel* amountLabel = new QLabel(QString("$%1").arg(amount, 0, 'f', 2), this);
        amountLabel->setStyleSheet("color: #0066cc; font-size: 14px; font-weight: bold;");

        mainLayout->addWidget(dateLabel);
        mainLayout->addWidget(centerWidget, 1);
        mainLayout->addWidget(amountLabel);

        setStyleSheet(
            "ExpenseButton {"
            "   background-color: white;"
            "   border: 1px solid #dddddd;"
            "   border-radius: 5px;"
            "   padding: 10px;"
            "   text-align: left;"
            "}"
            "ExpenseButton:hover {"
            "   background-color: #f5f5f5;"
            "}"
            );

        setMinimumHeight(70);
        setCursor(Qt::PointingHandCursor);
    }

    int expenseId() const { return m_expenseId; }

private:
    int m_expenseId;
};

#endif // EXPENSEBUTTON_H
