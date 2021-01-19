#include "channeleditor.h"

ChannelEditor::ChannelEditor(QWidget *parent) : QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
  createCentralWidget();
}


/// Добавить новый канал
Channel ChannelEditor::addChannel()
{
  channel = new Channel;

  return *channel;
}


/// Редактировать канал
Channel ChannelEditor::editChannel(Channel ch)
{
  channel = new Channel;

  return *channel;
}


/// Сохранить изменения
void ChannelEditor::saveChannel()
{

}


/// Отменить изменения
void ChannelEditor::cancelEdit()
{

}


/// Компоновка формы
void ChannelEditor::createCentralWidget()
{

}
