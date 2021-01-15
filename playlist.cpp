#include "playlist.h"

PlayList::PlayList()
{
  listName = "Noname playlist";
  urlTvg = "http://epg.it999.ru/edem.xml.gz";
  userAgent = "";
  autoload = true;
  cache = 500;
  deinterlace = 1;
  tvgShift = 0;
  aspectRatio = "16:9";
  crop = "";
  refreshPeriod = 0;

  channels = new QList<Channel>;
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
  crop = source.crop;
  aspectRatio = source.aspectRatio;
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
  if(!aspectRatio.isEmpty())
    {
      result += " aspect-ratio=\"" + aspectRatio + "\"";
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

void PlayList::setCrop(int w, int h, int x, int y)
{
  crop = "";
  if(w>0 && h>0)
    {
      crop = QString::number(w) + "*" + QString::number(h);

      if(x+0)
        crop += "+" + QString::number(x);
      if(y>0)
        crop += "+" + QString::number(y);
    }

}

void PlayList::setAspectRatio(int w, int h)
{
  aspectRatio = "";

  if(w>0 && h>0)
    {
      aspectRatio = QString::number(w) + ":" + QString::number(h);
    }
}
