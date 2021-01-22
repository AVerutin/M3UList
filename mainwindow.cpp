#include "mainwindow.h"

/// Конструктор класса по-умолчанию
MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  modified = false;
  listFileName = "";
  playList = new PlayList;
  channel = new Channel;

  createMenu();
  createWidget();
  fillChannelsList();
}


/// Деструктор класса по-умолчанию
MainWindow::~MainWindow()
{
}


/// Установка статуса документа:
/// true  - документ был изменен
/// false - документ не был изменен
void MainWindow::setModified(bool mod)
{
  QString title;
  if(playList->listName.isEmpty())
    {
      // Имя файла не установлено
      title = tr("Новый список воспроизведения");
    }
  else
    {
      title = playList->listName;
    }

  if(mod)
    {
      setWindowTitle("* " + title);
    }
  else
    {
      setWindowTitle(title);
    }

  modified = mod;
}


/// Наполнение таблицы списком каналов
void MainWindow::fillChannelsList()
{
  model->clear();
  for(int i=0; i<playList->getChannelsCount(); i++)
    {
      QList<QStandardItem *> items;
      Channel ch = playList->getChannelAt(i);
      items.append(new QStandardItem(QString::number(ch.tvgId)));
      items.append(new QStandardItem(ch.tvgName));
      items.append(new QStandardItem(ch.groupName));
      items.append(new QStandardItem(ch.url));

      model->appendRow(items);
    }

  model->setHorizontalHeaderLabels(QStringList() <<"№" << "Имя" << "Группа" << "Источник");
  // twChannels->resizeColumnToContents(0);
  // twChannels->resizeColumnToContents(1);
  // twChannels->resizeColumnToContents(2);
  twChannels->setColumnWidth(0, 25);
  twChannels->setColumnWidth(1, 100);
  twChannels->setColumnWidth(2, 120);
  twChannels->setColumnWidth(3, 250);
}


/// Парсинг списка воспроизведения
void MainWindow::parsePlayList(const QString fileName)
{
  parser = new Parser(fileName);
  *playList = parser->parse();
}


/// Создание главного меню приложения
void MainWindow::createMenu()
{
  // Пункт меню Создать
  aListCreate = new QAction(this);
  aListCreate->setText(tr("Создать"));
  aListCreate->setToolTip(tr("Создать новый список воспроизведения"));
  aListCreate->setStatusTip(tr("Создать новый список воспроизведения"));
  // QKeySequence keyListCreate = QKeySequence("CTRL+N");
  aListCreate->setShortcut(QKeySequence("CTRL+N"));
  connect(aListCreate, &QAction::triggered, this, &MainWindow::slotListCreate);

  // Пункт меню Открыть
  aListOpen = new QAction(this);
  aListOpen->setText(tr("Открыть"));
  aListOpen->setToolTip(tr("Открыть список воспроизведения"));
  aListOpen->setStatusTip(tr("Открыть список воспроизведения"));
  // QKeySequence keyListOpen = QKeySequence("CTRL+O");
  aListOpen->setShortcut(QKeySequence("CTRL+O"));
  connect(aListOpen, &QAction::triggered, this, &MainWindow::slotListOpen);

  // Пункт меню Сохранить
  aListSave = new QAction(this);
  aListSave->setText(tr("Сохранить"));
  aListSave->setToolTip(tr("Сохранить текущий список"));
  aListSave->setStatusTip(tr("Сохранить текущий список"));
  // QKeySequence keyListSave = QKeySequence("CTRL+S");
  aListSave->setShortcut(QKeySequence("CTRL+S"));
  connect(aListSave, &QAction::triggered, this, &MainWindow::slotListSave);

  // Пункт меню Сохранить как...
  aListSaveAs = new QAction(this);
  aListSaveAs->setText(tr("Сохранить как..."));
  aListSaveAs->setToolTip(tr("Сохранить текущий список под другим именем"));
  aListSaveAs->setStatusTip(tr("Сохранить текущий список под другим именем"));
  // QKeySequence keyListSaveAs = QKeySequence("CTRL+SHIFT+S");
  aListSaveAs->setShortcut(QKeySequence("CTRL+SHIFT+S"));
  connect(aListSaveAs, &QAction::triggered, this, &MainWindow::slotListSaveAs);

  // Пункт меню Выход
  aAppClose = new QAction(this);
  aAppClose->setText(tr("Выход"));
  aAppClose->setToolTip(tr("Выход из приложения"));
  aAppClose->setStatusTip(tr("Выход из приложения"));
  // QKeySequence keyAppClose = QKeySequence("ALT+X");
  aAppClose->setShortcut(QKeySequence("ALT+X"));
  connect(aAppClose, &QAction::triggered, this, &MainWindow::slotAppClose);


  mnPlayList = new QMenu(this);
  mnPlayList->setTitle(tr("Список"));
  mnPlayList->setStatusTip(tr("Управление списком воспроизведения"));
  mnPlayList->addAction(aListCreate);
  mnPlayList->addAction(aListOpen);
  mnPlayList->addAction(aListSave);
  mnPlayList->addAction(aListSaveAs);
  mnPlayList->addSeparator();
  mnPlayList->addAction(aAppClose);

  mnMainMenu = menuBar();
  mnMainMenu->addMenu(mnPlayList);
}


