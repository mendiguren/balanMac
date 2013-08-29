#include "nuevoingreso.h"
#include "global.h"
#include "ui_nuevoingreso.h"
#include "complementos/nonscrollablecombobox.h"

#include <QSqlQuery>
#include <QtSql>
#include <QLayout>
#include <QPlainTextEdit>
#include <QModelIndex>
#include <QPushButton>
#include <QObjectList>
#include <QAbstractItemView>
#include <QMessageBox>
#include <QSizePolicy>
#include <QTime>
#include <QDateTime>
#include <QPlainTextEdit>
#include <QTableView>
#include <QCheckBox>


NuevoIngreso::NuevoIngreso(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::nuevoIngreso)
{
    ui->setupUi(this);

    setObjectName("Nuevo Ingreso");

    if(!QSqlDatabase::database().isOpen())
    {
        QMessageBox::critical(0,"Database Error","Database is not open.");
    }

    viewPrestablesDisponibles = new QSqlTableModel(this);
    viewPrestablesDisponibles->setTable("viewPrestablesDisponibles");
    viewPrestablesDisponibles->select();

    modelClientes = new QSqlTableModel(this);
    modelClientes->setTable("clientes");
    modelClientes->select();

    completers = new SqlMultiCompleter("viewClientes",this);
    completers->attachColumn(ui->leNombre,1);
    completers->attachColumn(ui->leApellido,2);
    completers->attachColumn(ui->leEmpresa,3);
    completers->attachColumn(ui->leEmail,4);
    completers->attachColumn(ui->leTelefonoFijo,5);
    completers->attachColumn(ui->leTelefonoCelular,6);
    completers->attachColumn(ui->leCiudad,7);
    completers->attachColumn(ui->leProvincia,8);
    completers->attachColumn(ui->leCp,9);
    completers->attachColumn(ui->leDireccion,10);

    ui->tbBalanzas->setMinimumHeight(320);
    ui->tbBalanzas->setSizePolicy(QSizePolicy::MinimumExpanding,QSizePolicy::MinimumExpanding);
    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());

    nBalanzas = 1;
    ui->tbBalanzas->insertItem(0,nuevaBalanza(),"Balanza 1");
    ui->tbBalanzas->setCurrentIndex(0);

    connect(ui->tbBalanzas,SIGNAL(currentChanged(int)),this,SLOT(tbBalanzasPageChanged(int)));

    ui->leNombre->setMaxLength(255);
    ui->leApellido->setMaxLength(255);
    ui->leEmpresa->setMaxLength(255);
    ui->leEmail->setMaxLength(255);
    ui->leTelefonoFijo->setMaxLength(255);
    ui->leTelefonoCelular->setMaxLength(255);
    ui->leCiudad->setMaxLength(255);
    ui->leProvincia->setMaxLength(255);
    ui->leCp->setMaxLength(255);
    ui->leDireccion->setMaxLength(255);


}

NuevoIngreso::~NuevoIngreso()
{
    delete ui;
}

