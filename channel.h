#ifndef CHANNEL_H
#define CHANNEL_H

#include <QString>

#include "datatypes.h"

// Класс канала
class Channel
{
public:
  // Методы класса
  Channel();
  QString toString();
  void setCrop(int, int, int, int);
  void setCrop(const QString &);
  QString getCrop();
  void setAspectRatio(int, int);
  void setAspectRatio(const QString &);
  QString getAspectRatio();
  int incOrder();
  int decOrder();
  void setOrder(int);
  int getOrder();
  void setUserAgent(const QString &);
  QString getUserAgent();
  void setHttpReffer(const QString &);
  QString getHttpReffer();
  void setUrl(const QString &);
  QString getUrl();
  void setDuration(int);
  int getDuration();
  void setId(int);
  int getId();
  void setTvgId(const QString &);
  QString getTvgId();
  void setTvgName(const QString &);
  QString getTvgName();
  void setTvgLogo(const QString &);
  QString getTvgLogo();
  void setTvgShift(int);
  int getTvgShift();
  void setGroupName(const QString &);
  QString getGroupName();
  void setRadio(bool);
  bool isRadio();
  void setRecordable(bool);
  bool isRecordable();
  void setCensored(bool);
  bool isCensored();
  void setAgeRestricted(bool);
  bool isAgeRestricted();
  void setNameAsKey(bool);
  bool isNameAsKey();
  void setMono(bool);
  bool isMono();
  void setAudioTrack(const QString &);
  QString getAudioTrack();
  void setUrlM3u(const QString &);
  QString getUrlM3u();

  Channel &operator=(const Channel &);

private:
  // Свойства класса
  int order;
  QString aspectRatio;
  QString crop;
  QString url;

  VlcInfo *vlcInfo;
  ChannelInfo *channelInfo;
};

#endif // CHANNEL_H
