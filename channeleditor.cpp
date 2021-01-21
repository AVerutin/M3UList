#include "channeleditor.h"

ChannelEditor::ChannelEditor(QWidget *parent) : QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
  channel = new Channel;

  createCentralWidget();
}


/// Добавить новый канал
Channel ChannelEditor::getChannel()
{
  return *channel;
}

void ChannelEditor::setTitle(const QString title)
{
  if(!title.isEmpty())
    {
      winTitle = title;
      setWindowTitle(title);
    }
}


/// Компоновка формы
void ChannelEditor::createCentralWidget()
{
  // Инициализация списков
  groups = new QStringList;
  groups->append(tr("Общие"));
  groups->append(tr("Информационные"));
  groups->append(tr("Образовательные"));
  groups->append(tr("Познавательные"));
  groups->append(tr("Детские"));

  audiotracks = new QStringList;
  audiotracks->append(tr("RUS"));
  audiotracks->append(tr("ENG"));
  audiotracks->append(tr("UKR"));

  // Линия 1
  lblGroup = new QLabel(tr("Группа"));
  cbGroup = new QComboBox;
  lblGroup->setBuddy(cbGroup);
  cbGroup->clear();
  cbGroup->addItems(*groups);
  pbManageGroups = new QPushButton(tr("Группы"));
  connect(pbManageGroups, &QPushButton::clicked, this, &ChannelEditor::slotManageGroups);
  line1 = new QHBoxLayout;
  line1->addWidget(lblGroup);
  line1->addWidget(cbGroup, 1);
  line1->addWidget(pbManageGroups);

  // Линия 2
  lblName = new QLabel(tr("Имя"));
  leName = new QLineEdit;
  lblName->setBuddy(leName);
  hSpacer3 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
  lblId = new QLabel(tr("ID"));
  leId = new QLineEdit;
  lblId->setBuddy(leId);
  lblDuration = new QLabel(":");
  leDuration = new QLineEdit;
  lblDuration->setBuddy(leDuration);
  line2 = new QHBoxLayout;
  line2->addWidget(lblName);
  line2->addWidget(leName);
  line2->addSpacerItem(hSpacer3);
  line2->addWidget(lblId);
  line2->addWidget(leId, 1);
  line2->addWidget(lblDuration);
  line2->addWidget(leDuration, 1);

  // Линия 3
  lblLogo = new QLabel(tr("Логотип"));
  leLogo = new QLineEdit;
  lblLogo->setBuddy(leLogo);
  hSpacer4 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
  cbByName = new QCheckBox(tr("По имени"));
  line3 = new QHBoxLayout;
  line3->addWidget(lblLogo);
  line3->addWidget(leLogo, 1);
  line3->addSpacerItem(hSpacer4);
  line3->addWidget(cbByName);

  // Линия 4
  lblShift = new QLabel(tr("Сдвиг"));
  leShift = new QLineEdit;
  lblShift->setBuddy(leShift);
  hSpacer5 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
  cbRadio = new QCheckBox(tr("Радио"));
  cbHasArchive = new QCheckBox(tr("Архив"));
  line4 = new QHBoxLayout;
  line4->addWidget(lblShift);
  line4->addWidget(leShift, 1);
  line4->addSpacerItem(hSpacer5);
  line4->addWidget(cbRadio);
  line4->addWidget(cbHasArchive);

  // Линия 5
  cbCensored = new QCheckBox(tr("Для взрослых"));
  hSpacer6 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
  cbAgeControl = new QCheckBox(tr("Родительский контроль"));
  line5 = new QHBoxLayout;
  line5->addWidget(cbCensored);
  line5->addSpacerItem(hSpacer6);
  line5->addWidget(cbAgeControl);

  // Линия 6
  lblAudio = new QLabel(tr("Звуковая дорожка"));
  cbAudio = new QComboBox;
  cbAudio->addItems(*audiotracks);
  lblAudio->setBuddy(cbAudio);
  pbManageAudio = new QPushButton(tr("Дорожки"));
  connect(pbManageAudio, &QPushButton::clicked, this, &ChannelEditor::slotManageTracks);
  line6 = new QHBoxLayout;
  line6->addWidget(lblAudio);
  line6->addWidget(cbAudio, 1);
  line6->addWidget(pbManageAudio);

  // Линия 7
  lblSource = new QLabel(tr("Источник"));
  leSource = new QLineEdit;
  lblSource->setBuddy(lblSource);
  line7 = new QHBoxLayout;
  line7->addWidget(lblSource);
  line7->addWidget(leSource);

  // Линия кнопок
  hSpacer1 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
  pbOk = new QPushButton(tr("OK"));
  connect(pbOk, &QPushButton::clicked, this, &ChannelEditor::slotAccept);
  pbCancel = new QPushButton(tr("Отмена"));
  connect(pbCancel, &QPushButton::clicked, this, &ChannelEditor::reject);
  hSpacer2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
  lineButtons = new QHBoxLayout;
  lineButtons->addSpacerItem(hSpacer1);
  lineButtons->addWidget(pbOk, 0);
  lineButtons->addWidget(pbCancel, 0);
  lineButtons->addSpacerItem(hSpacer2);

  // Компоновка формы
  mainLayout = new QVBoxLayout;
  mainLayout->addLayout(line1);
  mainLayout->addLayout(line2);
  mainLayout->addLayout(line3);
  mainLayout->addLayout(line4);
  mainLayout->addLayout(line5);
  mainLayout->addLayout(line6);
  mainLayout->addLayout(line7);
  mainLayout->addLayout(lineButtons);
  setLayout(mainLayout);
  winTitle = winTitle.isEmpty() ? "Новый канал" : winTitle;
  setWindowTitle(winTitle);
  setFixedSize(380, 250);
}