/// Добавить новый канал
void MainWindow::slotChannelAdd()
{
  //  QMessageBox::information(this, QString(tr("Внимание")),
  //                              QString(tr("Добавить новый канал")),
  //                              QMessageBox::Ok);

  // Вызов окна для добавления канала
  formChannelEditor = new ChannelEditor(this);
  if(formChannelEditor->exec() == QDialog::Accepted)
    {
      *channel = formChannelEditor->getChannel();
      playList->addChannel(*channel);
      setModified(true);
    }

  delete formChannelEditor;
  formChannelEditor = nullptr;
  fillChannelsList();
}


/// Редактировать выбранный канал
void MainWindow::slotChannelEdit()
{
  QMessageBox::information(this, QString(tr("Внимание")),
                              QString(tr("Править выбранный канал")),
                              QMessageBox::Ok);


}


/// Удалить выбранный канал
void MainWindow::slotChannelDelete()
{
  QMessageBox::information(this, QString(tr("Внимание")),
                              QString(tr("Удалить выбранный канал")),
                              QMessageBox::Ok);


}


/// Переместить выбранный канал вверх
void MainWindow::slotChannelUp()
{
  QMessageBox::information(this, QString(tr("Внимание")),
                              QString(tr("Переместить выбранный канал вверх")),
                              QMessageBox::Ok);
}


/// Переместить выбранный канал вниз
void MainWindow::slotChannelDown()
{
  QMessageBox::information(this, QString(tr("Внимание")),
                              QString(tr("Переместить выбранный канал вниз")),
                           QMessageBox::Ok);
}


/// Обработка сигнала изменения текста в поле ввода имени списка
void MainWindow::slotPlaylistName_textChanged(const QString &name)
{
  if(!name.isEmpty() && name != "")
    {
      playList->listName = name;
    }
  else
    {
      playList->listName.clear();
    }

  setModified(true);
}


/// Обработка сигнала изменения состояния переключателя автозагрузки списка
void MainWindow::slotPlaylistAutoload_changeState(int state)
{
  playList->autoload = bool(state);
  setModified(true);
}


/// Обработка сигнала изменения текста в поле телегида
void MainWindow::slotPlaylistEpg_textChanged(const QString &epg)
{
  if(!epg.isEmpty())
    {
      playList->urlTvg = epg;
      setModified(true);
    }
}


/// Обработка сигнала изменения текста в поле смещения
void MainWindow::slotPlaylistShift_textChanged(const QString &shift)
{
  if(!shift.isEmpty())
    {
      int iShift = shift.toInt();
      if(iShift>0)
        {
          playList->tvgShift = iShift;
          setModified(true);
        }
    }
}


/// Обработка сигнала изменения текста в поле юзер-агента
void MainWindow::slotPlaylistUserAgent_textChanged(const QString &agent)
{
  if(!agent.isEmpty())
    {
      playList->userAgent = agent;
      setModified(true);
    }
}


