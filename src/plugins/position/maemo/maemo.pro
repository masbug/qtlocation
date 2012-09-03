TARGET = qtposition_maemo
QT += location gui dbus

load(qt_plugin)

DESTDIR = $$QT.location.plugins/position

INCLUDEPATH += $$QT.location.includes

SOURCES += qgeopositioninfosource_maemo.cpp \
            qgeosatelliteinfosource_maemo.cpp \
            dbuscomm_maemo.cpp \
            dbusserver_maemo.cpp \
    qgeopositioninfosourcefactory_maemo.cpp
HEADERS += qgeopositioninfosource_maemo_p.h \
            qgeosatelliteinfosource_maemo_p.h \
            dbuscomm_maemo_p.h \
            dbusserver_maemo_p.h \
    qgeopositioninfosourcefactory_maemo.h

target.path += $$[QT_INSTALL_PLUGINS]/position
INSTALLS += target

OTHER_FILES += \
    plugin.json
