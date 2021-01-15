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
  int refreshPeriod;
  int tvgShift;
  QString userAgent;

  QList<Channel> *channels;

  //Методы класса
  PlayList();
  PlayList &operator=(const PlayList);
  QString toString();
  void setCrop(int, int, int, int);
  void setAspectRatio(int, int);

private:
  QString crop;
  QString aspectRatio;

};

#endif // PLAYLIST_H
