#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QList>

#include "channel.h"

class PlayList
{
public:
  // Свойства класса
  QString listName;
  QString urlTvg;
  bool autoload;
  int cache;
  int deinterlace;
  QString aspectRatio;
  QString crop;
  int refreshPeriod;
  int tvgShift;

  QList<Channel> *channels;

  //Методы класса
  PlayList();

};

#endif // PLAYLIST_H
