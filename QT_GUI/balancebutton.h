#ifndef BALANCEBUTTON_H
#define BALANCEBUTTON_H

#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>

class BalanceButton : public QPushButton
{
    Q_OBJECT

public:
    explicit BalanceButton(const QString& username, double balance, QWidget *parent = nullptr)
        : QPushButton(parent)
    {
        setFlat(true);

        QHBoxLayout* layout = new QHBoxLayout(this);
        layout->setContentsMargins(12, 6, 12, 6);

        // Nazwa użytkownika
        QLabel* nameLabel = new QLabel(username, this);
        nameLabel->setStyleSheet("color: #000000; font-size: 14px; font-weight: normal;");
        layout->addWidget(nameLabel);

        // Kwota (dodatnia lub ujemna)
        QString balanceText = QString("%1$%2")
                                  .arg(balance < 0 ? "-" : "")
                                  .arg(QString::number(std::abs(balance), 'f', 2));
        QLabel* balanceLabel = new QLabel(balanceText, this);

        QString color = balance >= 0 ? "#2ECC71" : "#E74C3C";  // zielony lub czerwony
        balanceLabel->setStyleSheet(QString("color: %1; font-size: 14px; font-weight: bold;").arg(color));
        layout->addWidget(balanceLabel);
        layout->addStretch();

        setStyleSheet(
            "BalanceButton {"
            "   background-color: white;"
            "   border: 1px solid #dddddd;"
            "   border-radius: 8px;"
            "   padding: 8px;"
            "   text-align: left;"
            "}"
            "BalanceButton:hover {"
            "   background-color: #f5f5f5;"
            "}"
            );

        setMinimumHeight(50);
        setCursor(Qt::PointingHandCursor);
    }
};

#endif // BALANCEBUTTON_H
