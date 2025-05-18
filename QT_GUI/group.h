#ifndef GROUP_H
#define GROUP_H

#include <QString>
#include <QVector>

class Group
{
public:
    Group(const QString& name);
    QString getName() const;
    // Dodaj więcej funkcji związanych z grupą

private:
    QString name;
    // Dodaj więcej pól związanych z grupą
};

#endif // GROUP_H
