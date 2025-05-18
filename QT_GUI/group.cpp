#include "group.h"

Group::Group(const QString& name)
    : name(name)
{
}

QString Group::getName() const
{
    return name;
}
