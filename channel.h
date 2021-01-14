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
  QString aspectRatio;
  bool censored;

  // Методы класса
  Channel();
};

#endif // CHANNEL_H
