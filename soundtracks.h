/// Управление звуковыми дорожками

#ifndef SOUNDTRACKS_H
#define SOUNDTRACKS_H

#include <QDialog>
#include <QInputDialog>
#include <QListWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QStringList>
#include <QSpacerItem>

class SoundTracks : public QDialog
{
  Q_OBJECT
public:
  explicit SoundTracks(QWidget *parent = nullptr);
  void editSoundTracks(const QStringList);
  QStringList getSoundTracks();

private:
  QStringList *tracks;

  // Элементы формы
  QVBoxLayout *mainLayout;
  QHBoxLayout *line1;
  QHBoxLayout *line2;
  QVBoxLayout *sideButtons;
  QSpacerItem * vSpacer;
  QPushButton *btnAdd;
  QPushButton *btnEdit;
  QPushButton *btnDelete;
  QListWidget *trackEdit;
  QPushButton *okButton;
  QPushButton *cancelButton;
  QSpacerItem *hSpacer1;
  QSpacerItem *hSpacer2;

  void createCentralWidget();

private slots:
  void slotAddTrack();
  void slotEditTrack();
  void slotDeleteTrack();
  void slotAccept();
};

#endif // SOUNDTRACKS_H
