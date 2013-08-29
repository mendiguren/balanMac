#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>
#include <QSqlError>
#include <QDebug>

#include "nuevoingreso.h"
#include "consultaservico.h"
#include "basededatos.h"
#include "nuevaventa.h"
#include "nuevostockbalanza.h"
#include "nuevostockrepuestos.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;

    //--> Stacked Widget
    NuevoIngreso *nuevoIngreso;
    ConsultaServico *consultaServicio;
    BaseDeDatos *baseDeDatos;
    NuevaVenta *nuevaVenta;
    NuevoStockBalanza *nuevoStockBalanza;
    NuevoStockRepuestos *nuevoStockRepuestos;
    //<-- Stacked Widget


    QSqlTableModel *model;

public slots:
    void sidebarClicked(QString group,QString item);
    void nuevoIngresoDestroyed();
};

#endif // MAINWINDOW_H
