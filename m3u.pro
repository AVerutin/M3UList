QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    channel.cpp \
    channeleditor.cpp \
    groupseditor.cpp \
    main.cpp \
    mainwindow.cpp \
    playlist.cpp \
    playlistparser.cpp \
    soundtracks.cpp

HEADERS += \
    channel.h \
    channeleditor.h \
    datatypes.h \
    groupseditor.h \
    mainwindow.h \
    playlist.h \
    playlistparser.h \
    soundtracks.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    playlist.qrc


win32 {
        RC_FILE += icon.rc
        OTHER_FILES += icon.rc
}

FORMS +=


