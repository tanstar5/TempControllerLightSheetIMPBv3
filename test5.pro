QT += quick serialport core

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        communicatorqml.cpp \
        main.cpp

RESOURCES += qml.qrc



CONFIG-= static
#CONFIG += dll

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    ../temp/app_environment.h \
    ../temp/import_qml_plugins.h \
    communicatorqml.h

DISTFILES += \
    ../temp/UITempController.qmlproject \
    ../temp/UserInterface.qml \
    ../temp/qtquickcontrols2.conf \
    PNG/Asset 1@4x.png \
    PNG/Asset 1@4x.png \
    UntitledProject2/qtquickcontrols2.conf
