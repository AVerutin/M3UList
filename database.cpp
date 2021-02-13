#include "database.h"

/// Конструктор по умолчанию
DataBase::DataBase()
{

}


/// Инициализация базы данных
void DataBase::dbInit()
{
  sdb = QSqlDatabase::addDatabase("QSQLITE");
  QString dbPath = QCoreApplication::applicationDirPath() + "/m3u.dat";
  sdb.setDatabaseName(dbPath);
  query = new QSqlQuery;

//  sdb = QSqlDatabase::addDatabase("QSQLITE");
//  sdb.setDatabaseName("m3u.dat");
//  sdb.setHostName("localhost");
//  sdb.setUserName("admin");
//  sdb.setPassword("admin");

  // Подключение к базе данных
  if (!sdb.open()) {
        qDebug() << sdb.lastError().text();
  }

  /////////// DDL query ///////////
  QString str = "CREATE TABLE IF NOT EXISTS `groups` ("
          "`id` INTEGER PRIMARY KEY AUTOINCREMENT, "
          "`group` VARCHAR(50) "
          ");";
  bool b = query->exec(str);
  if (!b)
    {
      qDebug() << sdb.lastError().text();
    }

  str = "CREATE TABLE IF NOT EXISTS `tracks` ("
          "`id` INTEGER PRIMARY KEY AUTOINCREMENT, "
          "`track` VARCHAR(2) "
          ");";
  b = query->exec(str);
  if (!b)
    {
      qDebug() << sdb.lastError().text();
    }

  str = "CREATE TABLE `channels` ("
        "`id`	INTEGER NOT NULL, "
        "`playlist`	INTEGER NOT NULL, "
        "`name`	TEXT NOT NULL, "
        "`source`	INTEGER NOT NULL, "
        "`position`	INTEGER NOT NULL DEFAULT 0, "
        "`crop`	INTEGER, "
        "`aspect`	TEXT, "
        "`user_agent`	TEXT, "
        "`http_reffer`	TEXT, "
        "`duration`	INTEGER NOT NULL DEFAULT 0, "
        "`tvg_name`	TEXT, "
        "`tvg_logo`	TEXT, "
        "`tvg_shift`	INTEGER, "
        "`tvg_group`	TEXT, "
        "`tvg_epg`	TEXT, "
        "`radio`	INTEGER, "
        "`recorded`	INTEGER, "
        "`consored`	INTEGER, "
        "`age_restricred`	INTEGER, "
        "`mono`	INTEGER, "
        "`name_as_key`	INTEGER, "
        "`audio`	INTEGER, "
        "PRIMARY KEY(`id` AUTOINCREMENT));";
  b = query->exec(str);
  if (!b)
    {
      qDebug() << sdb.lastError().text();
    }

  str = "CREATE TABLE `playlists` ("
        "`id`	INTEGER NOT NULL, "
        "`name`	TEXT NOT NULL, "
        "`url_tvg`	TEXT, "
        "`cache`	INTEGER, "
        "`crop`		TEXT, "
        "`aspect`	TEXT, "
        "`autoload`	INTEGER, "
        "`deinterlace`	INTEGER, "
        "`refresh`	INTEGER, "
        "`shift`	INTEGER, "
        "PRIMARY KEY(`id` AUTOINCREMENT));";
  b = query->exec(str);
  if (!b)
    {
      qDebug() << sdb.lastError().text();
    }

  str = "CREATE INDEX `channels_id` ON `channels` (`id`	ASC);";
  b = query->exec(str);
  if (!b)
    {
      qDebug() << sdb.lastError().text();
    }

  str = "CREATE INDEX `playlists_id` ON `playlists` (`id`);";
  b = query->exec(str);
  if (!b)
    {
      qDebug() << sdb.lastError().text();
    }

  /////////// Data query ///////////
  if (!query->exec("SELECT count(*) as rows_cnt FROM `groups`;"))
    {
      qDebug() << sdb.lastError().text();
    }

  QSqlRecord rec = query->record();
  int cnt = 0;

  while (query->next())
    {
      cnt = query->value(rec.indexOf("rows_cnt")).toInt();
      if(cnt==0)
        {
          addGroup("Общие");
          addGroup("Информационные");
          addGroup("Образовательные");
          addGroup("Познавательные");
          addGroup("Детские");
          addGroup("Фильмы");
          addGroup("Региональные");
        }
    }

  if (!query->exec("SELECT count(*) as rows_cnt FROM `tracks`;"))
    {
      qDebug() << sdb.lastError().text();
    }

  rec = query->record();
  while (query->next())
    {
      cnt = query->value(rec.indexOf("rows_cnt")).toInt();
      if(cnt==0)
        {
          addTrack("RU");
          addTrack("EN");
          addTrack("UA");
        }
    }
}


