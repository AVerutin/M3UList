#include "channel.h"

Channel::Channel()
{
  order = -1;
  duration = 0;
  tvgId = 0;
  tvgName = "";
  tvgLogo = "";
  tvgShift = 0;
  groupName = "";
  radio = false;
  audioTrack = "";
  aspectRatio = "";
  crop = "";
  censored = false;
  epgId = 0;
  recordable = false; // recordable="true" or recordable="false"
  ageRestriction = false; // agerestriction="0" or agerestriction="1"
  nameAsKey = false; // nameaskey="0" or nameaskey="1"
  url = "";
}


/// Преобразование экземпляра класса в строку
QString Channel::toString()
{
  // Описание канала
  QString result = "#EXTINF:" + QString::number(duration);

  // ID канала
  if(tvgId>0)
    {
      result += " tvg-id=\"" + QString::number(tvgId) + "\n";
    }

  // имя канала
  if(!tvgName.isEmpty())
    {
      result += " tvg-name=\"" +tvgName + "\"";
    }

  // логотип
  if(!tvgLogo.isEmpty())
    {
      result += " tvg-logo=\"" + tvgLogo + "\"";
    }

  // сдвиг
  if(tvgShift>0)
    {
      result += " tvg-shift=\"" + QString::number(tvgShift) + "\"";
    }

  // радио
  if(radio)
    {
      result += " radio=\"1\"" ;
    }

  // звуковая дорожка
  if(!audioTrack.isEmpty())
    {
      result += " audio-track=\"" + audioTrack + "\"";
    }

  // соотношение сторон
  if(!aspectRatio.isEmpty())
    {
      result += " aspect-ratio=\"" + aspectRatio + "\"";
    }

  // цензура
  if(censored)
    {
      result += " censored=\"1\"";
    }

  // возрастное ограничение
  if(ageRestriction)
    {
      result = " agerestriction=\"1\"";
    }

  // индекс в программе
  if(epgId>0)
    {
      result += " epg-id=\"" + QString::number(epgId) + "\"";
    }

  // имеет архив
  if(recordable)
    {
      result += " recordable=\"true\"";
    }

  // имя в качестве ключа
  if(nameAsKey)
    {
      result += " nameaskey=\"1\"";
    }

  // имя группы
  if(!groupName.isEmpty())
    {
      result += " group-name=\"" + groupName + "\"";
    }

  result += "\n";
  result += url + "\n";
  return result;
}


/// Установить параметры обрезки
void Channel::setCrop(int w, int h, int x, int y)
{
  crop = "";
  if(w>0 && h>0)
    {
      crop = QString::number(w) + "*" + QString::number(h);
      if(x>0)
        crop += "+" + QString::number(x);
      if(y>0)
        crop += "+" + QString::number(y);
    }
}


/// Установить параметры соотношения сторон
void Channel::setAspectRatio(int w, int h)
{
  aspectRatio = "";
  if(w>0 && h>0)
    {
      aspectRatio = QString::number(w) + ":" + QString::number(h);
    }
}


/// Перегрузка оператора присваивания
Channel &Channel::operator=(const Channel source)
{
  duration = source.duration;
  tvgId = source.tvgId;
  tvgName = source.tvgName;
  tvgLogo = source.tvgLogo;
  tvgShift = source.tvgShift;
  groupName = source.groupName;
  radio = source.radio;
  audioTrack = source.audioTrack;
  censored = source.censored;
  epgId = source.epgId;
  recordable = source.recordable;
  ageRestriction = source.ageRestriction;
  nameAsKey = source.nameAsKey;
  url = source.url;
  aspectRatio = source.aspectRatio;
  crop = source.crop;

  return *this;
}


/// Увеличить текущее значение положения канала
int Channel::incOrder()
{
  return ++order;
}


/// Уменьшить текущее значение положения канала
int Channel::decOrder()
{
  return --order;
}


/// Установить текущее значение положения канала
void Channel::setOrder(int o)
{
  order = o;
}


/// Получить текущее значение положения канала
int Channel::getOrder()
{
  return order;
}
