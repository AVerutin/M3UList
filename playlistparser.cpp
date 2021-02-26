#include "playlistparser.h"

Parser::Parser()
{
  playlistName = "";
  logger = new Logger;
}

Parser::Parser(QString fileName)
{
  if(!fileName.isEmpty())
    playlistName = fileName;
  logger = new Logger;
}



/// Анализ файла списка воспроизведения
PlayList Parser::parse()
{
  PlayList list;
  Channel *chan = nullptr;

  listFile = new QFile(playlistName);
  if ((listFile->exists()) && (listFile->open(QIODevice::ReadOnly)))
  {
      int channelPosition = 0;
      QString line = "";
      while(!listFile->atEnd())
      {
          line = listFile->readLine().trimmed();
          if(line.isEmpty())
            continue;

          /// Заголовок списка
          if(line.startsWith("#EXTM3U"))
            {
              // Поиск параметров списка при помощи регулярных выражений
              PlayListInfo plInfo = getListTitle(line);

              list.setUrlTvg(plInfo.urlTvg);
              list.setTvgShift(plInfo.tvgShift);
              list.setCache(plInfo.cache);
              list.setDeinterlace(plInfo.deinterlace);
              list.setAspectRatio(plInfo.aspect);
              list.setCrop(plInfo.crop);
              list.setRefreshPeriod(plInfo.refresh);
              list.setAutoload(plInfo.autoload);

//              QString unitName = typeid(this).name();
//              logger->info("Открыт список: " + list.getListName(), unitName);
            }

          /// Заголовок канала
          else if(line.startsWith("#EXTINF"))
            {
              // Описание свойств канала
              ChannelInfo chInfo = getChannelInfo(line);
              if(chan==nullptr)
                chan = new Channel;

              channelPosition++;
              chan->setDuration(chInfo.duration);
              chan->setTvgId(chInfo.tvgId);
              chan->setTvgName(chInfo.tvgName);
              chan->setName(chInfo.name);
              chan->setTvgLogo(chInfo.tvgLogo);
              chan->setTvgShift(chInfo.tvgShift);
              chan->setGroupName(chInfo.groupName);
              chan->setRadio(chInfo.radio);
              chan->setAudioTrack(chInfo.audioTrack);
              chan->setAspectRatio(chInfo.aspect);
              chan->setRecordable(chInfo.recordable);
              chan->setCensored(chInfo.recordable);
              chan->setAgeRestricted(chInfo.ageRestrict);
              chan->setUrlM3u(chInfo.urlM3u);
              chan->setNameAsKey(chInfo.nameAsKey);
              chan->setCrop(chInfo.crop);
              chan->setMono(chInfo.mono);
              chan->setOrder(channelPosition);
              chan->setId(channelPosition);
//              chan->setNumber(channelPosition);

//              QString unitName = typeid(this).name();
//              logger->info("Получен канал: [" + QString::number(chan->getId()) + "] " + chan->getName(), unitName);
            }

          /// Наименование списка
          else if(line.startsWith("#PLAYLIST"))
            {
              QString listName = getListName(line);
              list.setListName(listName);
            }

          /// Наименование группы
          else if(line.startsWith("#EXTGRP"))
            {
              if(chan==nullptr)
                chan = new Channel;

              QString groupName = getGroupName(line);
              chan->setGroupName(groupName);
            }

          /// Дополнительные параметры для VLC
          else if(line.startsWith("#EXTVLCOPT"))
            {
              if(chan==nullptr)
                chan = new Channel;

              VlcInfo vlc = getVlcOpt(line);
              chan->setUserAgent(vlc.userAgent);
              chan->setHttpReffer(vlc.httpReferrer);
            }

          /// Ссылка на источник канал
          else if(line.contains("://"))
            {
              // Ссылка на источник канала
              if(chan==nullptr)
                chan = new Channel;

              chan->setUrl(line);
              list.addChannel(*chan);

              delete chan;
              chan = nullptr;
            }
        }

      listFile->close();
    }

  return list;
}



