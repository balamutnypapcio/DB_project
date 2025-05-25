#ifndef ADDGROUPDIALOG_H
#define ADDGROUPDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>

class AddGroupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddGroupDialog(QWidget *parent = nullptr);
    QString getGroupName() const;

private:
    QLineEdit *groupNameEdit;
    QMessageBox* createStyledMessageBox(QMessageBox::Icon icon,
                                        const QString& title,
                                        const QString& text);
    void setupUI();
    void setupStyles();
};

#endif // ADDGROUPDIALOG_H
