QT += widgets multimedia sql multimediawidgets network

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    lyrics.cpp \
    main.cpp \
    mainwindow.cpp \
    music.cpp \
    musicdao.cpp \
    musicwindow.cpp \
    videowindow.cpp

HEADERS += \
    lyrics.h \
    mainwindow.h \
    music.h \
    musicdao.h \
    musicwindow.h \
    videowindow.h

FORMS += \
    mainwindow.ui \
    musicwindow.ui \
    videowindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resouses.qrc

DISTFILES += \
    ../../../../resource/picture/full.png \
    ../../../../resource/picture/full_hover.png \
    ../../../../resource/picture/icon_music.png
