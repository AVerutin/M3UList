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
              PlayList p = getListTitle(line);
              list = p;
            }

          /// Заголовок канала
          else if(line.startsWith("#EXTINF"))
            {
              // Описание свойств канала
              channelPosition++;
              chan = getChannelInfo(line);
              chan.setOrder(channelPosition);

              // Поиск параметров канала при помощи регулярных выражений

            }

          /// Наименование списка
          else if(line.startsWith("#PLAYLIST"))
            {
              list.listName = getListName(line);
            }

          /// Дополнительные параметры для VLC
          else if(line.startsWith("#EXTVLCOPT"))
            {

            }

          /// Ссылка на источник канал
          else
            {
              // Ссылка на источник канала
              chan.url = line;
              list.channels->append(chan);
            }
        }

      listFile->close();
    }

  return list;
}


/// Разбор параметров заголовка списка воспроизведения
PlayList Parser::getListTitle(QString listTitle)
{
  PlayList result;
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
          result.setAspectRatio(ratio);
        }

      // crop="..."
      re = QRegExp("crop=\"(.*)\"");
      lastPos = 0;
      while((lastPos = re.indexIn(listTitle, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString crop = re.cap(1);
          result.setCrop(crop);
        }

      // refresh="..."
      re = QRegExp("refresh=\"(.*)\"");
      lastPos = 0;
      while((lastPos = re.indexIn(listTitle, lastPos)) != -1)
        {
          lastPos += re.matchedLength();
          QString refresh = re.cap(1);
          result.refreshPeriod = refresh.toInt();
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


/// Разбор строки с параметрами канала
Channel Parser::getChannelInfo(QString chan)
{
  Channel res;
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
          res.tvgId = id.toInt();
        }
    }

  return res;
}

