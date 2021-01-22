#include "playlistparser.h"

Parser::Parser()
{
  playlistName = "";
}

Parser::Parser(QString fileName)
{
  if(!fileName.isEmpty())
    playlistName = fileName;
}

PlayList Parser::parse()
{
  PlayList list;
  Channel chan;

  listFile = new QFile(playlistName);

  if ((listFile->exists()) && (listFile->open(QIODevice::ReadOnly)))
  {
      int channelPosition = 0;

      QString line = "";
      while(!listFile->atEnd())
      {
          line = listFile->readLine();

          /// Заголовок списка
          if(line.startsWith("#EXTM3U"))
            {
              // Поиск параметров списка при помощи регулярных выражений
              PlayListInfo plInfo = getListTitle(line);

              list.setListName(plInfo.listName);
              list.setUrlTvg(plInfo.urlTvg);
              list.setTvgShift(plInfo.tvgShift);
              list.setCache(plInfo.cache);
              list.setDeinterlace(plInfo.deinterlace);
              list.setAspectRatio(plInfo.aspect);
              list.setCrop(plInfo.crop);
              list.setRefreshPeriod(plInfo.refresh);
              list.setAutoload(plInfo.autoload);
            }

          /// Заголовок канала
          else if(line.startsWith("#EXTINF"))
            {
              // Описание свойств канала
              channelPosition++;
              ChannelInfo chInfo = getChannelInfo(line);

              chan.setDuration(chInfo.duration);
              chan.setId(chInfo.id);
              chan.setTvgId(chInfo.tvgId);
              chan.setTvgName(chInfo.tvgName);
              chan.setTvgLogo(chInfo.tvgLogo);
              chan.setTvgShift(chInfo.tvgShift);
              chan.setGroupName(chInfo.groupName);
              chan.setRadio(chInfo.radio);
              chan.setAudioTrack(chInfo.audioTrack);
              chan.setAspectRatio(chInfo.aspect);
              chan.setRecordable(chInfo.recordable);
              chan.setCensored(chInfo.recordable);
              chan.setAgeRestricted(chInfo.ageRestrict);
              chan.setUrlM3u(chInfo.urlM3u);
              chan.setNameAsKey(chInfo.nameAsKey);
              chan.setCrop(chInfo.crop);
              chan.setMono(chInfo.mono);
              chan.setOrder(channelPosition);

              // Поиск параметров канала при помощи регулярных выражений

            }

          /// Наименование списка
          else if(line.startsWith("#PLAYLIST"))
            {
              list.setListName(getListName(line));
            }

          /// Дополнительные параметры для VLC
          else if(line.startsWith("#EXTVLCOPT"))
            {
              VlcInfo vlc = getVlcOpt(line);
              chan.setUserAgent(vlc.userAgent);
              chan.setHttpReffer(vlc.httpReferrer);
            }

          /// Ссылка на источник канал
          else
            {
              // Ссылка на источник канала
              chan.getUrl() = line;
              list.addChannel(chan);
            }
        }

      listFile->close();
    }

  return list;
}


/// Разбор параметров заголовка списка воспроизведения
PlayListInfo Parser::getListTitle(QString listTitle)
{
  PlayListInfo result;
  if(!listTitle.isEmpty())
    {
      // Анализируем строку на наличие параметров списка

      // url-tvg="..." или url-xml="..."
      QRegExp re("url-tvg=\"(.*)\"");
      re.setMinimal(true);
      int lastPos = 0;
      while((lastPos = re.indexIn(listTitle, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString url = re.cap(1);
          result.urlTvg = url;
        }

      re = QRegExp("url-xml=\"(.*)\"");
      re.setMinimal(true);
      lastPos = 0;
      while((lastPos = re.indexIn(listTitle, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString url = re.cap(1);
          result.urlTvg = url;
        }

      // cache="..."
      re = QRegExp("cache=\"(.*)\"");
      lastPos = 0;
      while((lastPos = re.indexIn(listTitle, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString cache = re.cap(1);
          result.cache = cache.toInt();
        }

      // deinterlace="..."
      re = QRegExp("deinterlace=\"(.*)\"");
      lastPos = 0;
      while((lastPos = re.indexIn(listTitle, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString deinterlace = re.cap(1);
          result.deinterlace = deinterlace.toInt();
        }

      // aspect-ratio="..."
      re = QRegExp("aspect-ratio=\"(.*)\"");
      lastPos = 0;
      while((lastPos = re.indexIn(listTitle, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString ratio = re.cap(1);
          result.aspect = ratio;
        }

      // crop="..."
      re = QRegExp("crop=\"(.*)\"");
      lastPos = 0;
      while((lastPos = re.indexIn(listTitle, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString crop = re.cap(1);
          result.crop = crop;
        }

      // refresh="..."
      re = QRegExp("refresh=\"(.*)\"");
      lastPos = 0;
      while((lastPos = re.indexIn(listTitle, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString refresh = re.cap(1);
          result.refresh = refresh.toInt();
        }

      // m3uautoload=1
      re = QRegExp("m3uautoload=\"(.*)\"");
      lastPos = 0;
      while((lastPos = re.indexIn(listTitle, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString autoload = re.cap(1);
          result.autoload = (bool)autoload.toInt();
        }

      // tvg-shift=(...-2, -1, 0, +1, +2, ...)
      re = QRegExp("tvg-shift=\"(.*)\"");
      lastPos = 0;
      while((lastPos = re.indexIn(listTitle, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString shift = re.cap(1);
          result.tvgShift = shift.toInt();
        }
    }

  return result;
}


/// Разбор строки с наименованием списка воспроизведения
QString Parser::getListName(QString name)
{
  QString res;
  QRegExp re("#PLAYLIST:(.*)");
  int lastPos = 0;

  while((lastPos = re.indexIn(name, lastPos)) != -1)
    {
      lastPos += re.matchedLength();
      res = re.cap(1);
    }

  return res;
}


/// Разбор строки с параметрами VLC
VlcInfo Parser::getVlcOpt(QString vlc)
{
  VlcInfo res;
  QRegExp re("#EXTVLCOPT:http-user-agent=(.*)");
  int lastPos = 0;

  while((lastPos = re.indexIn(vlc, lastPos)) != -1)
    {
      lastPos += re.matchedLength();
      res.userAgent = re.cap(1);
    }

  re = QRegExp("#EXTVLCOPT:http-referrer=(.*)");
  lastPos = 0;

  while((lastPos = re.indexIn(vlc, lastPos)) != -1)
    {
      lastPos += re.matchedLength();
      res.httpReferrer = re.cap(1);
    }

  return res;
}


/// Разбор строки с параметрами канала
ChannelInfo Parser::getChannelInfo(QString chan)
{
  ChannelInfo res;
  if(!chan.isEmpty())
    {
      // Анализируем строку на наличие параметров списка

      // #EXTINF:...
      QRegExp re("#EXTINF:([-|\\d]*)\\b");

      int lastPos = 0;
      while((lastPos = re.indexIn(chan, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString id = re.cap(1);
          res.duration = id.toInt();
        }

      // tvg-id="..."
      re = QRegExp("tvg-id=\"(.*)\"");

      lastPos = 0;
      while((lastPos = re.indexIn(chan, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString id = re.cap(1);
          res.id = id.toInt();
        }
    }

  return res;
}

