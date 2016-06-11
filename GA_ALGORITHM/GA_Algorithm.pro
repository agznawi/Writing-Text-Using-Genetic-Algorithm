TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    individual.cpp \
    population.cpp \
    evolution.cpp

HEADERS += \
    individual.h \
    population.h \
    evolution.h \
    randengine.h

