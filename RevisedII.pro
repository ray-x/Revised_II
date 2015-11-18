#-------------------------------------------------
#
# Project created by QtCreator 2015-06-10T19:22:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RevisedII
TEMPLATE = app


SOURCES += \
    src/chapter.cpp \
    src/chapterlist.cpp \
    src/charactercombobox.cpp \
    src/charactermanager.cpp \
    src/choicemenueditor.cpp \
    src/codeeditor.cpp \
    src/configurationwindow.cpp \
    src/gameoptionsmanager.cpp \
    src/imagemanager.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/projectmgr.cpp \
    src/scenedesigner.cpp \
    src/scenepreviewer.cpp \
    src/step.cpp \
    src/videomanager.cpp \
    src/audiomanagerform.cpp \
    src/timerform.cpp \
    src/gameobject.cpp \
    src/choicemenueditorform.cpp

HEADERS  += \
    src/chapter.h \
    src/chapterlist.h \
    src/charactercombobox.h \
    src/charactermanager.h \
    src/choicemenueditor.h \
    src/codeeditor.h \
    src/configurationwindow.h \
    src/gameoptionsmanager.h \
    src/imagemanager.h \
    src/mainwindow.h \
    src/projectmgr.h \
    src/scenedesigner.h \
    src/scenepreviewer.h \
    src/step.h \
    src/videomanager.h \
    src/audiomanagerform.h \
    src/timerform.h \
    src/gameobject.h \
    src/choicemenueditorform.h

#FORMS    += mainwindow.ui

RESOURCES += \
    revised.qrc

DISTFILES += \
    translations/revised_ca.ts \
    translations/revised_de.ts \
    translations/revised_es.ts \
    translations/revised_fr.ts \
    translations/revised_it.ts


CONFIG += console

FORMS += \
    src/ImageManager.ui \
    src/videomanager.ui \
    src/audiomanagerform.ui \
    src/timerform.ui \
    src/choicemenueditorform.ui
