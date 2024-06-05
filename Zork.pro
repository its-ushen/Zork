QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    HelperUtils.cpp \
    country.cpp \
    functionalitem.cpp \
    gameengine.cpp \
    item.cpp \
    main.cpp \
    mainwindow.cpp \
    outfititem.cpp \
    player.cpp \
    specialitem.cpp \
    travelmanager.cpp \
    traveloption.cpp

HEADERS += \
    GameState.h \
    HelperUtils.h \
    Leaderboard.h \
    MyException.h \
    country.h \
    functionalitem.h \
    gameengine.h \
    item.h \
    mainwindow.h \
    multiplechoicequestion.h \
    outfititem.h \
    player.h \
    question.h \
    specialitem.h \
    travelmanager.h \
    traveloption.h \
    truefalsequestion.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
