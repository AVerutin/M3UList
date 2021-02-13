#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <QDate>
#include <QTime>
#include <QDebug>

class Logger
{
public:
  Logger();
  Logger(const QString &);
  void info(const QString &, const QString &);
  void warn(const QString &, const QString &);
  void error(const QString &, const QString &);

private:
  QString logFileName;
  QFile *logFile;
};

#endif // LOGGER_H
