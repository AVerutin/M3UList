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
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QCheckBox>
#include <QComboBox>
#include <QGroupBox>
#include <QSpacerItem>
#include <QFile>
#include <QFileDialog>
#include <QPushButton>
#include <QDialog>

#include "playlist.h"
#include "playlistparser.h"
#include "channeleditor.h"
#include "channel.h"
#include "groupseditor.h"
#include "soundtracks.h"

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  // Вспомогательные формы приложения
  ChannelEditor *formChannelEditor;

  // Центральный виджет приложения
  QWidget *mainWidget;
  QVBoxLayout *mainLayout;

  // 1 линия
  QHBoxLayout *line1;
  QLabel *lblListName;
  QLineEdit *leListName;
  QCheckBox *cbAutoload;

  // 2 линия
  QHBoxLayout *line2;
  QLabel *lblEpg;
  QLineEdit *leEpg;

  // 3 линия
  QHBoxLayout *line3;
  QLabel *lblAgent;
  QLineEdit *leAgent;
  QLabel *lblShift;
  QLineEdit *leShift;
  QLabel *lblCache;
  QLineEdit *leCache;
  QSpacerItem *spacer1;
  QSpacerItem *spacer2;

  // 4 линия
  QHBoxLayout *line4;
  QGroupBox *gbPage1;
  QVBoxLayout *lPage1;
  QHBoxLayout *lp1Line1;
  QLabel *lblCropWidth;
  QLineEdit *leCropWidth;
  QLabel *lblCropHeight;
  QLineEdit *leCropHeight;
  QHBoxLayout *lp1Line2;
  QLabel *lblCropTop;
  QLineEdit *leCropTop;
  QLabel *lblCropLeft;
  QLineEdit *leCropLeft;

  QGroupBox *gbPage2;
  QVBoxLayout *lPage2;
  QHBoxLayout *lp2Line1;
  QLabel *lblAspectWidth;
  QLineEdit *leAspectWidth;
  QLabel *lblAspectHeight;
  QLineEdit *leAspectHeight;

  // 5 линия
  QHBoxLayout *line5;
  QVBoxLayout *lp5Buttons;
  QTableView *twChannels;
  QStandardItemModel *model;
  QPushButton *btnChannelUp;
  QPushButton *btnChannelDown;
  QSpacerItem *spacer5;

  // 6 линия
  QHBoxLayout *line6;
  QSpacerItem *spacer3;
  QPushButton *btnAdd;
  QPushButton *btnEdit;
  QPushButton *btnDelete;
  QSpacerItem *spacer4;

  // Элементы главного меню
  QMenuBar *mnMainMenu;
  QMenu *mnPlayList;
  QAction *aListCreate;
  QAction *aListOpen;
  QAction *aListSave;
  QAction *aListSaveAs;
  QAction *aAppClose;
  QAction *aChannelAdd;
  QAction *aChannelEdit;
  QAction *aChannelDelete;

  // Строка состояния
  QStatusBar *stBar;

  // Свойства класса
  bool modified;
  QString listFileName;
  QFile *listFile;
  PlayList *playList;
  Channel *channel;
  Parser *parser;

  // Методы класса
  void createMenu();
  void createWidget();
  void setModified(bool);
  void parsePlayList(const QString);
  void fillChannelsList();

protected:
  void closeEvent (QCloseEvent *);

private slots:
  void slotListCreate();    // Создать новый список
  void slotListOpen();      // Открыть список из файла
  void slotListSave(bool);  // Сохранить список
  void slotListSaveAs();    // Сохранить список под другим именем
  void slotAppClose();      // Выйти из приложения
  void slotChannelAdd();    // Добавить новый канал
  void slotChannelEdit();   // Изменит выбранный канал
  void slotChannelDelete(); // Удалить выбранный канал
  void slotChannelUp();     // Переместить канал вверх
  void slotChannelDown();   // Переместить канал вниз

  // Слоты изменения значения полей на форме
  void slotPlaylistName_textChanged(const QString &);
  void slotPlaylistAutoload_changeState(int);
  void slotPlaylistEpg_textChanged(const QString &);
  void slotPlaylistShift_textChanged(const QString &);
  void slotPlaylistUserAgent_textChanged(const QString &);
  void slotPlaylistCache_textChanged(const QString &);
  void slotPlaylistCropWidth_textChanged(const QString &);
  void slotPlaylistCropHeight_textChanged(const QString &);
  void slotPlaylistCropTop_textChanged(const QString &);
  void slotPlaylistCropLeft_textChanged(const QString &);
  void slotAspectWidth_textChanged(const QString &);
  void slotAspectHeight_textChanged(const QString &);
};
#endif // MAINWINDOW_H
