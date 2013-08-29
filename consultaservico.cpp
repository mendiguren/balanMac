#include "consultaservico.h"
#include "ui_consultaservico.h"
#include <QSqlDatabase>
#include <QDebug>
#include "complementos/combodelegate.h"
#include "global.h"
#include <QMenu>
#include <QSqlRecord>
#include <QSqlField>

ConsultaServico::ConsultaServico(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::consultaServico)
{
    ui->setupUi(this);
    setObjectName("Consulta Servicio");

    listaTablas << "viewTransaccionesReparables";
    descripcionTabla <<"Balanzas a Reparar";

    listaTablas << "viewTransaccionesLimpiables";
    descripcionTabla << "Balanzas a Limpiar";

    listaTablas << "viewConfirmables";
    descripcionTabla << "Balanzas que Requieren Confirmacion";


    for(int tabla = 0; tabla < listaTablas.size(); ++tabla)
    {
        ui->cbTable->addItem(descripcionTabla.at(tabla));
        QExtendedTable *qExtendedTable = new QExtendedTable(this);
        qExtendedTable->setTable(listaTablas.at(tabla));
        qExtendedTable->setObjectName("tabla");
        ui->swExtentedTable->addWidget(qExtendedTable);

        //Show custom row menu
        connect(qExtendedTable,SIGNAL(rowShowContextMenu(QPoint)),this,SLOT(showCustomRowMenu(QPoint)));

        //Adding comboBox delegate for mysql enum
        for(int i=0; i < qExtendedTable->getModel()->columnCount(); ++i)
        {
            if(qExtendedTable->getModel()->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() == "prioridad")
            {
                ComboDelegate *cDelegate = new ComboDelegate(qExtendedTable,databaseManager->enumPrioridad);
                qExtendedTable->setColumnDelegate(i,cDelegate);
            }
            else if(qExtendedTable->getModel()->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() == "dimension")
            {
                ComboDelegate *cDelegate = new ComboDelegate(qExtendedTable,databaseManager->enumBalanzaSize);
                qExtendedTable->setColumnDelegate(i,cDelegate);
            }
        }

    }
    connect(ui->cbTable,SIGNAL(currentIndexChanged(int)),this,SLOT(cbTableChanged(int)));


}

ConsultaServico::~ConsultaServico()
{
    delete ui;
}

void ConsultaServico::reparacionDestoyed()
{
    ui->cbTable->setEnabled(true);
    ui->swExtentedTable->removeWidget(reparacion);
    ui->swExtentedTable->setCurrentIndex(0);
}

void ConsultaServico::confirmacionDestroyed()
{
    ui->cbTable->setEnabled(true);
    ui->swExtentedTable->removeWidget(confirmacion);
    ui->swExtentedTable->setCurrentIndex(2);

}

void ConsultaServico::cbTableChanged(int index)
{
    if(ui->swExtentedTable->currentWidget()->objectName() == "tabla")
    {
        static_cast<QExtendedTable*>(ui->swExtentedTable->currentWidget())->submit();
        ui->swExtentedTable->setCurrentIndex(index);
        updateView();
    }
}

void ConsultaServico::updateView()
{
    if(ui->swExtentedTable->currentWidget()->objectName() == "tabla")
    {
        static_cast<QExtendedTable*>(ui->swExtentedTable->currentWidget())->updateTable();
    }
}

void ConsultaServico::showCustomRowMenu(QPoint position)
{

    qDebug() << "opening custom menu";


    QString action;
    if(ui->cbTable->currentText()== descripcionTabla.at(0))    action = "Iniciar Reparacion";
    if(ui->cbTable->currentText()== descripcionTabla.at(1))    action = "Marcar Como Limpia";
    if(ui->cbTable->currentText()== descripcionTabla.at(2))    action = "Confirmar";




    QMenu menu;
    menu.addAction(action);

    QAction* selectedItem = menu.exec(position);

    if(selectedItem==NULL) return;
    if(selectedItem->text() == action)
    {
        QExtendedTable* qExtendedTable = qobject_cast<QExtendedTable*>(ui->swExtentedTable->currentWidget());
        QSqlRecord rec = qExtendedTable->getModel()->record( qExtendedTable->getTableView()->currentIndex().row());
        int idtransaccion = rec.field(0).value().toInt();
        qDebug() << rec;

        if(ui->cbTable->currentText()== descripcionTabla.at(0))
        { //TODO open repacion page

            reparacion = new Reparacion(this);
            ui->swExtentedTable->addWidget(reparacion);
            connect(reparacion,SIGNAL(destroyed()),this,SLOT(reparacionDestoyed()));
            ui->swExtentedTable->setCurrentWidget(reparacion);
            reparacion->initializeTransaccion(rec);
        }
        else if(ui->cbTable->currentText()== descripcionTabla.at(1))
        {
            databaseManager->setBalanzaAsLimpiada(idtransaccion);
        }
        else if(ui->cbTable->currentText()== descripcionTabla.at(2))
        {//TODO open llamadas page

            confirmacion = new confirmar(ui->swExtentedTable);
            ui->swExtentedTable->addWidget(confirmacion);
            connect(confirmacion,SIGNAL(destroyed()),this,SLOT(confirmacionDestroyed()));
            ui->swExtentedTable->setCurrentWidget(confirmacion);
            confirmacion->initializeTransaccion(idtransaccion);

        }
        ui->cbTable->setEnabled(false);
    }
    updateView();


}
