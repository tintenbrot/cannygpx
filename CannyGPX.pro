# Add more folders to ship with the application, here
folder_01.source = qml
folder_01.target = qml
DEPLOYMENTFOLDERS = folder_01

# Additional import path used to resolve QML modules in Creator's code model
QML_IMPORT_PATH =

symbian:TARGET.UID3 = 0xE0650B08

# Smart Installer package's UID
# This UID is from the protected range and therefore the package will
# fail to install if self-signed. By default qmake uses the unprotected
# range value if unprotected UID is defined for the application and
# 0x2002CCCF value if protected UID is given to the application
#symbian:DEPLOYMENT.installer_header = 0x2002CCCF

# Allow network access on Symbian
symbian:TARGET.CAPABILITY += NetworkServices

# If your application uses the Qt Mobility libraries, uncomment the following
# lines and add the respective components to the MOBILITY variable.
# CONFIG += mobility
# MOBILITY +=

# Speed up launching on MeeGo/Harmattan when using applauncherd daemon
# CONFIG += qdeclarative-boostable

# Add dependency to Symbian components
# CONFIG += qt-components

# The .cpp file which was generated for your project. Feel free to hack it.
SOURCES += main.cpp \
    src/gpxmodel.cpp \
    src/gpxviewer.cpp \
    src/gpx/gpxparser.cpp \
    src/gpx/gpxfileparser.cpp \
    src/gpx/cachelist.cpp \
    src/gpx/quazip-0.3/quazip/zip.c \
    src/gpx/quazip-0.3/quazip/unzip.c \
    src/gpx/quazip-0.3/quazip/quazipnewinfo.cpp \
    src/gpx/quazip-0.3/quazip/quazipfile.cpp \
    src/gpx/quazip-0.3/quazip/quazip.cpp \
    src/gpx/quazip-0.3/quazip/quacrc32.cpp \
    src/gpx/quazip-0.3/quazip/quaadler32.cpp \
    src/gpx/quazip-0.3/quazip/JlCompress.cpp \
    src/gpx/quazip-0.3/quazip/ioapi.c

# Please do not modify the following two lines. Required for deployment.
include(qmlapplicationviewer/qmlapplicationviewer.pri)
qtcAddDeployment()


HEADERS += \
    src/gpxmodel.h \
    src/gpxviewer.h \
    src/gpx/gpxparser.h \
    src/gpx/gpxfileparser.h \
    src/gpx/cachelist.h \
    src/gpx/quazip-0.3/quazip/zip.h \
    src/gpx/quazip-0.3/quazip/unzip.h \
    src/gpx/quazip-0.3/quazip/quazipnewinfo.h \
    src/gpx/quazip-0.3/quazip/quazipfileinfo.h \
    src/gpx/quazip-0.3/quazip/quazipfile.h \
    src/gpx/quazip-0.3/quazip/quazip.h \
    src/gpx/quazip-0.3/quazip/quacrc32.h \
    src/gpx/quazip-0.3/quazip/quachecksum32.h \
    src/gpx/quazip-0.3/quazip/quaadler32.h \
    src/gpx/quazip-0.3/quazip/JlCompress.h \
    src/gpx/quazip-0.3/quazip/ioapi.h \
    src/gpx/quazip-0.3/quazip/crypt.h

QT += declarative opengl script xmlpatterns sql network svg

OTHER_FILES += bar-descriptor.xml \
    src/gpx/quazip-0.3/quazip/quazip.pro

RESOURCES += CannyGPX.qrc