/// Обработка сигнала нажатия на кнопку OK
void ChannelEditor::slotAccept()
{
  channel->groupName = cbGroup->currentText();
  channel->tvgName = leName->text();
  channel->tvgId = leId->text().toInt();
  channel->duration = leDuration->text().toInt();
  channel->tvgLogo = leLogo->text();
  channel->nameAsKey = cbByName->isChecked();
  channel->tvgShift = leShift->text().toInt();
  channel->radio = cbRadio->isChecked();
  channel->recordable = cbHasArchive->isChecked();
  channel->censored = cbCensored->isChecked();
  channel->ageRestriction = cbAgeControl->isChecked();
  channel->audioTrack = cbAudio->currentText();
  channel->url = leSource->text();
  accept();
}

/// Обработка сигнала нажатия на кнопку Управление группами
void ChannelEditor::slotManageGroups()
{
  // Вызов окна со списком групп каналов
  GroupsEditor *grp = new GroupsEditor(this);
  grp->editGroups(*groups);
  int res = grp->exec();

  if(res == QDialog::Accepted)
    {
      *groups = grp->getGroups();
    }
  else

  delete grp;
  grp = nullptr;
  // Конец вызова окна со списком групп каналов

  if(groups->size() > 0)
    {
      cbGroup->clear();
      cbGroup->addItems(*groups);
    }
}


/// Обработка сигнала нажатия на кнопку Управление звуковыми дорожками
void ChannelEditor::slotManageTracks()
{
  // Вызов окна со списком звуковых дорожек
  SoundTracks *snd = new SoundTracks(this);
  snd->editSoundTracks(*audiotracks);
  QStringList st;
  int res = snd->exec();
  if(res == QDialog::Accepted)
    {
      *audiotracks = snd->getSoundTracks();
    }

  delete snd;
  snd = nullptr;
  // Конец вызова окна со списком звуковых дорожек

  if(audiotracks->size() > 0)
    {
      cbAudio->clear();
      cbAudio->addItems(*audiotracks);
    }
}
