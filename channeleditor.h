/// Форма редактора каналов

#ifndef CHANNELEDITOR_H
#define CHANNELEDITOR_H

#include <QDialog>
#include <QtWidgets>
#include <QtSql>

#include "channel.h"
#include "soundtracks.h"
#include "groupseditor.h"

class ChannelEditor : public QDialog
{
  Q_OBJECT
public:
  explicit ChannelEditor(QWidget *parent = nullptr);
  ~ChannelEditor();

  Channel getChannel();
  void setTitle(const QString);

private:
  QString winTitle;
  Channel *channel;
  QStringList *groups;
  QStringList *audiotracks;

  // Элементы формы
  QVBoxLayout *mainLayout;

  QHBoxLayout *line1;
  QLabel *lblGroup;
  QComboBox *cbGroup;
  QPushButton *pbManageGroups;

  QHBoxLayout *line2;
  QLabel *lblName;
  QLineEdit *leName;
  QSpacerItem *hSpacer3;
  QLabel *lblId;
  QLineEdit *leId;
  QLabel *lblDuration;
  QLineEdit *leDuration;

  QHBoxLayout *line3;
  QLabel *lblLogo;
  QLineEdit *leLogo;
  QSpacerItem *hSpacer4;
  QCheckBox *cbByName;

  QHBoxLayout *line4;
  QLabel *lblShift;
  QLineEdit *leShift;
  QSpacerItem *hSpacer5;
  QCheckBox *cbRadio;
  QCheckBox *cbHasArchive;

  QHBoxLayout *line5;
  QCheckBox *cbCensored;
  QSpacerItem *hSpacer6;
  QCheckBox *cbAgeControl;

  QHBoxLayout *line6;
  QLabel *lblAudio;
  QComboBox *cbAudio;
  QPushButton *pbManageAudio;

  QHBoxLayout *line7;
  QLabel *lblSource;
  QLineEdit *leSource;

  QHBoxLayout *lineButtons;
  QSpacerItem *hSpacer1;
  QPushButton *pbOk;
  QPushButton *pbCancel;
  QSpacerItem *hSpacer2;

  QSqlDatabase sdb;
  QSqlQuery *query;
  QStringList groupsList;
  QStringList tracksList;

  void createCentralWidget();
  void dbInit();

private slots:
  void slotAccept();
  void slotManageGroups();
  void slotManageTracks();

};

#endif // CHANNELEDITOR_H
