#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include <QList>
#include "channel.h"
#include "group.h"
#include "soundtrack.h"
#include "playlist.h"

class DataBase
{
public:
  DataBase();
  void dbInit();
  void dbClose();
  QStringList getGroups();
  bool addGroup(const QString &);
  bool addGroups(const QStringList &);
  bool removeGroup(const QString &);
  bool clearGroups();
  QStringList getTracks();
  bool addTrack(const QString &);
  bool addTracks(const QStringList &);
  bool removeTrack(const QString &);
  bool clearTracks();
  bool addChannel(const PlayListInfo &, const ChannelInfo &);
  ChannelInfo getChannel(const QString &);
  ChannelInfo getChannel(int);
  bool addPlaylist(const PlayListInfo &);
  PlayListInfo getPlaylist(const QString &);
  PlayListInfo getPlaylist(int);

  // Новые методы, для работы с группами в базе данных
  QList<Group> getGroupsList();
  void addGroupToList(const Group &);
  bool editGroupInList(int, const Group &);
  bool removeGroupFromList(int);

  // Новые методы, для работы со звуковыми дорожками в базе данных
  QList<Soundtrack> getSoundtracksList();
  void addSoundtrackToList(const Soundtrack &);
  bool editSoundtrackInList(int, const Soundtrack &);
  bool removeSoundtrackFromList(int);

private:
  QSqlDatabase sdb;
  QSqlQuery *query;

};

#endif // DATABASE_H
