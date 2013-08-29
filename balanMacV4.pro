#-------------------------------------------------
#
# Project created by QtCreator 2013-06-27T13:45:49
#
#-------------------------------------------------

QT       += core gui sql
CONFIG += console debug
QMAKE_CXXFLAGS += -std=c++0x

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = balanMacV4
TEMPLATE = app


SOURCES += main.cpp\
    databasemanager.cpp \
    global.cpp \
    nuevoingreso.cpp \
    sqlmulticompleter.cpp \
    mainwindow.cpp \
    consultaservico.cpp \
    complementos/qextendedtable.cpp \
    complementos/tdpreviewdialog.cpp \
    complementos/QfNavBar/selectablewidget.cpp \
    complementos/QfNavBar/navbaritem.cpp \
    complementos/QfNavBar/navbargroup.cpp \
    complementos/QfNavBar/navbar.cpp \
    complementos/QfNavBar/clickablelabel.cpp \
    complementos/QSpreadsheetHeaderView.cpp \
    complementos/csvexporter.cpp \
    complementos/wwWidgets/widgets/qwwclearlineedit/qwwclearlineedit.cpp \
    complementos/wwWidgets/widgets/qwwbuttonlineedit/qwwbuttonlineedit.cpp \
    complementos/wwWidgets/widgets/wwglobal_p.cpp \
    complementos/datetimedelegate.cpp \
    complementos/combodelegate.cpp \
    complementos/nonscrollablecombobox.cpp \
    complementos/qesccompleter.cpp \
    reparacion.cpp \
    basededatos.cpp \
    confirmar.cpp \
    confirmar_balanza.cpp \
    nuevostockbalanza.cpp \
    nuevostockrepuestos.cpp \
    nuevaventa.cpp

HEADERS  += \
    databasemanager.h \
    global.h \
    nuevoingreso.h \
    sqlmulticompleter.h \
    mainwindow.h \
    consultaservico.h \
    complementos/qextendedtable.h \
    complementos/tdpreviewdialog.h \
    complementos/QfNavBar/QfUiExport \
    complementos/QfNavBar/qf_uiexport.h \
    complementos/QfNavBar/QfSelectableWidget \
    complementos/QfNavBar/qf_selectablewidget.h \
    complementos/QfNavBar/QfNavBarItem \
    complementos/QfNavBar/qf_navbaritem.h \
    complementos/QfNavBar/QfNavBarGroup \
    complementos/QfNavBar/qf_navbargroup.h \
    complementos/QfNavBar/QfNavBar \
    complementos/QfNavBar/qf_navbar.h \
    complementos/QfNavBar/QfClickableLabel \
    complementos/QfNavBar/qf_clickablelabel.h \
    complementos/QSpreadsheetHeaderView.h \
    complementos/csvexporter.h \
    complementos/wwWidgets/widgets/qwwclearlineedit/QwwClearLineEdit \
    complementos/wwWidgets/widgets/qwwclearlineedit/qwwclearlineedit.h \
    complementos/wwWidgets/widgets/qwwbuttonlineedit/qwwbuttonlineedit_p.h \
    complementos/wwWidgets/widgets/qwwbuttonlineedit/QwwButtonLineEdit \
    complementos/wwWidgets/widgets/qwwbuttonlineedit/qwwbuttonlineedit.h \
    complementos/wwWidgets/widgets/wwglobal_p.h \
    complementos/wwWidgets/widgets/wwglobal.h \
    complementos/datetimedelegate.h \
    complementos/combodelegate.h \
    complementos/nonscrollablecombobox.h \
    complementos/qesccompleter.h \
    reparacion.h \
    basededatos.h \
    confirmar.h \
    confirmar_balanza.h \
    nuevostockbalanza.h \
    nuevostockrepuestos.h \
    nuevaventa.h

FORMS    += \
    nuevoingreso.ui \
    mainwindow.ui \
    consultaservico.ui \
    complementos/qextendedtable.ui \
    complementos/csvexporter.ui \
    reparacion.ui \
    basededatos.ui \
    confirmar.ui \
    confirmar_balanza.ui \
    nuevostockbalanza.ui \
    nuevostockrepuestos.ui \
    nuevaventa.ui


RESOURCES += \
    icons.qrc


