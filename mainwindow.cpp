#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
{
  modified = false;

  createMenu();
  createWidget();

  listFileName = "E:\\Projects\\CPP\\m3u\\5368.m3u";
}

MainWindow::~MainWindow()
{
}

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
  mnPlayList->addAction(aListCreate);
  mnPlayList->addAction(aListOpen);
  mnPlayList->addAction(aListSave);
  mnPlayList->addAction(aListSaveAs);
  mnPlayList->addSeparator();
  mnPlayList->addAction(aAppClose);

  mnMainMenu = menuBar();
  mnMainMenu->addMenu(mnPlayList);
}

// Создание главного окна приложения
void MainWindow::createWidget()
{
  // Добавление элементов на главную форму
  vblMainLayout = new QVBoxLayout(this);

  // Установка виждета на главную форму приложения
  mainWidget = new QWidget(this);
  mainWidget->setLayout(vblMainLayout);

  setCentralWidget(mainWidget);
}

// Обработка выбора пункта меню Список - Создать
void MainWindow::slotListCreate()
{
  QMessageBox::information(this, "Внимание", "Выбран пункт меню <b>Создать новый список</b>", QMessageBox::Ok, QMessageBox::Ok);
}

// Обработка выбора пункта меню Список - Открыть
void MainWindow::slotListOpen()
{
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
  }

  QString msg = "Открыт файл [%1]: прочитано строк: %2";
  msg = msg.arg(listFileName).arg(playList->count());

  QMessageBox::information(this, "Внимание", msg, QMessageBox::Ok, QMessageBox::Ok);

  delete playList;
}

// Обработка выбора пункта меню Список - Сохранить
void MainWindow::slotListSave()
{
  QMessageBox::information(this, "Внимание", "Выбран пункт меню <b>Сохранить текущий список</b>", QMessageBox::Ok, QMessageBox::Ok);
}

// Обработка выбора пункта меню Список - Сохранить как
void MainWindow::slotListSaveAs()
{
  QMessageBox::information(this, "Внимание", "Выбран пункт меню <b>Сохранить список под другим именем</b>", QMessageBox::Ok, QMessageBox::Ok);
}

// Обработка выбора пункта меню Список - Выход
void MainWindow::slotAppClose()
{
  if(modified)
    {
      QMessageBox::StandardButton res = QMessageBox::warning(this,
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

