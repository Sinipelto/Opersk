TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    tiedostonluku.cpp \
    kayttoliittyma.cpp \
    rakenne.cpp

HEADERS += \
    tiedostonluku.hh \
    kayttoliittyma.hh \
    rakenne.hh

DISTFILES += \
    temp.txt \
    input2.txt \
    input.txt