QWidget *NuevoIngreso::nuevaBalanza()
{
        QWidget *page = new QWidget(this);
        //-->Boton de eliminar page
        QPushButton *button = new QPushButton(page);
        button->setIcon(QIcon(":/icons/delete.png"));
        button->setIconSize(QSize(20,20));
        button->setMaximumSize(15,15);
        connect(button,SIGNAL(clicked()),this,SLOT(tbBalanzasDeletePage()));

        //-->Modelo
        QLineEdit *leModelo =  new QLineEdit(page);
        leModelo->setMaxLength(255);
        leModelo->setObjectName("leModelo");
        QLabel *lModelo = new QLabel("Modelo",page);
        QVBoxLayout *vlModelo = new QVBoxLayout();
        vlModelo->addWidget(lModelo);
        vlModelo->addWidget(leModelo);
        //-->Marca
        QLineEdit *leMarca =  new QLineEdit(page);
        leMarca->setObjectName("leMarca");
        leMarca->setMaxLength(255);
        QLabel *lMarca = new QLabel("Marca",page);
        QVBoxLayout *vlMarca = new QVBoxLayout();
        vlMarca->addWidget(lMarca);
        vlMarca->addWidget(leMarca);
        //-->Tamaño
        QComboBox *cbDimension =  new QComboBox(page);
        cbDimension->setObjectName("cbTamano");
        cbDimension->insertItems(0,databaseManager->enumBalanzaSize);
        cbDimension->setCurrentIndex(-1);
        QLabel *lTamano= new QLabel("Tamano",page);
        QVBoxLayout *vlTamano = new QVBoxLayout();
        vlTamano->addWidget(lTamano);
        vlTamano->addWidget(cbDimension);

        //-->NumeroDeSerie
        QLineEdit *leNumeroDeSerie =  new QLineEdit(page);
        leNumeroDeSerie->setObjectName("leNumeroDeSerie");
        leNumeroDeSerie->setMaxLength(255);
        QLabel *lNumeroDeSerie = new QLabel("NumeroDeSerie",page);
        QVBoxLayout *vlNumeroDeSerie = new QVBoxLayout();
        vlNumeroDeSerie->addWidget(lNumeroDeSerie);
        vlNumeroDeSerie->addWidget(leNumeroDeSerie);
        //-->Prioridad
        QComboBox *cbPrioridad =  new QComboBox(page);
        cbPrioridad->setObjectName("cbPrioridad");
        cbPrioridad->insertItem(0,"Alta");
        cbPrioridad->insertItem(1,"Normal");
        cbPrioridad->insertItem(2,"Baja");
        cbPrioridad->setCurrentIndex(-1);
        QLabel *lPrioridad = new QLabel("Prioridad",page);
        QVBoxLayout *vlPrioridad = new QVBoxLayout();
        vlPrioridad->addWidget(lPrioridad);
        vlPrioridad->addWidget(cbPrioridad);
        //-->Accesorios
        QPlainTextEdit *pteAccesorios =  new QPlainTextEdit(page);
        pteAccesorios->setTabChangesFocus(true);
        pteAccesorios->setObjectName("pteAccesorios");
        QLabel *lAccesorios = new QLabel("Accesorios",page);
        QVBoxLayout *vlAccesorios = new QVBoxLayout();
        vlAccesorios->addWidget(lAccesorios);
        vlAccesorios->addWidget(pteAccesorios);
        //-->Observaciones
        QPlainTextEdit *pteObservaciones =  new QPlainTextEdit(page);
        pteObservaciones->setTabChangesFocus(true);
        pteObservaciones->setObjectName("pteObservaciones");
        QLabel *lObservaciones = new QLabel("Observaciones",page);
        QVBoxLayout *vlObservaciones = new QVBoxLayout();
        vlObservaciones->addWidget(lObservaciones);
        vlObservaciones->addWidget(pteObservaciones);

        //-->Prestables
        QCheckBox *checkBoxPrestables = new QCheckBox("Prestar Balanza", page);
        checkBoxPrestables->setObjectName("checkBoxPrestables"); //I set a number as the object name
        NonScrollableComboBox *comboBoxPrestables = new NonScrollableComboBox(page);
        comboBoxPrestables->setObjectName("comboBoxPrestables"); //I set a number as the object name

        QTableView *vPrestables = new QTableView(page);
        vPrestables->setObjectName(QString::number(vectorPrestables.size())); //I set a number as the object name
        vectorPrestables.append(vPrestables);
        prestablesSeleccionadas.append(-1);
        vPrestables->setModel(viewPrestablesDisponibles);
        vPrestables->resizeColumnsToContents();
        vPrestables->resizeRowsToContents();
        vPrestables->verticalHeader()->setVisible(false);
        vPrestables->setMinimumWidth(vPrestables->horizontalHeader()->length());
        vPrestables->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        vPrestables->setSelectionMode(QAbstractItemView::SingleSelection);
        vPrestables->setSelectionBehavior(QAbstractItemView::SelectRows);
        vPrestables->setAutoScroll(false);
        comboBoxPrestables->setModel(viewPrestablesDisponibles);
        comboBoxPrestables->setModelColumn(0);
        comboBoxPrestables->setView(vPrestables);
        comboBoxPrestables->setCurrentIndex(-1);
        QVBoxLayout *vlPrestables = new QVBoxLayout();
        vlPrestables->addWidget(checkBoxPrestables);
        vlPrestables->addWidget(comboBoxPrestables);

        comboBoxPrestables->setEnabled(false);
        connect(checkBoxPrestables,SIGNAL(toggled(bool)),comboBoxPrestables,SLOT(setEnabled(bool)));
        connect(checkBoxPrestables,SIGNAL(toggled(bool)),this,SLOT(checkBoxPrestable(bool)));

        connect(comboBoxPrestables,SIGNAL(currentIndexChanged(int)),this,SLOT(comboBoxPrestablesIndexChanged(int)));


        //sqlmulticompleter
        SqlMultiCompleter *balanzaCompleter = new SqlMultiCompleter("viewBalanzas",page);
        balanzaCompleter->attachColumn(leNumeroDeSerie,1);
        balanzaCompleter->attachColumn(cbPrioridad,2);
        balanzaCompleter->attachColumn(leModelo,3);
        balanzaCompleter->attachColumn(leMarca,4);
        balanzaCompleter->attachColumn(cbDimension,5);
        //Set the layout
        QGridLayout *grid = new QGridLayout(page);

        grid->addWidget(button,1,5,Qt::AlignTop);
        grid->addLayout(vlNumeroDeSerie,1,1,1,2);
        grid->addLayout(vlPrioridad,1,3,1,2);
        grid->setRowStretch(1,1);

        grid->addLayout(vlModelo,2,1);
        grid->addLayout(vlMarca,2,2);
        grid->addLayout(vlTamano,2,3,1,2);
        grid->setRowStretch(2,1);

        grid->addLayout(vlObservaciones,3,1,1,2);
        grid->addLayout(vlAccesorios,3,3,1,2);
        grid->setRowStretch(3,20);

        grid->addLayout(vlPrestables,4,1,1,4);
        grid->setRowStretch(4,1);

        page->setGeometry(5,5,250,250);
        page->setMaximumHeight(250);
        page->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Fixed);

        updateComboPrestables();
        return page;

}

