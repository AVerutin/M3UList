#ifndef DATABASE_H
#define DATABASE_H

#include <QtSql>
#include "channel.h"
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

private:
  QSqlDatabase sdb;
  QSqlQuery *query;

};

#endif // DATABASE_H
