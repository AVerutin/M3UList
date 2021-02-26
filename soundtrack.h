#ifndef SOUNDTRACK_H
#define SOUNDTRACK_H

#include <QString>

class Soundtrack
{
public:
  Soundtrack();
  Soundtrack(const Soundtrack &);
  int getUid();
  void setUid(int);
  QString getName();
  void setName(const QString &);

private:
  int uid;
  QString name;
};

#endif // SOUNDTRACK_H