/// Обработка сигнала изменения текста в поле кеш
void MainWindow::slotPlaylistCache_textChanged(const QString &cache)
{
  if(!cache.isEmpty())
    {
      playList->cache = cache.toInt();
      setModified(true);
    }
}


/// Обработка сигнала изменения текста в поле Обрезка по ширине
void MainWindow::slotPlaylistCropWidth_textChanged(const QString &width)
{
  if(!width.isEmpty())
    {
      playList->setCropWidth(width.toInt());
      setModified(true);
    }
}


/// Обработка сигнала изменения текста в поле Обрезка по высоте
void MainWindow::slotPlaylistCropHeight_textChanged(const QString &height)
{
  if(!height.isEmpty())
    {
      playList->setCropHeight(height.toInt());
      setModified(true);
    }
}


/// Обработка сигнала изменения текста в поле Обрезка сверху
void MainWindow::slotPlaylistCropTop_textChanged(const QString &top)
{
  if(!top.isEmpty())
    {
      playList->setCropTop(top.toInt());
      setModified(true);
    }
}


/// Обработка сигнала изменения текста в поле Обрезка слева
void MainWindow::slotPlaylistCropLeft_textChanged(const QString &left)
{
  if(!left.isEmpty())
    {
      playList->setCropLeft(left.toInt());
      setModified(true);
    }
}


/// Обработка сигнала изменения текста в поле Соотношение сторон - Ширина
void MainWindow::slotAspectWidth_textChanged(const QString &width)
{
  if(!width.isEmpty())
    {
      playList->setAspectRatioWidth(width.toInt());
      setModified(true);
    }
}


/// Обработка сигнала изменения текста в поле Соотношение сторон - Высота
void MainWindow::slotAspectHeight_textChanged(const QString &height)
{
  if(!height.isEmpty())
    {
      playList->setAspectRatioHeight(height.toInt());
      setModified(true);
    }
}


