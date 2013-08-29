#include "nuevostockbalanza.h"
#include "ui_nuevostockbalanza.h"

NuevoStockBalanza::NuevoStockBalanza(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NuevoStockBalanza)
{
    ui->setupUi(this);
    setObjectName("Balanzas Nuevas");
}

NuevoStockBalanza::~NuevoStockBalanza()
{
    delete ui;
}