/// Разбор параметров заголовка списка воспроизведения
PlayListInfo Parser::getListTitle(const QString &listTitle)
{
  PlayListInfo result;
  if(!listTitle.isEmpty())
    {
      // Анализируем строку на наличие параметров списка
      qDebug() << listTitle;

      // url-tvg="..." или url-xml="..." url-tvg=\"(.+?)\"
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
      re = QRegExp("cache=\"*(\\d*)\"*");
      lastPos = 0;
      while((lastPos = re.indexIn(listTitle, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString cache = re.cap(1);
          result.cache = cache.toInt();
        }

      // deinterlace="..."
      re = QRegExp("deinterlace=\"*(\\d*)?\"*");
      lastPos = 0;
      while((lastPos = re.indexIn(listTitle, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString deinterlace = re.cap(1);
          result.deinterlace = deinterlace.toInt();
        }

      // aspect-ratio="..."
      re = QRegExp("aspect-ratio=\"*(\\d+:\\d+)?\"*");
      lastPos = 0;
      while((lastPos = re.indexIn(listTitle, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString ratio = re.cap(1);
          result.aspect = ratio;
        }

      // crop="..."
      re = QRegExp("crop=\"(.*)\"\\s");
      lastPos = 0;
      while((lastPos = re.indexIn(listTitle, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString crop = re.cap(1);
          result.crop = crop;
        }

      // refresh="..."
      re = QRegExp("refresh=\"*(\\d*)?\"*");
      lastPos = 0;
      while((lastPos = re.indexIn(listTitle, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString refresh = re.cap(1);
          result.refresh = refresh.toInt();
        }

      // m3uautoload=1
      re = QRegExp("m3uautoload=\"*(\\d?)?\"*");
      lastPos = 0;
      while((lastPos = re.indexIn(listTitle, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString autoload = re.cap(1);
          result.autoload = (bool)autoload.toInt();
        }

      // tvg-shift=(...-2, -1, 0, +1, +2, ...)
      re = QRegExp("tvg-shift=\"*([+|-]?\\d?)?\"*");
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



/// Разбор строки с наименованием группы
QString Parser::getGroupName(const QString &grpName)
{
  QString res;
  QRegExp re("#EXTGRP:(.*)");
  int lastPos = 0;

  while((lastPos = re.indexIn(grpName, lastPos)) != -1)
    {
      lastPos += re.matchedLength();
      res = re.cap(1);
    }

  return res;
}



/// Разбор строки с наименованием списка воспроизведения
QString Parser::getListName(const QString &name)
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
VlcInfo Parser::getVlcOpt(const QString &vlc)
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
ChannelInfo Parser::getChannelInfo(const QString &chan)
{
  ChannelInfo res;
  if(!chan.isEmpty())
    {
      // Анализируем строку на наличие параметров списка

      // #EXTINF:...
      QRegExp re("#EXTINF:([+,-]?[0-9]+)");
      int lastPos = 0;
      while((lastPos = re.indexIn(chan, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString val = re.cap(1);
          res.duration = val.toInt();
        }

      // tvg-id="..."
      re = QRegExp("tvg-id=(\"|')([^\"']+)");
      lastPos = 0;
      while((lastPos = re.indexIn(chan, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString val = re.cap(2);
          res.tvgId = val;
        }

      // tvg-name="..."
      re = QRegExp("tvg-name=(\"|')([^\"']+)");
      lastPos = 0;
      while((lastPos = re.indexIn(chan, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString val = re.cap(2);
          res.tvgName = val;
        }

      // tvg-logo="..."
      re = QRegExp("tvg-logo=(\"|')([^\"']+)");
      lastPos = 0;
      while((lastPos = re.indexIn(chan, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString val = re.cap(2);
          res.tvgLogo = val;
        }

      // tvg-epg="..."
      re = QRegExp("tvg-epg=(\"|')([^\"']+)");
      lastPos = 0;
      while((lastPos = re.indexIn(chan, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString val = re.cap(2);
          res.tvgEpg = val;
        }

      // tvg-shift="..."
      re = QRegExp("tvg-shift=(\"|')([^\"']+)");
      lastPos = 0;
      while((lastPos = re.indexIn(chan, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString val = re.cap(2);
          res.tvgShift = val.toInt();
        }

      // group-title="..."
      re = QRegExp("group-title=(\"|')([^\"']+)");
      lastPos = 0;
      while((lastPos = re.indexIn(chan, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString val = re.cap(2);
          res.groupName = val;
        }

      // radio="..."
      re = QRegExp("radio=(\"|')([^\"']+)");
      lastPos = 0;
      while((lastPos = re.indexIn(chan, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString val = re.cap(2);
          res.radio = val.toInt();
        }

      // aspect-ratio="..."
      re = QRegExp("aspect-ratio=(\"|')([^\"']+)");
      lastPos = 0;
      while((lastPos = re.indexIn(chan, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString val = re.cap(2);
          res.aspect = val;
        }

      // audio-track="..."
      re = QRegExp("audio-track=(\"|')([^\"']+)");
      lastPos = 0;
      while((lastPos = re.indexIn(chan, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString val = re.cap(2);
          res.audioTrack = val;
        }

      // recordable="..."
      re = QRegExp("recordable=(\"|')([^\"']+)");
      lastPos = 0;
      while((lastPos = re.indexIn(chan, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString val = re.cap(2);
          res.recordable = val=="true" ? true : false;
        }

      // censored="..."
      re = QRegExp("censored=(\"|')([^\"']+)");
      lastPos = 0;
      while((lastPos = re.indexIn(chan, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString val = re.cap(2);
          res.censored = val.toInt();
        }

      // agerestriction="..."
      re = QRegExp("agerestriction=(\"|')([^\"']+)");
      lastPos = 0;
      while((lastPos = re.indexIn(chan, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString val = re.cap(2);
          res.ageRestrict = val.toInt();
        }

      // url-m3u="..."
      re = QRegExp("url-m3u=(\"|')([^\"']+)");
      lastPos = 0;
      while((lastPos = re.indexIn(chan, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString val = re.cap(2);
          res.urlM3u = val;
        }

      // nameaskey="..."
      re = QRegExp("nameaskey=(\"|')([^\"']+)");
      lastPos = 0;
      while((lastPos = re.indexIn(chan, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString val = re.cap(2);
          res.nameAsKey = val.toInt();
        }

      // crop="..."
      re = QRegExp("crop=(\"|')([^\"']+)");
      lastPos = 0;
      while((lastPos = re.indexIn(chan, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString val = re.cap(2);
          res.crop = val;
        }

      // mono="..."
      re = QRegExp("mono=(\"|')([^\"']+)");
      lastPos = 0;
      while((lastPos = re.indexIn(chan, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString val = re.cap(2);
          res.mono = val.toInt();
        }

      // Название канала после запятой
      re = QRegExp(",([^\n]*)");
      lastPos = 0;
      while((lastPos = re.indexIn(chan, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString val = re.cap(1);
          res.name = val;
        }
    }

  return res;
}

