#ifndef DATATYPES_H
#define DATATYPES_H

#include <QString>

/////// Описание параметров тега #EXTVLCOPT
struct VlcInfo
{
public:
  QString userAgent;    // http-user-agent —— юзер-агент
  QString httpReferrer; // http-referrer —— поставщик услуг

  VlcInfo()
  {
    userAgent = "";
    httpReferrer = "";
  }
};


/////// Описание параметров тега #EXTGRP
struct GroupInfo
{
public:
  QString groupName;  // #EXTGRP: —— наименование группы каналов

  GroupInfo()
  {
    groupName = "";
  }
};


/////// Описание параметров тега #EXTM3U
struct PlayListInfo
{
public:
  QString listName; // дополнительный тег #PLAYLIST позволяющий присвоить имя всему списку
  QString urlTvg;   //  url-xml либо url-tvg —— ссылка на ТВ-программу передач
  int tvgShift;     //  tvg-shift —— значение (в часах) изменение времени в файле EPG. Применяется для всех каналов
  int cache;        //  cache —— время кеширования
  int deinterlace;  //  deinterlace —— деинтерлейс (0, 1 — Blend, 2 — Mean)
  QString aspect;   //  aspect-ratio —— соотношение сторон (none, 4:3, 16:9)
  QString crop;     //  crop —— обрезка W*H+X+Y (690*550+15+10)
  int refresh;      //  refresh —— период обновления
  bool autoload;    //  m3uautoload=1 —— включение автозагрузки файла телепрограммы.

  PlayListInfo()
  {
    listName = "NoName";
    urlTvg = "";
    tvgShift = 0;
    cache = 500;
    deinterlace = 0;
    aspect = "";
    crop = "";
    refresh = 0;
    autoload = false;
  }
};


/////// Описание параметров тега #EXTINF
struct ChannelInfo
{
public:
  int duration;     // :0 —— продолжительность (для ТВ — 0 или –1)
  int id;           // id —— уникальный идентификатор канала
  QString tvgId;    // tvg-id —— значение ChannelID в xml-файле EPG. Если этого тега нет, то производится поиск по тегу tvg-name.
  QString tvgName;  // tvg-name —— значение display-name в файле EPG (отображаемое имя канала)
  QString tvgLogo;  // tvg-logo —— имя файла логотипа без расширения (в формате .png)
  int tvgShift;     // tvg-shift —— значение (в часах) изменение времени в файле EPG. Применятся для одного канала
  QString groupName;// group-name —— имя группы канала. Применяется для создания групп каналов
  bool radio;       // radio —— канал без видео (радио)
  QString audioTrack;// audio-track —— определяет аудио-дорожку (eng, rus)
  QString aspect;   // aspect-ratio —— соотношение сторон (16:9, 4:3, 3:2, 1:1)
  bool recordable;  // recordable=false/true —— Наличие архива записей телепередач для данного канала
  bool censored;    // censored —— родительский контроль (0 или 1)
  bool ageRestrict; // agerestriction=0/1 —— Возрастное ограничение для канала
  QString urlM3u;   // url-m3u —— новый адрес списка каналов (использовать для массового изменения адреса в плеерах у абонентов).
  bool nameAsKey;   // nameaskey —— (0/1) использовать название канала в качестве ключевого поля для сохранения настроек, а не его адрес (использовать в динамически генерируемых списках).
  QString crop;     // crop —— обрезка кадра WxH+X+Y (например, 690x550+15+10).
  bool mono;        // mono —— (0/1) моно-звук.

  VlcInfo vlcInfo;

  ChannelInfo()
  {
    duration = 0;
    id = 0;
    tvgId = "";
    tvgName = "";
    tvgLogo = "";
    tvgShift = 0;
    groupName = "";
    radio = false;
    audioTrack = "";
    aspect = "";
    censored = false;
    ageRestrict = false;
    urlM3u = "";
    nameAsKey = false;
    crop = "";
    mono = false;
    recordable = false;
  }
};


#endif // DATATYPES_H
