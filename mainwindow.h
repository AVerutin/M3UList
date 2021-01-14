#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>

#include "playlist.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  // Центральный виджет приложения
  QWidget *mainWidget;
  QVBoxLayout *vblMainLayout;

  // Элементы главного меню
  QMenuBar *mnMainMenu;
  QMenu *mnPlayList;
  QAction *aListCreate;
  QAction *aListOpen;
  QAction *aListSave;
  QAction *aListSaveAs;
  QAction *aAppClose;

  // Свойства класса
  bool modified;
  QString listFileName;
  QFile *listFile;

  // Методы класса
  void createMenu();
  void createWidget();

private slots:
  void slotListCreate();
  void slotListOpen();
  void slotListSave();
  void slotListSaveAs();
  void slotAppClose();
};
#endif // MAINWINDOW_H
