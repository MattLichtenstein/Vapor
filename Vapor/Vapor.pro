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
    Components/VDropdown.cpp \
    Components/VLabel.cpp \
    Components/VNavigator.cpp \
    Components/VButton.cpp \
    Components/VProgressBar.cpp \
    Components/VResultItem.cpp \
    Components/VScrollArea.cpp \
    Components/VThreatItem.cpp \
    Components/VWindowTitleBar.cpp \
    Main/main.cpp \
    Main/VMainWindow.cpp \
    Models/VScanData.cpp \
    Utilities/XMLReader.cpp \
    Views/VResultsPage.cpp \
    Views/VScanInProgressPage.cpp \
    Views/VScanPage.cpp

HEADERS += \
    Components/VDropdown.h \
    Components/VLabel.h \
    Components/VNavigator.h \
    Components/VProgressBar.h \
    Components/VResultItem.h \
    Components/VScrollArea.h \
    Components/VThreatItem.h \
    Components/VWindowTitleBar.h \
    Main/VMainWindow.h \
    Models/VScanData.h \
    Utilities/VColors.h \
    Utilities/VIcons.h \
    Utilities/VPaths.h \
    Utilities/VSizes.h \
    Components/VButton.h \
    Utilities/XMLReader.h \
    Views/VResultsPage.h \
    Views/VScanInProgressPage.h \
    Views/VScanPage.h

TRANSLATIONS += \
    Vapor_en_US.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
