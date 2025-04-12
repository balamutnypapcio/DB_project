#ifndef GROUPSWINDOW_H
#define GROUPSWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

class GroupsWindow : public QMainWindow
{
    Q_OBJECT

public:
    GroupsWindow(QWidget *parent = nullptr);
    ~GroupsWindow();

    private slots:
        void onCreateNewGroupClicked();

private:
    QWidget *createGroupWidget(const QString &name, int members, const QString &lastUpdated);

    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    QPushButton *createNewButton;
    QLabel *titleLabel;
};

#endif // GROUPSWINDOW_H