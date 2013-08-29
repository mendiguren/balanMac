#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "complementos/QfNavBar/QfNavBar"

#include "global.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    showMaximized();
    ui->mainToolBar->hide();
    setWindowTitle("BalanMac [Enterprise Resource Planning] Sapo ");
    setWindowIcon(QIcon(":/icons/sapo.png"));
    setWindowIconText("Sapo ERP");

    //-->Add Side Bar
    QfNavBarGroup *group = ui->navbar->addGroup("SERVICIO TECNICO");
    ui->navbar->addItem(group, QPixmap(":/icons/book.png"), "Estadisticas");

    nuevoIngreso = new NuevoIngreso(this); ui->stackedWidget->addWidget(nuevoIngreso); ui->navbar->addItem(group, QPixmap(":/icons/new.png"),  nuevoIngreso->objectName());
    connect(nuevoIngreso,SIGNAL(destroyed()),this,SLOT(nuevoIngresoDestroyed()));

    ui->navbar->addItem(group, QPixmap(":/icons/z_allApps.png"),  "Retiro de Balanzas");
    consultaServicio = new ConsultaServico(this);  ui->stackedWidget->addWidget(consultaServicio); ui->navbar->addItem(group, QPixmap(":/icons/check.png"),  consultaServicio->objectName());
    ui->navbar->addItem(group, QPixmap(":/icons/plata.png"),  "Facturacion");

    group = ui->navbar->addGroup("VENTAS");
    ui->navbar->addItem(group, QPixmap(":/icons/book.png"), "Estadisticas");
    nuevaVenta = new NuevaVenta(this); ui->stackedWidget->addWidget(nuevaVenta); ui->navbar->addItem(group, QPixmap(":/icons/new.png"),  nuevaVenta->objectName());
    ui->navbar->addItem(group, QPixmap(":/icons/check.png"),  "Consultas");
    ui->navbar->addItem(group, QPixmap(":/icons/plata.png"),  "Facturacion");

    group = ui->navbar->addGroup("STOCK");
    nuevoStockBalanza = new NuevoStockBalanza(this); ui->stackedWidget->addWidget(nuevoStockBalanza); ui->navbar->addItem(group, QPixmap(":/icons/balanza.png"), nuevoStockBalanza->objectName());
    nuevoStockRepuestos = new NuevoStockRepuestos(this); ui->stackedWidget->addWidget(nuevoStockRepuestos); ui->navbar->addItem(group, QPixmap(":/icons/stock.png"), nuevoStockRepuestos->objectName());

    group = ui->navbar->addGroup("SISTEMA");
    baseDeDatos = new BaseDeDatos(this); ui->stackedWidget->addWidget(baseDeDatos); ui->navbar->addItem(group, QPixmap(":/icons/db.png"), baseDeDatos->objectName());


    connect(ui->navbar,SIGNAL(itemClicked(QString,QString)),this,SLOT(sidebarClicked(QString,QString)));
    //<--Add Side Bar

}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::sidebarClicked(QString group, QString item)
{
    if(item == nuevoIngreso->objectName()) ui->stackedWidget->setCurrentWidget(nuevoIngreso);
    else if(item == consultaServicio->objectName()  && group == "SERVICIO TECNICO")
    {
        ui->stackedWidget->setCurrentIndex(2);
        consultaServicio->updateView();
    }
    else if(item == nuevaVenta->objectName()) ui->stackedWidget->setCurrentWidget(nuevaVenta);
    else if(item == baseDeDatos->objectName()) ui->stackedWidget->setCurrentWidget(baseDeDatos);
    else if(item == nuevoStockBalanza->objectName()) ui->stackedWidget->setCurrentWidget(nuevoStockBalanza);
    else if(item == nuevoStockRepuestos->objectName()) ui->stackedWidget->setCurrentWidget(nuevoStockRepuestos);
    else ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::nuevoIngresoDestroyed()
{
    ui->stackedWidget->removeWidget(nuevoIngreso);
    nuevoIngreso = new NuevoIngreso(this);
    ui->stackedWidget->addWidget(nuevoIngreso);
    ui->stackedWidget->setCurrentWidget(nuevoIngreso);
}
