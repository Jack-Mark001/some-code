QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bmi.cpp \
    imgshowwindow.cpp \
    indexwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    registwindow.cpp

HEADERS += \
    bmi.h \
    imgshowwindow.h \
    indexwindow.h \
    mainwindow.h \
    registwindow.h

FORMS += \
    bmi.ui \
    imgshowwindow.ui \
    indexwindow.ui \
    mainwindow.ui \
    registwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