/// Создание главного окна приложения
void MainWindow::createWidget()
{
  // Создание элементов главной формы

  // Элементы 1 линии
  lblListName = new QLabel(tr("Имя списка"));
  leListName = new QLineEdit;
  connect(leListName, &QLineEdit::textChanged, this, &MainWindow::slotPlaylistName_textChanged);
  lblListName->setBuddy(leListName);
  cbAutoload = new QCheckBox(tr("Автозагрузка"));
  cbAutoload->setChecked(false);
  connect(cbAutoload, &QCheckBox::stateChanged, this, &MainWindow::slotPlaylistAutoload_changeState);
  line1 = new QHBoxLayout;
  line1->addWidget(lblListName);
  line1->addWidget(leListName);
  line1->addWidget(cbAutoload);

  // Элементы 2 линии
  lblEpg = new QLabel(tr("Телегид"));
  leEpg = new QLineEdit;
  connect(leEpg, &QLineEdit::textChanged, this, &MainWindow::slotPlaylistEpg_textChanged);
  lblEpg->setBuddy(leEpg);
  line2 = new QHBoxLayout;
  line2->addWidget(lblEpg);
  line2->addWidget(leEpg);

  // Элементы 3 линии
  lblAgent = new QLabel(tr("Агент"));
  leAgent = new QLineEdit;
  connect(leAgent, &QLineEdit::textChanged, this, &MainWindow::slotPlaylistUserAgent_textChanged);
  lblAgent->setBuddy(leAgent);
  spacer1 = new QSpacerItem(20, 20, QSizePolicy::Expanding);
  lblShift = new QLabel(tr("Смещение"));
  leShift = new QLineEdit;
  connect(leShift, &QLineEdit::textChanged, this, &MainWindow::slotPlaylistShift_textChanged);
  lblShift->setBuddy(leShift);
  spacer2 = new QSpacerItem(20, 20, QSizePolicy::Expanding);
  lblCache = new QLabel(tr("Кэш"));
  leCache = new QLineEdit;
  connect(leCache, &QLineEdit::textChanged, this, &MainWindow::slotPlaylistCache_textChanged);
  lblCache->setBuddy(leCache);
  line3 = new QHBoxLayout;
  line3->addWidget(lblAgent);
  line3->addWidget(leAgent);
  line3->addSpacerItem(spacer1);
  line3->addWidget(lblShift);
  line3->addWidget(leShift);
  line3->addSpacerItem(spacer2);
  line3->addWidget(lblCache);
  line3->addWidget(leCache);

  // Элементы 4 линии
  // левая группа
  lblCropWidth = new QLabel(tr("Ширина"));
  leCropWidth = new QLineEdit;
  connect(leCropWidth, &QLineEdit::textChanged, this, &MainWindow::slotPlaylistCropWidth_textChanged);
  lblCropWidth->setBuddy(leCropWidth);
  lblCropHeight = new QLabel(tr("Высота"));
  leCropHeight = new QLineEdit;
  connect(leCropHeight, &QLineEdit::textChanged, this, &MainWindow::slotPlaylistCropHeight_textChanged);
  lblCropHeight->setBuddy(leCropHeight);
  lp1Line1 = new QHBoxLayout;
  lp1Line1->addWidget(lblCropWidth);
  lp1Line1->addWidget(leCropWidth);
  lp1Line1->addWidget(lblCropHeight);
  lp1Line1->addWidget(leCropHeight);

  lblCropTop = new QLabel(tr("Сверху"));
  leCropTop = new QLineEdit;
  connect(leCropTop, &QLineEdit::textChanged, this, &MainWindow::slotPlaylistCropTop_textChanged);
  lblCropTop->setBuddy(leCropTop);
  lblCropLeft = new QLabel(tr("Слева"));
  leCropLeft = new QLineEdit;
  connect(leCropLeft, &QLineEdit::textChanged, this, &MainWindow::slotPlaylistCropLeft_textChanged);
  lblCropLeft->setBuddy(leCropLeft);
  lp1Line2 = new QHBoxLayout;
  lp1Line2->addWidget(lblCropTop);
  lp1Line2->addWidget(leCropTop);
  lp1Line2->addWidget(lblCropLeft);
  lp1Line2->addWidget(leCropLeft);

  lPage1 = new QVBoxLayout;
  lPage1->addLayout(lp1Line1);
  lPage1->addLayout(lp1Line2);
  gbPage1 = new QGroupBox(tr("Обрезка"));
  gbPage1->setLayout(lPage1);

  // правая группа
  lblAspectWidth = new QLabel(tr("Ширина"));
  leAspectWidth = new QLineEdit;
  connect(leAspectWidth, &QLineEdit::textChanged, this, &MainWindow::slotAspectWidth_textChanged);
  lblAspectWidth->setBuddy(leAspectWidth);
  lblAspectHeight = new QLabel(tr("Высота"));
  leAspectHeight = new QLineEdit;
  connect(leAspectHeight, &QLineEdit::textChanged, this, &MainWindow::slotAspectHeight_textChanged);
  lblAspectHeight->setBuddy(leAspectHeight);
  lp2Line1 = new QHBoxLayout;
  lp2Line1->addWidget(lblAspectWidth);
  lp2Line1->addWidget(leAspectWidth);
  lp2Line1->addWidget(lblAspectHeight);
  lp2Line1->addWidget(leAspectHeight);

  lPage2 = new QVBoxLayout;
  lPage2->addLayout(lp2Line1);
  gbPage2 = new QGroupBox(tr("Соотношение сторон"));
  gbPage2->setLayout(lPage2);

  // установка групп
  line4 = new QHBoxLayout;
  line4->addWidget(gbPage1);
  line4->addWidget(gbPage2);

  // Элементы 5 линии
  twChannels = new QTableView;
  twChannels->setSelectionBehavior(QAbstractItemView::SelectRows);
  twChannels->setEditTriggers(QAbstractItemView::NoEditTriggers);
  model = new QStandardItemModel(this);
  twChannels->setModel(model);

  line5 = new QHBoxLayout;
  btnChannelUp = new QPushButton(tr("Вверх"));
  btnChannelUp->setFixedWidth(70);
  connect(btnChannelUp, &QPushButton::clicked, this, &MainWindow::slotChannelUp);
  btnChannelDown = new QPushButton(tr("Вниз"));
  btnChannelDown->setFixedWidth(70);
  connect(btnChannelDown, &QPushButton::clicked, this, &MainWindow::slotChannelDown);
  spacer5 = new QSpacerItem(0, 40, QSizePolicy::Ignored, QSizePolicy::Expanding);
  lp5Buttons = new QVBoxLayout;
  lp5Buttons->addWidget(btnChannelUp, 1);
  lp5Buttons->addWidget(btnChannelDown, 1);
  lp5Buttons->addSpacerItem(spacer5);

  line5->addWidget(twChannels, 0);
  line5->addLayout(lp5Buttons, 1);

  // Элементы 6 линии
  spacer3 = new QSpacerItem(20, 20, QSizePolicy::Expanding);
  btnAdd = new QPushButton(tr("Добавить"));
  connect(btnAdd, &QPushButton::clicked, this, &MainWindow::slotChannelAdd);
  btnEdit = new QPushButton(tr("Правка"));
  connect(btnEdit, &QPushButton::clicked, this, &MainWindow::slotChannelEdit);
  btnDelete = new QPushButton(tr("Удалить"));
  connect(btnDelete, &QPushButton::clicked, this, &MainWindow::slotChannelDelete);
  spacer4 = new QSpacerItem(20, 20, QSizePolicy::Expanding);
  line6 = new QHBoxLayout;
  line6->addSpacerItem(spacer3);
  line6->addWidget(btnAdd);
  line6->addWidget(btnEdit);
  line6->addWidget(btnDelete);
  line6->addSpacerItem(spacer4);

  // Добавление элементов на главную форму
  mainLayout = new QVBoxLayout;
  mainLayout->addLayout(line1);
  mainLayout->addLayout(line2);
  mainLayout->addLayout(line3);
  mainLayout->addLayout(line4);
  mainLayout->addLayout(line5);
  mainLayout->addLayout(line6);

  // Установка элементов на главную форму
  mainWidget = new QWidget;
  mainWidget->setLayout(mainLayout);
  setCentralWidget(mainWidget);

  // Создание строки состояния
  stBar = statusBar();
  stBar->setSizeGripEnabled(false);
  stBar->showMessage(tr("Готово."));

  // Установка параметров главной формы
  setWindowTitle(tr("Новый список воспроизведения"));
  setFixedSize(650, 450);
  setWindowIcon(QIcon(":/appIcon/icons/appIcon.ico"));
}


