#include "soundtrack.h"

Soundtrack::Soundtrack()
{
  uid = -1;
  name = "";
}

Soundtrack::Soundtrack(const Soundtrack &item)
{
  uid = item.uid;
  name = item.name;
}

int Soundtrack::getUid()
{
  return uid;
}

void Soundtrack::setUid(int id)
{
  uid = id;
}

QString Soundtrack::getName()
{
  return name;
}

void Soundtrack::setName(const QString &new_name)
{
  name = new_name;
}

