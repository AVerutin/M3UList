#ifndef PLAYLISTPARSER_H
#define PLAYLISTPARSER_H

#include <QString>
#include <QFile>
#include <QRegExp>
#include <QDebug>
// #include <QList>

#include "playlist.h"
#include "channel.h"
#include "logger.h"

class Parser
{
public:
  Parser();
  Parser(QString);

  PlayList parse();

private:
  Channel *channel;
  QFile *listFile;
  QString playlistName;
  Logger *logger;

  PlayListInfo getListTitle(const QString &);
  QString getGroupName(const QString &);
  QString getListName(const QString &);
  VlcInfo getVlcOpt(const QString &);
  ChannelInfo getChannelInfo(const QString &);
};

#endif // PLAYLISTPARSER_H
