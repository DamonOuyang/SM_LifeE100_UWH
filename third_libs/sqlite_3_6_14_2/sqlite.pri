INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

# Input
HEADERS += $$PWD/sqlite3.h \
           $$PWD/sqlite3ext.h \
	   $$PWD/sqlite_funcs.h \
	   $$PWD/sqlite_us16_wrapper.h \
           $$PWD/SQLiteWrapper.h

SOURCES += $$PWD/sqlite3.c \
	   $$PWD/sqlite_funcs.cpp \
	   $$PWD/sqlite_us16_wrapper.cpp \
           $$PWD/SQLiteWrapper.cpp
