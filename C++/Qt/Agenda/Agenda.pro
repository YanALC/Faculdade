#-------------------------------------------------
#
# Project created by QtCreator 2017-05-19T11:30:55
#
#-------------------------------------------------

QT       += core gui
#QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Agenda
TEMPLATE = app

#INCLUDEPATH += C:/kqoauth-kqoauth/include C:/kqoauth-kqoauth/src
#LIBS += -LC:/kqoauth-kqoauth/lib

CONFIG += console c++11

SOURCES += main.cpp\
    emailui.cpp \
    telefoneui.cpp \
    enderecoui.cpp \
    agendaui.cpp \
    contato.cpp \
    contatoui.cpp \
    dados.cpp \
    listartudo.cpp \
    arquivo.cpp \
    teladeopcoes.cpp \
    listaragendas.cpp

HEADERS  += \
    lista.h \
    no.h \
    emailui.h \
    telefoneui.h \
    enderecoui.h \
    agendaui.h \
    contato.h \
    contatoui.h \
    dados.h \
    listartudo.h \
    arquivo.h \
    teladeopcoes.h \
    listaragendas.h

FORMS    += \
    emailui.ui \
    telefoneui.ui \
    enderecoui.ui \
    contatoui.ui \
    agendaui.ui \
    listartudo.ui \
    teladeopcoes.ui \
    listaragendas.ui

DISTFILES += \
    ./data/Agendas.txt \
    ./data/YanContatos.txt \
    ./data/YanEmails.txt \
    ./data/YanEnderecos.txt \
    ./data/YanTelefones.txt

CONFIG(debug, debug|release) {
    VARIANT = debug
} else {
    VARIANT = release
}

install_it.path = $$OUT_PWD//$$VARIANT/
install_it.files = data/*
INSTALLS += install_it
