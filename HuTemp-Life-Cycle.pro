#-------------------------------------------------
#
# Project created by QtCreator 2019-04-07T10:12:34
#
#-------------------------------------------------

QT       += core gui printsupport network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HuTemp-Life-Cycle
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
    passwordreset.cpp \
    previoususersdialog.cpp \
    smtp.cpp \
        widget.cpp \
    quickviewsdialogbox.cpp \
    zonesdialogbox.cpp \
    devicesdialogbox.cpp \
    readingsdialogbox.cpp \
    periodsdialogbox.cpp \
    newpasswordpostresetdialog.cpp \
    additionalsettingsnotificationsdialog.cpp \
    additionaladminsettingsdialog.cpp \
    helpdialog.cpp \
    contactsupportdialog.cpp \
    addauserdialog.cpp

HEADERS += \
    passwordreset.h \
    previoususersdialog.h \
    smtp.h \
        widget.h \
    quickviewsdialogbox.h \
    zonesdialogbox.h \
    devicesdialogbox.h \
    readingsdialogbox.h \
    periodsdialogbox.h \
    newpasswordpostresetdialog.h \
    additionalsettingsnotificationsdialog.h \
    additionaladminsettingsdialog.h \
    helpdialog.h \
    contactsupportdialog.h \
    addauserdialog.h

FORMS += \
    passwordreset.ui \
    previoususersdialog.ui \
        widget.ui \
    quickviewsdialogbox.ui \
    zonesdialogbox.ui \
    devicesdialogbox.ui \
    readingsdialogbox.ui \
    periodsdialogbox.ui \
    newpasswordpostresetdialog.ui \
    additionalsettingsnotificationsdialog.ui \
    additionaladminsettingsdialog.ui \
    helpdialog.ui \
    contactsupportdialog.ui \
    addauserdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
