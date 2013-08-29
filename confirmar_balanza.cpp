#include "confirmar_balanza.h"
#include "ui_confirmar_balanza.h"
#include "global.h"

Confirmar_balanza::Confirmar_balanza(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Confirmar_balanza)
{
    ui->setupUi(this);
    ui->cbPrioridad->addItems(databaseManager->enumPrioridad);
    ui->cbPrioridad->setDisabled(true);

    connect(ui->rbConfirmada,SIGNAL(clicked()),this,SLOT(setRedBackground()));
    connect(ui->rbNoResponde,SIGNAL(clicked()),this,SLOT(setRedBackground()));
    connect(ui->rbRechazada,SIGNAL(clicked()),this,SLOT(setRedBackground()));


}

Confirmar_balanza::~Confirmar_balanza()
{
    delete ui;
}

void Confirmar_balanza::setBalanza(int idtransaccion)
{ //TODO set transaccion
    QStringList values = databaseManager->getTransaccion(idtransaccion);

    ui->lePrecio->setText(values.at(0));
    ui->leMarca->setText(values.at(1));
    ui->leModelo->setText(values.at(2));
    ui->cbPrioridad->setCurrentIndex(databaseManager->enumPrioridad.indexOf(values.at(3)));
    ui->pteObservaciones->setPlainText(values.at(4));
    ui->pteAccesorios->setPlainText(values.at(5));

    if(values.at(6).toInt() !=0)
    {
         ui->tableView->setModel(databaseManager->getPrestable(idtransaccion,this));
    }
}

bool Confirmar_balanza::checkCompletness()
{
    if(!ui->rbRechazada->isChecked() && !ui->rbConfirmada->isChecked() && !ui->rbNoResponde->isChecked())
    {//No state has been chosed
        ui->groupBox->setStyleSheet("background-color:red;");
        return false;
    }
    return true;
}

void Confirmar_balanza::commit()
{//TODO commit changes confirmacion

}

void Confirmar_balanza::setRedBackground()
{
    ui->groupBox->setStyleSheet("");
}
