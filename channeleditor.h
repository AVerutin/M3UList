/// Форма редактора каналов

#ifndef CHANNELEDITOR_H
#define CHANNELEDITOR_H

#include <QDialog>
#include <QtWidgets>
#include "channel.h"

class ChannelEditor : public QDialog
{
  Q_OBJECT
public:
  explicit ChannelEditor(QWidget *parent = nullptr);
  Channel addChannel();
  Channel editChannel(Channel);

private:
  Channel *channel;

  void createCentralWidget();

private slots:
  void saveChannel();
  void cancelEdit();

};

#endif // CHANNELEDITOR_H
