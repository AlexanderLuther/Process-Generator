QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

QMAKE_CXXFLAGS += -std=c++0x -pthread -lrt
LIBS += -pthread -lrt


SOURCES += \
    Command.cpp \
    CommandDriver.cpp \
    Main.cpp \
    MainFrame.cpp \
    SharedMemoryDriver.cpp \
    Stem.cpp \
    Branch.cpp \
    FilesDriver.cpp \
    Leaf.cpp \
    Process.cpp

HEADERS += \
    MainFrame.h \
    Command.h \
    CommandDriver.h \
    SharedMemoryDriver.h \
    Stem.h \
    Branch.h \
    CommandType.h \
    FilesDriver.h \
    Leaf.h \
    Process.h

FORMS += \
    mainframe.ui

TRANSLATIONS += \
    ProcessGenerator_es_GT.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target



