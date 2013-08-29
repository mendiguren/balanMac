#include "confirmar.h"
#include "ui_confirmar.h"
#include "databasemanager.h"
#include "global.h"

confirmar::confirmar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::confirmar)
{
    ui->setupUi(this);


    ui->tbBalanzas->removeItem(0);

}

confirmar::~confirmar()
{
    delete ui;
}

bool confirmar::initializeTransaccion(int idtransaccion)
{
    QStringList cliente = databaseManager->getCliente(idtransaccion);
    setLEClientes(cliente);

    QVector<int> transacciones = databaseManager->getBalanzas(idtransaccion);

    foreach(int balanza_idtransaccion,transacciones)
    {
        Confirmar_balanza *balanza = new Confirmar_balanza(this);
        vectorBalanzas.append(balanza);
        balanza->setBalanza(balanza_idtransaccion);
        ui->tbBalanzas->addItem(balanza,"Balanza");
    }
    return true;
}

void confirmar::setLEClientes(QStringList values)
{
    ui->leNombre->setText(values.at(1));
    ui->leApellido->setText(values.at(2));
    ui->leEmpresa->setText(values.at(3));
    ui->leEmail->setText(values.at(4));
    ui->leTelefonoFijo->setText(values.at(5));
    ui->leTelefonoCelular->setText(values.at(6));
    ui->leCiudad->setText(values.at(7));
    ui->leProvincia->setText(values.at(8));
    ui->leCp->setText(values.at(9));
    ui->leDireccion->setText(values.at(10));
}

void confirmar::on_pbIngresar_clicked()
{
    bool success = true;
    foreach(Confirmar_balanza* balanza,vectorBalanzas) //This check if all the information is complete
    {
        if(!balanza->checkCompletness()) success = false;
    }
    if(!success)  return;
    else
    {
        foreach(Confirmar_balanza* balanza,vectorBalanzas) //This check if all the information is complete
        {
            balanza->commit();
        }
    }
    deleteLater();
}

void confirmar::on_pbCancelar_clicked()
{
    deleteLater();

}
