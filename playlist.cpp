#include "playlist.h"

PlayList::PlayList()
{
  listName = "Noname playlist";
  urlTvg = "http://epg.it999.ru/edem.xml.gz";
  userAgent = "";
  autoload = true;
  cache = 500;
  deinterlace = 0;
  tvgShift = 0;
  aspectWidth = 16;
  aspectHeight = 9;
  cropWidth = 0;
  cropHeight = 0;
  cropTop = 0;
  cropLeft = 0;
  refreshPeriod = 0;
  crop = "";
  aspect = "";

  channels = new QList<Channel>;
  channelUid = 0;
}

// Перегрузка оператора присваивания
PlayList &PlayList::operator=(const PlayList source)
{
  // получение параметров свойств списка
  listName = source.listName;
  urlTvg = source.urlTvg;
  autoload = source.autoload;
  cache = source.cache;
  deinterlace = source.deinterlace;
  refreshPeriod = source.refreshPeriod;
  tvgShift = source.tvgShift;
  userAgent = source.userAgent;
  cropWidth = source.cropWidth;
  cropHeight = source.cropHeight;
  cropTop = source.cropTop;
  cropLeft = source.cropLeft;
  aspectWidth = source.aspectWidth;
  aspectHeight = source.aspectHeight;
  channels = new QList<Channel>;

  // получение списка каналов
  for(QList<Channel>::iterator it=channels->begin(); it!=channels->end(); it++)
    {
      channels->append(*it);
    }

  return *this;
}

QString PlayList::toString()
{
  QString result;

  // Заголовок листа
  if(!listName.isEmpty())
    {
      result += "#PLAYLIST: " + listName + "\n";
    }

  // юзер-агент
  if(!userAgent.isEmpty())
    {
      result += "#EXTVLCOPT:http-user-agent=" + userAgent + "\n";
    }

  // Описание листа
  result += "#EXTM3U";

  // Ссылка на программу передач
  if(!urlTvg.isEmpty())
    {
      result += " url-tvg=\"" + urlTvg + "\n";
    }

  // автозагрузка
  if(autoload)
    {
      result += " m3uautoload=\"1\"";
    }

  // кеш
  if(cache>0)
    {
      result += " cache=\"" + QString::number(cache) + "\"";
    }

  // деинтерлейс
  if(deinterlace>0)
    {
      result += " deinterlace=\"" + QString::number(deinterlace) + "\"";
    }

  // соотношение сторон
  if(!aspect.isEmpty())
    {
      result += " aspect-ratio=\"" + aspect + "\"";
    }

  // сдвиг времени
  if(tvgShift>0)
    {
      result += " tvg-shift=\"" + QString::number(tvgShift) + "\"";
    }

  // обрезка кадра
  if(!crop.isEmpty())
    {
      result += " crop=\"" + crop + "\"";
    }

  // период обновления
  if(refreshPeriod>0)
    {
      result += " refresh=\"" + QString::number(refreshPeriod) + "\"";
    }

  // Завершение описания листа
  result += "\n";

  // Добавляем описание каналов
  QList<Channel>::iterator i;
  for(i=channels->begin(); i!=channels->end(); i++)
    {
      result += i->toString();
    }

  return result;
}


/// Установить строковое значение обрезки
void PlayList::setCrop()
{
  if(cropWidth>0 && cropHeight>0)
    {
      crop = QString::number(cropWidth) + "*" + QString::number(cropHeight);
      if(cropTop>0)
        crop += "+" + QString::number(cropTop);
      if(cropLeft>0)
        crop += "+" + QString::number(cropLeft);
    }
}


/// Установить строковое значение соотношения сторон
void PlayList::setAspectRatio()
{
  if(aspectWidth>0 && aspectHeight>0)
    {
      aspect = QString::number(aspectWidth) + "*" + QString::number(aspectHeight);
    }
}


/// Установить обрезку кадра
void PlayList::setCrop(int w, int h, int t, int l)
{
  if(w>0)
    cropWidth = w;
  if(h>0)
    cropHeight = h;
  if(t>0)
    cropTop = t;
  if(l>0)
    cropLeft = l;

  setCrop();
}


/// Установить обрезку по ширине
void PlayList::setCropWidth(int w)
{
  if(w>0)
    cropWidth = w;

  setCrop();
}


/// Установить обрезку по высоте
void PlayList::setCropHeight(int h)
{
  if(h>0)
    cropHeight = h;

  setCrop();
}


/// Установить обрезку сверху
void PlayList::setCropTop(int t)
{
  if(t>0)
    cropTop = t;

  setCrop();
}


/// Установить обрезку слева
void PlayList::setCropLeft(int l)
{
  if(l>0)
    cropLeft = l;

  setCrop();
}


/// Установить обрезку кадра из строки
void PlayList::setCrop(QString c)
{
  if(!c.isEmpty())
    crop = c;
}


/// Получить обрезку кадра
QString PlayList::getCrop()
{
  return crop;
}


/// Установить соотношение сторон
void PlayList::setAspectRatio(int w, int h)
{
  if(w>0)
    aspectWidth = w;
  if(h>0)
    aspectHeight = h;

  setAspectRatio();
}


/// Установить ширину соотношения сторон
void PlayList::setAspectRatioWidth(int w)
{
  if(w>0)
    aspectWidth = w;

  setAspectRatio();
}


/// Установить высоту соотношения сторон
void PlayList::setAspectRatioHeight(int h)
{
  if(h>0)
    aspectHeight = h;

  setAspectRatio();
}


/// Установить соотношение сторон
void PlayList::setAspectRatio(QString ratio)
{
  if(!ratio.isEmpty())
    aspect = ratio;
}


/// Получить соотношение сторон
QString PlayList::getAspectRatio()
{
  return aspect;
}


/// Добавить канал в список каналов
int PlayList::addChannel(const Channel ch)
{
  int uid = 1;
  QList<Channel>::iterator it;
  for(it=channels->begin(); it!=channels->end(); it++)
    {
      if(it->tvgId > uid)
        uid = it->tvgId;
    }

  Channel item = ch;
  item.tvgId = uid;
  channels->append(item);

  return uid;
}


/// Правка канала
Channel PlayList::editChannel(const Channel ch)
{
  Channel res = ch;

  return res;
}


/// Удалить канал по номеру позиции в списке
bool PlayList::deleteChannelAt(int)
{
  return false;
}


/// Удалить канал по идентификатору
bool PlayList::deleteChannel(int)
{
  return false;
}


/// Получить количество каналов
int PlayList::getChannelsCount()
{
  return channels->size();
}


/// Получить канал по его номеру
Channel PlayList::getChannelAt(int pos)
{
  Channel res;
  if(pos <= channels->size())
    res = channels->at(pos);

  return res;
}


/// Получить канал по его идентификатору
Channel PlayList::getChannel(int uid)
{
  Channel res;
  for(int i=0; i<channels->size(); i++)
    if(channels->at(i).tvgId == uid)
      {
        res = channels->at(i);
        break;
      }

  return res;
}

