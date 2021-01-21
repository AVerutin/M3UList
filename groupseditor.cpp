#include "groupseditor.h"

GroupsEditor::GroupsEditor(QWidget *parent)
  : QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
  groups = new QStringList;
  createCentralWidget();
}


/// Установить список групп
void GroupsEditor::setGroups(QStringList grps)
{
  if(grps.size() > 0)
    {
      groups->clear();
      for(int i=0; i<grps.size(); i++)
        {
          groups->append(grps.at(i));
        }
    }
}


/// Компоновка формы
void GroupsEditor::createCentralWidget()
{
  groupsEdit = new QListWidget;
  groupsEdit->clear();

  btnAdd = new QPushButton(tr("Добавить"));
  connect(btnAdd, &QPushButton::clicked, this, &GroupsEditor::slotAddGroup);
  btnEdit = new QPushButton(tr("Правка"));
  connect(btnEdit, &QPushButton::clicked, this, &GroupsEditor::slotEditGroup);
  btnDelete = new QPushButton(tr("Удалить"));
  connect(btnDelete, &QPushButton::clicked, this, &GroupsEditor::slotDeleteGroup);
  vSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);

  sideButtons = new QVBoxLayout;
  sideButtons->addWidget(btnAdd);
  sideButtons->addWidget(btnEdit);
  sideButtons->addWidget(btnDelete);
  sideButtons->addSpacerItem(vSpacer);

  line1 = new QHBoxLayout;
  line1->addWidget(groupsEdit);
  line1->addLayout(sideButtons);

  hSpacer1 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
  hSpacer2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
  okButton = new QPushButton(tr("OK"));
  cancelButton = new QPushButton(tr("Отмена"));
  connect(okButton, &QPushButton::clicked, this, &GroupsEditor::slotAccept);
  connect(cancelButton, &QPushButton::clicked, this, &GroupsEditor::reject);

  line2 = new QHBoxLayout;
  line2->addSpacerItem(hSpacer1);
  line2->addWidget(okButton);
  line2->addWidget(cancelButton);
  line2->addSpacerItem(hSpacer2);

  mainLayout = new QVBoxLayout;
  mainLayout->addLayout(line1);
  mainLayout->addLayout(line2);
  setLayout(mainLayout);

  setWindowTitle("Группы");
  setFixedSize(250, 250);
}


/// Обработка сигнала нажатия на кнопку Добавить
void GroupsEditor::slotAddGroup()
{
  bool ok;
  QString text = QInputDialog::getText(this,
                               QString::fromUtf8("Группа каналов"),
                               QString::fromUtf8("Группа:"),
                               QLineEdit::Normal,
                               "", &ok, Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
  if (ok && !text.isEmpty()){
      groupsEdit->addItem(QString::fromUtf8("%1").arg(text));
    }
}


/// Правка списка звуковых дорожек
void GroupsEditor::editGroups(const QStringList list)
{
  groupsEdit->clear();

  // Сохраним оригинальный список и заполним список на форме
  if(list.size()>0)
    {
      groups->clear();

      for(int i=0; i<list.size(); i++)
        {
          groups->append(list[i]);
          groupsEdit->addItem(list[i]);
        }
    }
}


/// Получить список звуковых дорожек
QStringList GroupsEditor::getGroups()
{
  return *groups;
}


/// Обработка сигнала нажатия на кнопку Правка
void GroupsEditor::slotEditGroup()
{
  bool ok;
  QString text = QInputDialog::getText(this,
                               QString::fromUtf8("Группа каналов"),
                               QString::fromUtf8("Группа:"),
                               QLineEdit::Normal,
                               groupsEdit->currentItem()->text(), &ok, Qt::WindowTitleHint | Qt::WindowSystemMenuHint);
  if (ok && !text.isEmpty()){
      groupsEdit->currentItem()->setText(QString::fromUtf8("%1").arg(text));
    }
}


/// Обработка сигнала нажатия на кнопку Удалить
void GroupsEditor::slotDeleteGroup()
{
  delete groupsEdit->takeItem(groupsEdit->currentRow());
}


/// Обработка сигнала нажатия на кнопку OK
void GroupsEditor::slotAccept()
{
  // Сохраняем значение из списка в список строк tracks
  groups->clear();
  int t = groupsEdit->count();
  for(int i = 0; i < t; i++)
      {
        groups->append(groupsEdit->item(i)->text());
      }

  accept();
}
