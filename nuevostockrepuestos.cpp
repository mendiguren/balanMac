#include "nuevostockrepuestos.h"
#include "ui_nuevostockrepuestos.h"

NuevoStockRepuestos::NuevoStockRepuestos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NuevoStockRepuestos)
{
    ui->setupUi(this);

    setObjectName("Repuestos");
}

NuevoStockRepuestos::~NuevoStockRepuestos()
{
    delete ui;
}
