QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    container.cpp \
    containerhandlerdialog.cpp \
    helpwindow.cpp \
    imdgunit.cpp \
    imdgunithandlerdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    xmltag.cpp

HEADERS += \
    container.h \
    containerhandlerdialog.h \
    helpwindow.h \
    imdgunit.h \
    imdgunithandlerdialog.h \
    mainwindow.h \
    xmltag.h

FORMS += \
    containerhandlerdialog.ui \
    helpwindow.ui \
    imdgunithandlerdialog.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


RESOURCES +=

DISTFILES += \
    tests/IMDG DEBRV no weight.cxml \
    tests/IMDG DEBRV no weight.cxml \
    tests/IMDG DEBRV only.txt \
    tests/IMDG DEBRV only.txt \
    tests/IMDG MXATM only.cxml \
    tests/IMDG MXATM only.cxml \
    tests/IMDG Manifest Rotterdam.txt \
    tests/IMDG Manifest Rotterdam.txt \
    tests/IMDG Rotterdam.cxml \
    tests/IMDG Rotterdam.cxml \
    tests/IMDG only DEBRV.cxml \
    tests/IMDG only DEBRV.cxml \
    tests/IMDG test cargo.cxml \
    tests/IMDG test cargo.cxml \
    tests/IMDG.edi \
    tests/MXATM.txt