/// Закрыть подключение к базе данных
void DataBase::dbClose()
{
  sdb.close();
}


/// Получить список групп из базы данных
QStringList DataBase::getGroups()
{
  QStringList result;
  if (!query->exec("SELECT `group` FROM `groups` ORDER BY `group`;"))
    {
      qDebug() << sdb.lastError().text();
    }

  QSqlRecord rec = query->record();
  QString grp = "";

  while (query->next())
    {
      grp = query->value(rec.indexOf("group")).toString();
      result.append(grp);
    }

  return result;
}


/// Добавить группу в базу данных
bool DataBase::addGroup(const QString &grpName)
{
  bool result = false;
  if(!grpName.isEmpty())
    {
      QString queryString = "INSERT INTO `groups` (`group`) "
              "VALUES ('%1');";
      queryString = queryString.arg(grpName);
      result = query->exec(queryString);
      if (!result)
        {
          qDebug() << sdb.lastError().text();
        }
    }

  return result;
}


/// Добавить список групп
bool DataBase::addGroups(const QStringList &grps)
{
  bool result = false;
  if(grps.size()>0)
    {
      QString queryString = "";
      for(int i=0; i<grps.size(); i++)
        {
          queryString = "INSERT INTO `groups` (`group`) VALUES ('%1');\n";
          queryString = queryString.arg(grps.at(i));

          result = query->exec(queryString);
          if (!result)
            {
              qDebug() << sdb.lastError().text();
            }
        }
    }

  return result;
}


/// Удалить группу из базы данных
bool DataBase::removeGroup(const QString &grpName)
{
  bool result = false;
  if(!grpName.isEmpty())
    {
      QString queryString = "DELETE FROM `groups` WHERE `group` = '%1';";
      queryString = queryString.arg(grpName);
      result = query->exec(queryString);
      if (!result)
        {
          qDebug() << sdb.lastError().text();
        }
    }

  return result;
}


/// Очистить список групп
bool DataBase::clearGroups()
{
  bool result = false;
  QString queryString = "DELETE FROM `groups`;";
  result = query->exec(queryString);
  if (!result)
    {
      qDebug() << sdb.lastError().text();
    }

  return result;
}


/// Получить список звуковых дорожек из базы данных
QStringList DataBase::getTracks()
{
  QStringList result;
  if (!query->exec("SELECT `track` FROM `tracks` ORDER BY `track`;"))
    {
      qDebug() << sdb.lastError().text();
    }

  QSqlRecord rec = query->record();
  QString track = "";

  while (query->next())
    {
      track = query->value(rec.indexOf("track")).toString();
      result.append(track);
    }

  return result;
}


/// Добавить звуковую дорожку в базу данных
bool DataBase::addTrack(const QString &trackName)
{
  bool result = false;
  if(!trackName.isEmpty())
    {
      QString queryString = "INSERT INTO `tracks` (`track`) VALUES ('%1');";
      queryString = queryString.arg(trackName);
      result = query->exec(queryString);
      if (!result)
        {
          qDebug() << sdb.lastError().text();
        }
    }

  return result;
}


/// Добавить список звуковых дорожек
bool DataBase::addTracks(const QStringList &tracks)
{
  bool result = false;
  if(tracks.size()>0)
    {
      QString queryString = "";
      for(int i=0; i<tracks.size(); i++)
        {
          queryString = "INSERT INTO `tracks` (`track`) VALUES ('%1');\n";
          queryString = queryString.arg(tracks.at(i));

          result = query->exec(queryString);
          if (!result)
            {
              qDebug() << sdb.lastError().text();
            }
        }
    }

  return result;
}


/// Удалить звуковую дорожку из базы данных
bool DataBase::removeTrack(const QString &trackName)
{
  bool result = false;
  if(!trackName.isEmpty())
    {
      QString queryString = "DELETE FROM `tracks` WHERE `track` = '%1';";
      queryString = queryString.arg(trackName);
      result = query->exec(queryString);
      if (!result)
        {
          qDebug() << sdb.lastError().text();
        }
    }

  return result;
}


