#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QMenuBar>
#include <QMenu>
#include <QStatusBar>
#include <QAction>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFile>
#include <QFileDialog>
#include <QPushButton>

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
  QVBoxLayout *mainLayout;
  QPushButton *testButton;

  // Элементы главного меню
  QMenuBar *mnMainMenu;
  QMenu *mnPlayList;
  QAction *aListCreate;
  QAction *aListOpen;
  QAction *aListSave;
  QAction *aListSaveAs;
  QAction *aAppClose;

  // Строка состояния
  QStatusBar *stBar;

  // Свойства класса
  bool modified;
  QString listFileName;
  QFile *listFile;
  PlayList *playList;

  // Методы класса
  void createMenu();
  void createWidget();
  void setModified(bool);
  void parsePlayList(const QStringList);

private slots:
  void slotListCreate();
  void slotListOpen();
  void slotListSave();
  void slotListSaveAs();
  void slotAppClose();
  void setMod(); // временный слот
};
#endif // MAINWINDOW_H
