QT       += core # dbus

TARGET = togglewlanscan
CONFIG   += console
CONFIG   -= app_bundle
# For notifications
CONFIG += meegotouch
CONFIG += link_pkgconfig
PKGCONFIG += gq-gconf

TEMPLATE = app

SOURCES += main.cpp \
    togglewlanscan.cpp

contains(MEEGO_EDITION,harmattan) {
    target.path = /opt/togglewlanscan/bin
    INSTALLS += target

}

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/postinst \
    qtc_packaging/debian_harmattan/prerm \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog

HEADERS += \
    togglewlanscan.h

# Copied from qmlapplicationviewer
installPrefix = /opt/$${TARGET}

desktopfile.files = $${TARGET}_harmattan.desktop
desktopfile.path = /usr/share/applications
icon.files = $${TARGET}_on_80.png $${TARGET}_off_80.png
icon.path = /usr/share/icons/hicolor/80x80/apps
data.files = $${TARGET}_on_harmattan.desktop $${TARGET}_off_harmattan.desktop
data.path = /opt/togglewlanscan/data

export(icon.files)
export(icon.path)
export(desktopfile.files)
export(desktopfile.path)
INSTALLS += icon desktopfile data

target.path = $${installPrefix}/bin
export(target.path)
INSTALLS += target

export (ICON)
export (INSTALLS)
export (DEPLOYMENT)
export (TARGET.EPOCHEAPSIZE)
export (TARGET.CAPABILITY)
export (LIBS)
export (QMAKE_EXTRA_TARGETS)
