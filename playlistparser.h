#ifndef PLAYLISTPARSER_H
#define PLAYLISTPARSER_H

#include <QString>
#include <QFile>
#include <QRegExp>
// #include <QList>

#include "playlist.h"
#include "channel.h"

class Parser
{
public:
  Parser();
  Parser(QString);

  PlayList parse();

private:
  PlayList *playList;
  Channel *channel;
  QFile *listFile;
  QString playlistName;

  PlayListInfo getListTitle(QString);
  QString getListName(QString);
  VlcInfo getVlcOpt(QString);
  ChannelInfo getChannelInfo(QString);
};

#endif // PLAYLISTPARSER_H
