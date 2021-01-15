#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  modified = false;
  listFileName = "";

  createMenu();
  createWidget();
}

MainWindow::~MainWindow()
{
}


/// Установка статуса документа:
/// true  - документ был изменен
/// false - документ не был изменен
void MainWindow::setModified(bool mod)
{
  QString title;
  if(listFileName.isEmpty())
    {
      // Имя файла не установлено
      title = "Новый список воспроизведения";
    }
  else
    {
      title = listFileName;
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


/// Парсинг списка воспроизведения
void MainWindow::parsePlayList(const QStringList)
{
  playList = new PlayList;

  // Построчный анализ списка и разбор каждой строки
}


/// Создание главного меню приложения
void MainWindow::createMenu()
{
  // Пункт меню Создать
  aListCreate = new QAction(this);
  aListCreate->setText("Создать");
  aListCreate->setToolTip("Создать новый список воспроизведения");
  aListCreate->setStatusTip("Создать новый список воспроизведения");
  // QKeySequence keyListCreate = QKeySequence("CTRL+N");
  aListCreate->setShortcut(QKeySequence("CTRL+N"));
  connect(aListCreate, &QAction::triggered, this, &MainWindow::slotListCreate);

  // Пункт меню Открыть
  aListOpen = new QAction(this);
  aListOpen->setText("Открыть");
  aListOpen->setToolTip("Открыть список воспроизведения");
  aListOpen->setStatusTip("Открыть список воспроизведения");
  // QKeySequence keyListOpen = QKeySequence("CTRL+O");
  aListOpen->setShortcut(QKeySequence("CTRL+O"));
  connect(aListOpen, &QAction::triggered, this, &MainWindow::slotListOpen);

  // Пункт меню Сохранить
  aListSave = new QAction(this);
  aListSave->setText("Сохранить");
  aListSave->setToolTip("Сохранить текущий список");
  aListSave->setStatusTip("Сохранить текущий список");
  // QKeySequence keyListSave = QKeySequence("CTRL+S");
  aListSave->setShortcut(QKeySequence("CTRL+S"));
  connect(aListSave, &QAction::triggered, this, &MainWindow::slotListSave);

  // Пункт меню Сохранить как...
  aListSaveAs = new QAction(this);
  aListSaveAs->setText("Сохранить как...");
  aListSaveAs->setToolTip("Сохранить текущий список под другим именем");
  aListSaveAs->setStatusTip("Сохранить текущий список под другим именем");
  // QKeySequence keyListSaveAs = QKeySequence("CTRL+SHIFT+S");
  aListSaveAs->setShortcut(QKeySequence("CTRL+SHIFT+S"));
  connect(aListSaveAs, &QAction::triggered, this, &MainWindow::slotListSaveAs);

  // Пункт меню Выход
  aAppClose = new QAction(this);
  aAppClose->setText("Выход");
  aAppClose->setToolTip("Выход из приложения");
  aAppClose->setStatusTip("Выход из приложения");
  // QKeySequence keyAppClose = QKeySequence("ALT+X");
  aAppClose->setShortcut(QKeySequence("ALT+X"));
  connect(aAppClose, &QAction::triggered, this, &MainWindow::slotAppClose);


  mnPlayList = new QMenu(this);
  mnPlayList->setTitle("Список");
  mnPlayList->setStatusTip("Управление списком воспроизведения");
  mnPlayList->addAction(aListCreate);
  mnPlayList->addAction(aListOpen);
  mnPlayList->addAction(aListSave);
  mnPlayList->addAction(aListSaveAs);
  mnPlayList->addSeparator();
  mnPlayList->addAction(aAppClose);

  mnMainMenu = menuBar();
  mnMainMenu->addMenu(mnPlayList);
}


///Тестовый слот для установки статуса документа Изменен
void MainWindow::setMod()
{
  setModified(true);
}


/// Создание главного окна приложения
void MainWindow::createWidget()
{
  // Создание элементов главной формы
  testButton = new QPushButton("Пуш ми!");
  connect(testButton, &QPushButton::clicked, this, &MainWindow::setMod);

  // Добавление элементов на главную форму
  mainLayout = new QVBoxLayout;
  mainLayout->addWidget(testButton);

  // Установка элементов на главную форму
  mainWidget = new QWidget;
  mainWidget->setLayout(mainLayout);
  setCentralWidget(mainWidget);

  // Создание строки состояния
  stBar = statusBar();
  stBar->setSizeGripEnabled(false);
  stBar->showMessage("Готово.");

  // Установка параметров главной формы
  setWindowTitle("Новый список воспроизведения");
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
      res = QMessageBox::warning(this, QString::fromUtf8("Внимание"),
                            QString::fromUtf8("Все изменения в текущем списке будут утеряны!\nПродолжить в любом случае?"),
                            QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

      if(res == QMessageBox::No)
        return;
    }

  listFileName = "";
  playList = new PlayList;
  stBar->showMessage("Создан новый список воспроизведения");
  setModified(false);
}


/// Обработка выбора пункта меню Список - Открыть
void MainWindow::slotListOpen()
{
  // Проверим, изменен ли документ
  if(modified)
    {
      QMessageBox::StandardButton res;
      res = QMessageBox::warning(this, QString::fromUtf8("Внимание"),
                            QString::fromUtf8("Все изменения в текущем списке будут утеряны!\nПродолжить в любом случае?"),
                            QMessageBox::Yes | QMessageBox::No, QMessageBox::No);

      if(res == QMessageBox::No)
        return;
    }

  listFileName = QFileDialog::getOpenFileName(this,
                              QString::fromUtf8("Открыть список воспроизведения"),
                              QDir::currentPath(),
                              "Списки воспроизведения (*.m3u *.m3u8);;Все файла (*.*)");

  // Пользователь отменил открытие файла
  if(listFileName.isEmpty())
    return;

  QStringList *playList = new QStringList();
  listFile = new QFile(listFileName);

  if ((listFile->exists())&&(listFile->open(QIODevice::ReadOnly)))
  {
      QString line = "";
          while(!listFile->atEnd())
          {
              line = listFile->readLine();
              playList->append(line);
          }

      listFile->close();

      QString msg = "Открыт файл [%1]: прочитано строк: %2";
      msg = msg.arg(listFileName).arg(playList->count());

      stBar->showMessage(msg);
      setWindowTitle("Список: " + listFileName);
      setModified(false);
    }

  delete playList;
}

// Обработка выбора пункта меню Список - Сохранить
void MainWindow::slotListSave()
{
  if(modified || listFileName.isEmpty())
    {
      // Сохраняем текущий плейлист под тем же именем
      if(listFileName.isEmpty())
        {
          listFileName = QFileDialog::getSaveFileName(this,
                                      QString::fromUtf8("Сохранить список воспроизведения"),
                                      QDir::currentPath(),
                                      "Списки воспроизведения (*.m3u *.m3u8);;Все файла (*.*)");

          // Пользователь отменил сохранение файла
          if(listFileName.isEmpty())
            return;
        }

      stBar->showMessage("Список воспроизведения сохранен");
      setModified(false);
    }
}

// Обработка выбора пункта меню Список - Сохранить как
void MainWindow::slotListSaveAs()
{
  // Запрашиваем имя нового файла и сохраянем текущй плейлист под этим именем
  // Изменяем имя файла текущего листа на новый
  listFileName = QFileDialog::getSaveFileName(this,
                              QString::fromUtf8("Сохранить список воспроизведения"),
                              QDir::currentPath(),
                              "Списки воспроизведения (*.m3u *.m3u8);;Все файлы (*.*)");

  // Пользователь отменил сохранение файла
  if(listFileName.isEmpty())
    return;

  setModified(false);
}

// Обработка выбора пункта меню Список - Выход
void MainWindow::slotAppClose()
{
  if(modified)
    {
      QMessageBox::StandardButton res =
          QMessageBox::warning(this,
                               "Внимание!",
                               "Имеются <u>несохраненные изменения!</u>\nВыйти в любом случае?",
                               QMessageBox::Yes | QMessageBox::No,
                               QMessageBox::No);
      if(res == QMessageBox::Yes)
        {
          close();
        }
    }
  else
    {
      close();
    }
}

