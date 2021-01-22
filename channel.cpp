#include "channel.h"

Channel::Channel()
{
  order = -1;
  channelInfo = new ChannelInfo;
  vlcInfo = new VlcInfo;

  aspectRatio = "";
  crop = "";
  url = "";
}


/// Преобразование экземпляра класса в строку
QString Channel::toString()
{
  bool needComma = false;

  // Описание канала
  QString result = "#EXTINF:" + QString::number(channelInfo->duration);

  // ID канала
  if(channelInfo->tvgId>0)
    {
      result += " tvg-id=\"" + channelInfo->tvgId + "\n";
      needComma = true;
    }

  // имя канала
  if(!channelInfo->tvgName.isEmpty())
    {
      result += " tvg-name=\"" + channelInfo->tvgName + "\"";
      needComma = true;
    }

  // логотип
  if(!channelInfo->tvgLogo.isEmpty())
    {
      result += " tvg-logo=\"" + channelInfo->tvgLogo + "\"";
      needComma = true;
    }

  // сдвиг
  if(channelInfo->tvgShift>0)
    {
      result += " tvg-shift=\"" + QString::number(channelInfo->tvgShift) + "\"";
      needComma = true;
    }

  // радио
  if(channelInfo->radio)
    {
      result += " radio=\"1\"" ;
      needComma = true;
    }

  // звуковая дорожка
  if(!channelInfo->audioTrack.isEmpty())
    {
      result += " audio-track=\"" + channelInfo->audioTrack + "\"";
      needComma = true;
    }

  // соотношение сторон
  if(!aspectRatio.isEmpty())
    {
      result += " aspect-ratio=\"" + aspectRatio + "\"";
      needComma = true;
    }

  // цензура
  if(channelInfo->censored)
    {
      result += " censored=\"1\"";
      needComma = true;
    }

  // возрастное ограничение
  if(channelInfo->ageRestrict)
    {
      result = " agerestriction=\"1\"";
      needComma = true;
    }

  // имеет архив
  if(channelInfo->recordable)
    {
      result += " recordable=\"true\"";
      needComma = true;
    }

  // имя в качестве ключа
  if(channelInfo->nameAsKey)
    {
      result += " nameaskey=\"1\"";
      needComma = true;
    }

  // имя группы
  if(!channelInfo->groupName.isEmpty())
    {
      result += " group-name=\"" + channelInfo->groupName + "\"";
      needComma = true;
    }

  if(!channelInfo->tvgName.isEmpty())
    {
      if(needComma)
        result += ",";

      result += channelInfo->tvgName;
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

void Channel::setCrop(const QString &cr)
{
  if(!cr.isEmpty())
    crop = cr;
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

void Channel::setAspectRatio(const QString &aspect)
{
  if(!aspect.isEmpty())
    aspectRatio = aspect;
}


/// Перегрузка оператора присваивания
Channel &Channel::operator=(const Channel &source)
{
  channelInfo->duration = source.channelInfo->duration;
  channelInfo->tvgId = source.channelInfo->tvgId;
  channelInfo->tvgName = source.channelInfo->tvgName;
  channelInfo->tvgLogo = source.channelInfo->tvgLogo;
  channelInfo->tvgShift = source.channelInfo->tvgShift;
  channelInfo->groupName = source.channelInfo->groupName;
  channelInfo->radio = source.channelInfo->radio;
  channelInfo->audioTrack = source.channelInfo->audioTrack;
  channelInfo->censored = source.channelInfo->censored;
  channelInfo->recordable = source.channelInfo->recordable;
  channelInfo->ageRestrict = source.channelInfo->ageRestrict;
  channelInfo->nameAsKey = source.channelInfo->nameAsKey;
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


/// Юзер агент
void Channel::setUserAgent(const QString &uAgent)
{
  if(!uAgent.isEmpty())
    vlcInfo->userAgent = uAgent;
}

QString Channel::getUserAgent()
{
  return vlcInfo->userAgent;
}


/// Http Refferer
void Channel::setHttpReffer(const QString &ref)
{
  if(!ref.isEmpty())
    vlcInfo->httpReferrer = ref;
}

QString Channel::getHttpReffer()
{
  return vlcInfo->httpReferrer;
}


/// Ссылка на поток
void Channel::setUrl(const QString &u)
{
  if(!u.isEmpty())
    url = u;
}

QString Channel::getUrl()
{
  return url;
}


/// Продолжительность
void Channel::setDuration(int duration)
{
  channelInfo->duration = duration;
}

int Channel::getDuration()
{
  return channelInfo->duration;
}


/// Идентификатор канала
void Channel::setId(int id)
{
  channelInfo->id = id;
}

int Channel::getId()
{
  return channelInfo->id;
}


/// Идентификатор канала для телегида
void Channel::setTvgId(const QString &tId)
{
  if(!tId.isEmpty())
    channelInfo->tvgId = tId;
}

QString Channel::getTvgId()
{
  return channelInfo->tvgId;
}


/// Отображаемое имя канала
void Channel::setTvgName(const QString &name)
{
  if(!name.isEmpty())
    channelInfo->tvgName = name;
}

QString Channel::getTvgName()
{
  return channelInfo->tvgName;
}


/// Логотип канала
void Channel::setTvgLogo(const QString &logo)
{
  if(!logo.isEmpty())
    channelInfo->tvgLogo = logo;
}

QString Channel::getTvgLogo()
{
  return channelInfo->tvgLogo;
}


/// Смещение времени канала
void Channel::setTvgShift(int shift)
{
  channelInfo->tvgShift = shift;
}

int Channel::getTvgShift()
{
  return channelInfo->tvgShift;
}


/// Наименование группы
void Channel::setGroupName(const QString &grpName)
{
  if(!grpName.isEmpty())
    channelInfo->groupName = grpName;
}

QString Channel::getGroupName()
{
  return channelInfo->groupName;
}


/// Канал без видео (радио)
void Channel::setRadio(bool radio)
{
  channelInfo->radio = radio;
}

bool Channel::isRadio()
{
  return channelInfo->radio;
}


/// Канал имеет архив передач
void Channel::setRecordable(bool rec)
{
  channelInfo->recordable = rec;
}

bool Channel::isRecordable()
{
  return channelInfo->recordable;
}


/// Содержит материал для взрослых
void Channel::setCensored(bool censored)
{
  channelInfo->censored = censored;
}

bool Channel::isCensored()
{
  return channelInfo->censored;
}


/// Подвержен возрастному ограничению
void Channel::setAgeRestricted(bool restrict)
{
  channelInfo->ageRestrict = restrict;
}

bool Channel::isAgeRestricted()
{
  return channelInfo->ageRestrict;
}


/// Использовать имя канала для привязки телепрограммы
void Channel::setNameAsKey(bool useName)
{
  channelInfo->nameAsKey = useName;
}

bool Channel::isNameAsKey()
{
  return channelInfo->nameAsKey;
}


/// Монофонический звук
void Channel::setMono(bool mono)
{
  channelInfo->mono = mono;
}

bool Channel::isMono()
{
  return channelInfo->mono;
}


/// Используемая звуковоая дорожка
void Channel::setAudioTrack(const QString &audio)
{
  if(!audio.isEmpty())
    channelInfo->audioTrack = audio;
}

QString Channel::getAudioTrack()
{
  return channelInfo->audioTrack;
}


/// Новый адрес списка каналов
void Channel::setUrlM3u(const QString &m3u)
{
  if(!m3u.isEmpty())
    channelInfo->urlM3u = m3u;
}

QString Channel::getUrlM3u()
{
  return channelInfo->urlM3u;
}


