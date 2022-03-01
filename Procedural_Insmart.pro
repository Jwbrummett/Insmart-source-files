TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    market.cpp \
    market.cpp

HEADERS += \
    stockdatatypes.h

DISTFILES += \
    stockLocations.conf \
    stocks_winner.data \
    stocks_loser.data
