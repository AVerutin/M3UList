#include "soundtracks.h"

SoundTracks::SoundTracks(QWidget *parent) : QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
  tracks = new QStringList;
  createCentralWidget();
}


/// Компоновка формы
void SoundTracks::createCentralWidget()
{
  trackEdit = new QListWidget;
  trackEdit->clear();

  btnAdd = new QPushButton(tr("Добавить"));
  connect(btnAdd, &QPushButton::clicked, this, &SoundTracks::slotAddTrack);
  btnEdit = new QPushButton(tr("Правка"));
  connect(btnEdit, &QPushButton::clicked, this, &SoundTracks::slotEditTrack);
  btnDelete = new QPushButton(tr("Удалить"));
  connect(btnDelete, &QPushButton::clicked, this, &SoundTracks::slotDeleteTrack);
  vSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);

  sideButtons = new QVBoxLayout;
  sideButtons->addWidget(btnAdd);
  sideButtons->addWidget(btnEdit);
  sideButtons->addWidget(btnDelete);
  sideButtons->addSpacerItem(vSpacer);

  line1 = new QHBoxLayout;
  line1->addWidget(trackEdit);
  line1->addLayout(sideButtons);

  hSpacer1 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
  hSpacer2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
  okButton = new QPushButton(tr("OK"));
  cancelButton = new QPushButton(tr("Отмена"));
  connect(okButton, &QPushButton::clicked, this, &SoundTracks::slotAccept);
  connect(cancelButton, &QPushButton::clicked, this, &SoundTracks::reject);

  line2 = new QHBoxLayout;
  line2->addSpacerItem(hSpacer1);
  line2->addWidget(okButton);
  line2->addWidget(cancelButton);
  line2->addSpacerItem(hSpacer2);

  mainLayout = new QVBoxLayout;
  mainLayout->addLayout(line1);
  mainLayout->addLayout(line2);
  setLayout(mainLayout);

  setWindowTitle("Аудиодорожки");
  setFixedSize(250, 250);
}


/// Обработка сигнала нажатия на кнопку Добавить
void SoundTracks::slotAddTrack()
{
  bool ok;
  QString text = QInputDialog::getText(this,
                               QString::fromUtf8("Звуковая дорожка"),
                               QString::fromUtf8("Дорожка:"),
                               QLineEdit::Normal,
                               "", &ok, Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
  if (ok && !text.isEmpty()){
      trackEdit->addItem(QString::fromUtf8("%1").arg(text));
    }
}


/// Правка списка звуковых дорожек
void SoundTracks::editSoundTracks(QStringList list)
{
  trackEdit->clear();

  // Сохраним оригинальный список и заполним список на форме
  if(list.size()>0)
    {
      tracks->clear();

      for(int i=0; i<list.size(); i++)
        {
          tracks->append(list[i]);
          trackEdit->addItem(list[i]);
        }
    }
}


/// Получить список звуковых дорожек
QStringList SoundTracks::getSoundTracks()
{
  return *tracks;
}


/// Обработка сигнала нажатия на кнопку Правка
void SoundTracks::slotEditTrack()
{
  bool ok;
  QString text = QInputDialog::getText(this,
                               QString::fromUtf8("Звуковая дорожка"),
                               QString::fromUtf8("Дорожка:"),
                               QLineEdit::Normal,
                               trackEdit->currentItem()->text(), &ok, Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
  if (ok && !text.isEmpty()){
      trackEdit->currentItem()->setText(QString::fromUtf8("%1").arg(text));
    }
}


/// Обработка сигнала нажатия на кнопку Удалить
void SoundTracks::slotDeleteTrack()
{
  delete trackEdit->takeItem(trackEdit->currentRow());
}


/// Обработка сигнала нажатия на кнопку OK
void SoundTracks::slotAccept()
{
  // Сохраняем значение из списка в список строк tracks
  tracks->clear();
  int t = trackEdit->count();
  for(int i = 0; i < t; i++)
      {
        tracks->append(trackEdit->item(i)->text());
      }

  accept();
}
