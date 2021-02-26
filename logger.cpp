#include "logger.h"

/// Конструктор по умолчанию
Logger::Logger()
{
  // Проверяем наличие папки для сохранения логов
  QString path = QDir::currentPath() + "\\logs";
  QDir dir(path);
  if (!dir.exists()) {
      dir.mkpath(path);
  }
  // Имя файла не указано, создаем файл по текущей дате
  QDate today = QDate::currentDate();
  logFileName = path + "\\" + today.toString("dd-MM-yyyy") + ".log";
  logFile = new QFile(logFileName);
  if(!logFile->exists())
    {
      if(!logFile->open(QIODevice::WriteOnly | QIODevice::Text))
        {
          qDebug() <<"Не удалось создать файл логов " + logFileName;
        }

      logFile->close();
    }

}


/// Конструктор с именем файла
Logger::Logger(const QString &logName)
{
  if(!logName.isEmpty())
    {
      logFileName = QDir::currentPath() + "\\" + logName;
      logFile = new QFile(logFileName);
      if(!logFile->exists())
        {
          if (!logFile->open(QIODevice::WriteOnly | QIODevice::Text))
          {
              qDebug() << "Ошибка при создании файла логов " << logFileName;
          }
        }

      if(logFile->exists() && logFile->open(QIODevice::Append | QIODevice::Text))
        {
          QString unitName = typeid(this).name();
          qDebug() <<unitName <<"\n";
          QTextStream out(logFile);
          out << unitName;
        }

      logFile->close();
    }
}


/// Запись информационной строки в лог
void Logger::info(const QString &info, const QString &sender)
{
  if(!info.isEmpty())
    {
      if(logFile->exists() && logFile->open(QIODevice::Append | QIODevice::Text))
        {
          QTextStream out(logFile);
          QDate today = QDate::currentDate();
          QTime time = QTime::currentTime();
          QString now = today.toString("dd-MM-yyyy") + " " + time.toString("HH:mm:ss.zzz");
          out <<"[" <<now <<"]" <<"{ INF " <<sender <<" }: " << info <<"\n";
        }

      logFile->close();
    }
}


/// Запись предупреждающей строки в лог
void Logger::warn(const QString &warn, const QString &sender)
{
  if(!warn.isEmpty())
    {
      if(logFile->exists() && logFile->open(QIODevice::Append | QIODevice::Text))
        {
          QTextStream out(logFile);
          QDate today = QDate::currentDate();
          QTime time = QTime::currentTime();
          QString now = today.toString("dd-MM-yyyy") + " " + time.toString("HH:mm:ss.zzz");
          out <<"[" <<now <<"]" <<"{ WRN " <<sender <<" }: " << warn <<"\n";
        }

      logFile->close();
    }
}


/// Запись строки с ошибкой в лог
void Logger::error(const QString &error, const QString &sender)
{
  if(!error.isEmpty())
    {
      if(logFile->exists() && logFile->open(QIODevice::Append | QIODevice::Text))
        {
          QTextStream out(logFile);
          QDate today = QDate::currentDate();
          QTime time = QTime::currentTime();
          QString now = today.toString("dd-MM-yyyy") + " " + time.toString("HH:mm:ss.zzz");
          out <<"[" <<now <<"]" <<"{ ERR " <<sender <<" }: " << error <<"\n";
        }

      logFile->close();
    }
}

