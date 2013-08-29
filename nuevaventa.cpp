#include "nuevaventa.h"
#include "ui_nuevaventa.h"

NuevaVenta::NuevaVenta(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NuevaVenta)
{
    ui->setupUi(this);

    setObjectName("Nueva Venta");
}

NuevaVenta::~NuevaVenta()
{
    delete ui;
}
