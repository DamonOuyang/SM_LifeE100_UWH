INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

HEADERS += \
    $$PWD/guard.h \
    $$PWD/lock_def.h \
    $$PWD/lockex.h \
    $$PWD/lock.h


SOURCES += \
    $$PWD/guard.cpp \
    $$PWD/lockex.cpp \
    $$PWD/lock.c

