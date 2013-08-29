#include "qextendedtable.h"
#include "ui_qextendedtable.h"
#include "QSpreadsheetHeaderView.h"
#include <QSortFilterProxyModel>
#include "csvexporter.h"
#include "tdpreviewdialog.h"
#include <QMenu>
#include "datetimedelegate.h"

#include <QDebug>


QExtendedTable::QExtendedTable(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QExtendedTable)
{
    ui->setupUi(this);

    connect(ui->leSearchText,SIGNAL(buttonClicked()),this,SLOT(clearSearch()));
    connect(ui->leSearchText,SIGNAL(returnPressed()),this,SLOT(on_pushButton_clicked()));
    connect(ui->leSearchText,SIGNAL(textEdited(QString)),this,SLOT(checkClear(QString)));
    ui->leSearchText->setPlaceholderText("Buscar...");

    //Set a datetime delegate
    DateTimeDelegate* dtDelegate= new DateTimeDelegate(this);
    ui->tableView->setItemDelegate(dtDelegate);

    printer = new QPrinter(QPrinter::HighResolution);//For printing pdf

   setWindowFlags(Qt::FramelessWindowHint);
}

QExtendedTable::~QExtendedTable()
{
    delete ui;
}

void QExtendedTable::setTable(QString tableName)
{

    model = new QSqlTableModel(this);

    model->setTable(tableName);
    model->select();

    header = new QSpreadsheetHeaderView(Qt::Horizontal, this);
    ui->tableView->setHorizontalHeader(header);
    header->setResizeMode(QHeaderView::ResizeToContents);



    proxy = new QSortFilterProxyModel;
    proxy->setSourceModel(model);
    proxy->setFilterKeyColumn(-1);


    ui->tableView->setModel(proxy);
    ui->tableView->setContextMenuPolicy(Qt::CustomContextMenu);

    model->setEditStrategy(QSqlTableModel::OnFieldChange);

    connect(ui->tableView,SIGNAL(customContextMenuRequested(QPoint)),this,SLOT(ShowContextMenu(QPoint)));

}

void QExtendedTable::on_pushButton_clicked()
{
    QString searchText = ui->leSearchText->text().trimmed();
    proxy->setFilterFixedString(searchText);

}

void QExtendedTable::clearSearch()
{
    proxy->setFilterFixedString("");
}

void QExtendedTable::checkClear(QString text)
{
    if(text.isEmpty())
    {
        clearSearch();
    }
}

void QExtendedTable::ShowContextMenu(const QPoint &pos)
{
    // for most widgets
        QPoint globalPos = this->mapToGlobal(pos);
        globalPos.setX(globalPos.x()+30);
        globalPos.setY(globalPos.y()+80);
        // for QAbstractScrollArea and derived classes you would use:
        // QPoint globalPos = myWidget->viewport()->mapToGlobal(pos)


        if(receivers(SIGNAL(rowShowContextMenu(QPoint))) > 0) // Check only if some class is connected to this signal
        {

            int selectedRow = ui->tableView->rowAt(pos.y());
            if(selectedRow != -1)
            { //A row has been selected
                ui->tableView->selectRow(ui->tableView->rowAt(pos.y()));
                emit rowShowContextMenu(globalPos);
                return;
            }
        }




        QString a1 = "Agregar Fila Al Final";
        QString a2 = "Eliminar Filas Seleccionadas";
        QString a3 = "Exportar Tabla CSV(Excel)";
        QString a4 = "Exportar Tabla Como PDF";

        QMenu myMenu;
        myMenu.addAction(a1);
        myMenu.addAction(a2);
        myMenu.addSeparator();
        myMenu.addAction(a3);
        myMenu.addAction(a4);
        // ...



        QAction* selectedItem = myMenu.exec(globalPos);

        if(selectedItem==NULL) return;
        if(selectedItem->text()==a1)
        {
            qDebug() << model->headerData(model->rowCount()-1,Qt::Vertical);
            if(model->headerData(model->rowCount()-1,Qt::Vertical) != "*" || model->rowCount() == 0)//No permite agregar varios rows nuevos en simultaneo
            {
                model->insertRow(model->rowCount());
            }
            clearSearch();
        }
        if(selectedItem->text()==a2)
        {
            QModelIndexList selection( ui->tableView->selectionModel()->selectedRows());


            QList<int> rows;
            foreach( const QModelIndex & index, selection) {
               rows.append( index.row() );
            }

            qSort( rows );

            int prev = -1;
            for( int i = rows.count() - 1; i >= 0; i -= 1 ) {
               int current = rows[i];
               if( current != prev ) {
                  model->removeRows( current, 1 );
                  prev = current;
               }
            }
        }
        if(selectedItem->text() == a3)
        {
            CSVExporter *dialog = new CSVExporter (ui->tableView,this);
            dialog->exec();
        }
        else if(selectedItem->text() == a4)
        {
            TDPreviewDialog *dialog = new TDPreviewDialog (ui->tableView,printer,this);
            dialog->setHeaderText("BalanMac - "+model->tableName());
            dialog->exportPdf("balanmac-"+model->tableName());
            delete dialog;

        }

}

void QExtendedTable::updateTable()
{
    model->select();
    ui->tableView->reset();

}


void QExtendedTable::submit()
{
    proxy->submit();
}

void QExtendedTable::setColumnDelegate(int column, QAbstractItemDelegate *delegate)
{
    ui->tableView->setItemDelegateForColumn(column,delegate);
}

QSqlTableModel* QExtendedTable::getModel()
{
    return model;
}

QTableView *QExtendedTable::getTableView()
{
    return ui->tableView;
}