/// Обработка выбора пункта меню Список - Создать
void MainWindow::slotListCreate()
{
  if(modified)
    {
      // Предупреждение о наличии несохраненных изменений
      QMessageBox::StandardButton res;
      res = QMessageBox::warning(this, QString(tr("Внимание")),
                            QString(tr("Все изменения в текущем списке будут утеряны!\nПродолжить в любом случае?")),
                            QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

      if(res == QMessageBox::No)
        return;
    }

  listFileName = "";
  playList = new PlayList;
  stBar->showMessage(tr("Создан новый список воспроизведения"));
  setModified(false);
}


/// Обработка выбора пункта меню Список - Открыть
void MainWindow::slotListOpen()
{
  // Проверим, изменен ли документ
  if(modified)
    {
      QMessageBox::StandardButton res;
      res = QMessageBox::warning(this, QString(tr("Внимание")),
                            QString(tr("Все изменения в текущем списке будут утеряны!\nПродолжить в любом случае?")),
                            QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

      if(res == QMessageBox::No)
        return;
    }

  listFileName = QFileDialog::getOpenFileName(this,
                              QString(tr("Открыть список воспроизведения")),
                              QDir::currentPath(),
                              tr("Списки воспроизведения (*.m3u *.m3u8);;Все файла (*.*)"));

  // Пользователь отменил открытие файла
  if(listFileName.isEmpty())
    return;

  parsePlayList(listFileName);

  QString msg = tr("Открыт файл [%1]");
  msg = msg.arg(listFileName);

  stBar->showMessage(msg);
  setWindowTitle(tr("Список: ") + listFileName);
  setModified(false);
}


/// Обработка выбора пункта меню Список - Сохранить
void MainWindow::slotListSave(bool permanent)
{
  if(modified || permanent || listFileName.isEmpty())
    {
      // Сохраняем текущий плейлист под тем же именем
      if(listFileName.isEmpty())
        {
          listFileName = QFileDialog::getSaveFileName(this,
                                      QString(tr("Сохранить список воспроизведения")),
                                      QDir::currentPath(),
                                      tr("Списки воспроизведения (*.m3u *.m3u8);;Все файла (*.*)"));

          // Пользователь отменил сохранение файла
          if(listFileName.isEmpty())
            return;

          listFile = new QFile(listFileName);
          if(listFile->open(QIODevice::WriteOnly | QIODevice::Text))
            {
              QTextStream writeStream(listFile);

              // Записывем заголовок списка
              writeStream << "#EXTM3U";
              writeStream << (playList->urlTvg.isEmpty() ? "" : " url-tvg=\"" + playList->urlTvg + "\"");
              writeStream << (playList->tvgShift!=0 ? " tvg-shift=\"" + QString::number(playList->tvgShift) + "\"" : "");
              writeStream << (playList->cache==0 ? "" : " cache=\"" + QString::number(playList->cache) + "\"");
              writeStream << (playList->deinterlace==0 ? "" : " deinterlace=\"" + QString::number(playList->deinterlace) + "\"");
              writeStream << (playList->getAspectRatio().isEmpty() ? "" : " aspect-ratio=\"" + playList->getAspectRatio() + "\"");
              writeStream << (playList->getCrop().isEmpty() ? "" : " crop=\"" + playList->getCrop() + "\"");
              writeStream << (playList->refreshPeriod==0 ? "" : " refresh=\"" + QString::number(playList->refreshPeriod) + "\"");
              writeStream << (!playList->autoload ? "" : " m3uautoload=\"1\"");
              writeStream << "\n";

              // Записываем юзер-агента
              writeStream << (!playList->userAgent.isEmpty() ? "#EXTVLCOPT:http-user-agent=\"" + playList->userAgent + "\"\n" : "");

              // Записываем название списка
              writeStream << (!playList->listName.isEmpty() ? "#PLAYLIST:" + playList->listName + "\n" : "");

              // Записываем имеющиеся каналы
              for(int i=0; i<playList->getChannelsCount(); i++)
                {
                  writeStream << "";
                }

              listFile->close();
            }
        }

      stBar->showMessage(tr("Список воспроизведения сохранен в файл: ") + listFileName);
      setModified(false);
    }
}


/// Обработка выбора пункта меню Список - Сохранить как
void MainWindow::slotListSaveAs()
{
  // Запрашиваем имя нового файла и сохраянем текущй плейлист под этим именем
  // Изменяем имя файла текущего листа на новый
  listFileName = QFileDialog::getSaveFileName(this,
                              QString(tr("Сохранить список воспроизведения")),
                              QDir::currentPath(),
                              tr("Списки воспроизведения (*.m3u *.m3u8);;Все файлы (*.*)"));

  // Пользователь отменил сохранение файла
  if(listFileName.isEmpty())
    return;

  slotListSave(true);

  setModified(false);
}


/// Обработка выбора пункта меню Список - Выход
void MainWindow::slotAppClose()
{
  close();
}


/// Обработка события выхода из приложения
void MainWindow::closeEvent(QCloseEvent *event)
 {
  if(modified)
    {
      QMessageBox::StandardButton res =
          QMessageBox::warning(this,
                               tr("Внимание!"),
                               tr("Имеются <u>несохраненные изменения!</u>\nВыйти в любом случае?"),
                               QMessageBox::Yes | QMessageBox::No,
                               QMessageBox::No);
      if(res == QMessageBox::Yes)
        {
          event->accept();
        }
      else
        {
          event->ignore();
        }
    }
  else
    {
      event->accept();
    }

 }

