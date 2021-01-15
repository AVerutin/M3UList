#ifndef CHANNEL_H
#define CHANNEL_H

#include <QString>

// Класс канала
class Channel
{
public:
  // Свойства класса
  int duration;
  int tvgId;
  QString tvgName;
  QString tvgLogo;
  int tvgShift;
  QString groupName;
  bool radio;
  QString audioTrack;
  bool censored;
  int epgId;
  bool recordable;
  bool ageRestriction;
  bool nameAsKey;
  QString url;

  // Методы класса
  Channel();
  QString toString();
  void setCrop(int, int, int, int);
  QString getCrop();
  void setAspectRatio(int, int);
  QString getAspectRatio();

  Channel &operator=(const Channel);

private:
  QString aspectRatio;
  QString crop;
};

#endif // CHANNEL_H
