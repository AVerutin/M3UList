/// Форма управления группами каналов

#ifndef GROUPSEDITOR_H
#define GROUPSEDITOR_H

#include <QDialog>
#include <QInputDialog>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringList>
#include <QSpacerItem>


class GroupsEditor : public QDialog
{
  Q_OBJECT
public:
  explicit GroupsEditor(QWidget *parent = nullptr);
  void editGroups(const QStringList);
  QStringList getGroups();
  void setGroups(QStringList);

private:
  QStringList *groups;

  // Элементы формы
  QVBoxLayout *mainLayout;
  QHBoxLayout *line1;
  QHBoxLayout *line2;
  QVBoxLayout *sideButtons;
  QSpacerItem * vSpacer;
  QPushButton *btnAdd;
  QPushButton *btnEdit;
  QPushButton *btnDelete;
  QListWidget *groupsEdit;
  QPushButton *okButton;
  QPushButton *cancelButton;
  QSpacerItem *hSpacer1;
  QSpacerItem *hSpacer2;

  void createCentralWidget();

private slots:
  void slotAddGroup();
  void slotEditGroup();
  void slotDeleteGroup();
  void slotAccept();

};

#endif // GROUPSEDITOR_H
