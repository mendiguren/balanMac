#include "basededatos.h"
#include "ui_basededatos.h"
#include <QSqlDatabase>
#include <QDebug>
#include "complementos/combodelegate.h"
#include "global.h"


BaseDeDatos::BaseDeDatos(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaseDeDatos)
{
    ui->setupUi(this);

    setObjectName("Base de datos");
    foreach(QString tableName,QSqlDatabase::database().tables())
    {
        ui->cbTable->addItem(tableName);
        QExtendedTable *table = new QExtendedTable(this);
        table->setTable(tableName);
        ui->swExtentedTable->addWidget(table);

        //Adding comboBox delegate for mysql enum
        for(int i=0; i < table->getModel()->columnCount(); ++i)
        {
            if(table->getModel()->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() == "prioridad")
            {
                ComboDelegate *cDelegate = new ComboDelegate(table,databaseManager->enumPrioridad);
                table->setColumnDelegate(i,cDelegate);
            }
            else if(table->getModel()->headerData(i, Qt::Horizontal, Qt::DisplayRole).toString() == "dimension")
            {
                ComboDelegate *cDelegate = new ComboDelegate(table,databaseManager->enumBalanzaSize);
                table->setColumnDelegate(i,cDelegate);
            }
        }
    }

    connect(ui->cbTable,SIGNAL(currentIndexChanged(int)),this,SLOT(cbTableChanged(int)));
}


BaseDeDatos::~BaseDeDatos()
{
    delete ui;
}






void BaseDeDatos::cbTableChanged(int index)
{
    static_cast<QExtendedTable*>(ui->swExtentedTable->currentWidget())->submit();
    ui->swExtentedTable->setCurrentIndex(index);
    updateView();
}

void BaseDeDatos::updateView()
{
    static_cast<QExtendedTable*>(ui->swExtentedTable->currentWidget())->updateTable();
}