QStringList NuevoIngreso::getLEClientes()
{
    QStringList valores;
    valores << ui->leNombre->text();
    valores << ui->leApellido->text();
    valores << ui->leEmpresa->text();
    valores << ui->leEmail->text();
    valores << ui->leTelefonoFijo->text();
    valores << ui->leTelefonoCelular->text();
    valores << ui->leCiudad->text();
    valores << ui->leProvincia->text();
    valores << ui->leCp->text();
    valores << ui->leDireccion->text();

    return valores;
}

void NuevoIngreso::setLEClientes(QStringList values)
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

void NuevoIngreso::on_pbIngresar_clicked()
{
    int idCiudad  = databaseManager->insertCiudad(ui->leCp->text().toInt(), ui->leCiudad->text() ,ui->leProvincia->text());
    int idCliente = databaseManager->insertCliente(ui->leNombre->text(), ui->leApellido->text(), ui->leEmpresa->text(), ui->leEmail->text(),
                                  ui->leTelefonoFijo->text(), ui->leTelefonoCelular->text(), ui->leDireccion->text(), idCiudad);

    for(int page = 0; page < ui->tbBalanzas->count()-1; ++page)
    {
          QWidget *balanza = ui->tbBalanzas->widget(page);

          QLineEdit *leMarca =  balanza->findChild<QLineEdit* >("leMarca");
          QLineEdit *leModelo =  balanza->findChild<QLineEdit* >("leModelo");
          QLineEdit *leNumeroDeSerie = balanza->findChild<QLineEdit*>("leNumeroDeSerie");
          QComboBox *cbPrioridad =  balanza->findChild<QComboBox*>("cbPrioridad");
          QPlainTextEdit *pteAccesorios = balanza->findChild<QPlainTextEdit*>("pteAccesorios");
          QPlainTextEdit *pteObservaciones =  balanza->findChild<QPlainTextEdit*>("pteObservaciones");
          QComboBox *cbTamano =  balanza->findChild<QComboBox*>("cbTamano");


          QString marca = leMarca->text();
          QString model = leModelo->text();
          int idBalanza = databaseManager->insertBalanza(leMarca->text(),leModelo->text(),cbTamano->currentIndex());

          QString idPrestable;
          if(prestablesSeleccionadas.at(page) == -1) { idPrestable = "null"; }
          else { idPrestable = QString::number(viewPrestablesDisponibles->record(prestablesSeleccionadas.at(page)).field(0).value().toInt());}

          qDebug() << "PRESTABLE SELECCIONADA ID = " << viewPrestablesDisponibles->record(prestablesSeleccionadas.at(page)).field(0).value();

          int idUbicacion = databaseManager->getUbicacion(cbTamano->currentIndex());
          databaseManager->insertTransaccion(leNumeroDeSerie->text(),cbPrioridad->currentText(),pteAccesorios->toPlainText(),pteObservaciones->toPlainText(),idCliente,idBalanza,idPrestable,idUbicacion,ui->dateTimeEdit->dateTime().toString("yyyy-MM-dd hh:mm:ss"));
          //WARNING check in windows to change the date format
    }

    close();
    emit tableMdified();  //WARNING check this signal is still usefull
    deleteLater();
}

