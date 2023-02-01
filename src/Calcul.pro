QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../src/CalcFiles/calc.c \
    ../src/CalcFiles/calc_polish_notation_module.c \
    ../src/QCfiles/graph.cpp \
    ../src/CalcFiles/alib_dynamic_module.c \
    ../src/plot/qcustomplot.cpp \
    ../src/CalcFiles/read_term_module.c \
    ../src/CalcFiles/transfer_to_polish_notation.c \
    ../src/QCfiles/main.cpp \
    ../src/QCfiles/mainwindow.cpp

HEADERS += \
    ../src/CalcFiles/calc.h \
    ../src/CalcFiles/calc_polish_notation_module.h \
    ../src/CalcFiles/errors.h \
    ../src/QCfiles/graph.h \
    ../src/CalcFiles/alib_dynamic_module.h \
    ../src/plot/qcustomplot.h \
    ../src/CalcFiles/read_term_module.h \
    ../src/CalcFiles/transfer_to_polish_notation.h \
    ../src/QCfiles/mainwindow.h

FORMS += \
    ../src/QCfiles/graph.ui \
    ../src/QCfiles/mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