/// Очистить список звуковых дорожек
bool DataBase::clearTracks()
{
  bool result = false;
  QString queryString = "DELETE FROM `tracks`;";
  result = query->exec(queryString);
  if (!result)
    {
      qDebug() << sdb.lastError().text();
    }

  return result;
}


/// Добавить канал в базу данных
bool DataBase::addChannel(const PlayListInfo &playlist, const ChannelInfo &channel)
{
  bool result = false;
  if(channel.name!="" && playlist.listId!=0)
    {
      QString queryStr = "INSERT INTO `channels` ("
        "`playlist`, `name`, `source`, `position`, `crop`, `aspect`, `user_agent`, "
        "`http_reffer`, `duration`, `tvg_name`, `tvg_logo`, `tvg_shift`, `tvg_group`, "
        "`tvg_epg`, `radio`, `recorded`, `consored`, `age_restricred`, `mono`, `name_as_key`, "
        "`audio`) VALUES (%1, '%2', %3, %4, %5, '%6', '%7', '%8', %9, '%10',"
        "'%11', %12, '%13', '%14', %15, %16, %17, %18, %19, %20, %21);";
      queryStr = queryStr.arg(QString::number(playlist.listId), QString::number(channel.id), channel.source, QString::number(channel.position));
      queryStr = queryStr.arg(channel.crop, channel.aspect, channel.vlcInfo.userAgent, channel.vlcInfo.httpReferrer, QString::number(channel.duration));
      queryStr = queryStr.arg(channel.tvgName, channel.tvgLogo, QString::number(channel.tvgShift), channel.groupName, channel.tvgEpg);
      queryStr = queryStr.arg(QString::number(channel.radio), QString::number(channel.recordable), QString::number(channel.censored), QString::number(channel.ageRestrict));
      queryStr = queryStr.arg(QString::number(channel.mono), QString::number(channel.nameAsKey), channel.audioTrack);

      result = query->exec(queryStr);
      if (!result)
        {
          qDebug() << sdb.lastError().text();
        }
    }

  return result;
}


/// Получить канал из базы данных по имени
ChannelInfo DataBase::getChannel(const QString &chName)
{
  ChannelInfo result;
  if(!chName.isEmpty())
    {
      if (!query->exec("SELECT * FROM `channels` WHERE `name`='';"))
        {
          qDebug() << sdb.lastError().text();
        }

      while (query->next())
        {
          result.name = query->value(2).toString();
          result.source = query->value(3).toString();
          result.position = query->value(4).toInt();
          result.crop = query->value(5).toString();
          result.aspect = query->value(6).toString();
          result.vlcInfo.userAgent = query->value(7).toString();
          result.vlcInfo.httpReferrer = query->value(8).toString();
          result.duration = query->value(9).toInt();
          result.tvgName = query->value(10).toString();
          result.tvgLogo = query->value(11).toString();
          result.tvgShift = query->value(12).toInt();
          result.groupName = query->value(13).toString();
          result.tvgEpg = query->value(14).toString();
          result.radio = query->value(15).toBool();
          result.recordable = query->value(16).toBool();
          result.censored = query->value(17).toBool();
          result.ageRestrict = query->value(18).toBool();
          result.mono = query->value(19).toBool();
          result.nameAsKey = query->value(20).toBool();
          result.audioTrack = query->value(21).toString();
        }
    }

  return result;
}


/// Добавить список воспроизведения в базу данных
bool DataBase::addPlaylist(const PlayListInfo &pl)
{
  bool result = false;
  if(!pl.listName.isEmpty())
    {
      QString str = "INSERT INTO `playlists` (`name`, `url_tvg`, `cache`, `crop`, "
        "`aspect`, `autoload`, `deinterlace`, `refresh`, `shift`) "
        "VALUES (%1, '%2', %3, %4, %5, '%6', '%7', '%8', %9);";

      str = str.arg(pl.listName, pl.urlTvg, QString::number(pl.cache), pl.crop, pl.aspect, QString::number(pl.autoload));
      str = str.arg(QString::number(pl.deinterlace), QString::number(pl.refresh), QString::number(pl.tvgShift));

      result = query->exec(str);
      if (!result)
        {
          qDebug() << sdb.lastError().text();
        }
    }

  return result;
}