void NuevoIngreso::tbBalanzasPageChanged(int index)
{
    if(index == ui->tbBalanzas->count()-1)
     {

         ui->tbBalanzas->setCurrentIndex(ui->tbBalanzas->count()-2);
         ui->tbBalanzas->insertItem(ui->tbBalanzas->count()-1,nuevaBalanza(),"Balanza "+QString::number(++nBalanzas));
         ui->tbBalanzas->setMinimumHeight(280+nBalanzas*32);
         ui->tbBalanzas->setCurrentIndex(ui->tbBalanzas->count()-2);
    }
}

void NuevoIngreso::tbBalanzasDeletePage()
{
    //Agrega a la lista de balanzas prestables , la que se habia incluida en el combobox de la pagina a eliminar
    QCheckBox* checkBoxPrestables = ui->tbBalanzas->currentWidget()->findChild<QCheckBox*>("checkBoxPrestables");
    checkBoxPrestables->setChecked(false);

    if(ui->tbBalanzas->count()>2)
    {
        int actualIndex = ui->tbBalanzas->currentIndex();
        ui->tbBalanzas->setCurrentIndex(actualIndex-1);
        ui->tbBalanzas->removeItem(actualIndex);
        ui->tbBalanzas->setMinimumHeight(280+nBalanzas*32);
    }
    else  //There is only one tab balanzas so, Insted of deleting it I clean it!
    {
        //Clear all the line edits of the page
        QList<QLineEdit*> list = ui->tbBalanzas->currentWidget()->findChildren<QLineEdit*>();
        foreach(QLineEdit* le, list) {
            le->setText("");
        }
        //Clear all the PlainTextEdit
        QList<QPlainTextEdit*> listP = ui->tbBalanzas->currentWidget()->findChildren<QPlainTextEdit*>();
        foreach(QPlainTextEdit* le, listP) {
            le->setPlainText("");
        }
    }
    ui->tbBalanzas->setFocus();
}

void NuevoIngreso::comboBoxPrestablesIndexChanged(int index)
{
     prestablesSeleccionadas[ui->tbBalanzas->currentIndex()]=index;
     updateComboPrestables();
}

void NuevoIngreso::checkBoxPrestable(bool enabled)
{
    if(enabled == false)
    {
        QComboBox* comboBoxPrestables = ui->tbBalanzas->currentWidget()->findChild<QComboBox*>("comboBoxPrestables");
        comboBoxPrestables->setCurrentIndex(-1);
    }
}

void NuevoIngreso::updateComboPrestables()
{
    //Show all rows
    foreach(QTableView* view,vectorPrestables)
    {
        for(int i=0; i < viewPrestablesDisponibles->rowCount() ; ++i)
        {
            view->showRow(i);
        }
    }

    for(int comboSelecionador=0; comboSelecionador < prestablesSeleccionadas.size(); ++comboSelecionador)
    {
        int seleccionada = prestablesSeleccionadas.at(comboSelecionador);
        foreach(QTableView* view,vectorPrestables)
        {
            if(comboSelecionador != view->objectName().toInt()  && seleccionada != -1)
            {//I hide all the selected prestable from all the combo box except the one from where it was choseen
                qDebug() << "hidding row " << seleccionada << " int the tableView number " << view->objectName();
                view->hideRow(seleccionada);
            }
        }
    }
}

