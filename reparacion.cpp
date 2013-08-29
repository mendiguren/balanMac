#include "reparacion.h"
#include "ui_reparacion.h"
#include "global.h"
#include <QSqlField>

Reparacion::Reparacion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Reparacion)
{
    ui->setupUi(this);

    QRegExp rx("[0-9]*[.][0-9]{1,2}");
    QValidator* validatorNum = new QRegExpValidator (rx, this);
    ui->lePrecio->setAlignment(Qt::AlignRight);
    ui->lePrecio->setValidator(validatorNum);


}

Reparacion::~Reparacion()
{
    delete ui;
}

void Reparacion::initializeTransaccion(QSqlRecord rec)
{
    QStringList values = databaseManager->getTransaccion(rec.field(0).value().toInt());

    ui->lePrecio->setText(values.at(0));
    ui->leMarca->setText(values.at(1));
    ui->leModelo->setText(values.at(2));
    ui->pteObservaciones->setPlainText(values.at(4));
    ui->pteAccesorios->setPlainText(values.at(5));

    ui->leUbicacion->setText(rec.field(1).value().toString());
}



void Reparacion::on_pbCancelar_clicked()
{
    deleteLater();
}

void Reparacion::on_pbAceptar_clicked()
{
    deleteLater();
}
