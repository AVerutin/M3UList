#ifndef GROUP_H
#define GROUP_H

#include <QString>

class Group
{
public:
  Group();
  Group(const Group &);
  int getUid();
  void setUid(int);
  QString getName();
  void setName(const QString &);

private:
  int uid;
  QString name;

};

#endif // GROUP_H
