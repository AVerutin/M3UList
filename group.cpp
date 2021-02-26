#include "group.h"

Group::Group()
{
  uid = -1;
  name = "";
}

Group::Group(const Group &item)
{
  uid = item.uid;
  name = item.name;
}

int Group::getUid()
{
  return uid;
}

void Group::setUid(int id)
{
  uid = id;
}

QString Group::getName()
{
  return name;
}

void Group::setName(const QString &new_name)
{
  name = new_name;
}

