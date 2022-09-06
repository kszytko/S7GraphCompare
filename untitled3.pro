QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17


VERSION = 0.1

CONFIG(debug,debug|release){
    CONFIG += console
}

test {
    message(Test build)

    QT += testlib
    TARGET = demo-test

    SOURCES += \
        graph.cpp \
        graphparser.cpp \
        tests/test_main.cpp \
        tests/graphParserTest.cpp \

    HEADERS += \
        graph.h \
        graphparser.h \

} else {
    message(Normal build)

    TARGET = demo

    SOURCES += \
        graph.cpp \
        graphparser.cpp \
        main.cpp \
        mainwindow.cpp \

    HEADERS += \
        graph.h \
        graphparser.h \
        mainwindow.h

    FORMS += \
        mainwindow.ui
}

target.path = $${TARGET}
INSTALLS += target

SOURCES += \
    tests/test_main.cpp


