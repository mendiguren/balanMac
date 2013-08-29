#ifndef NUEVOINGRESO_H
#define NUEVOINGRESO_H

#include <QWidget>
#include <QCompleter>
#include <QSqlTableModel>
#include <QStringList>
#include <QTableView>
#include "sqlmulticompleter.h"

namespace Ui {
class nuevoIngreso;
}

class NuevoIngreso : public QWidget
{
    Q_OBJECT
    
public:
    explicit NuevoIngreso(QWidget *parent = 0);
    ~NuevoIngreso();

    QString getLastExecutedQuery(const QSqlQuery& query);
    
private:
    Ui::nuevoIngreso *ui;

    int nBalanzas;


    QWidget *nuevaBalanza();
    QStringList getLEClientes();
    void setLEClientes(QStringList values);

    QSqlTableModel *modelClientes;
    QSqlTableModel *viewPrestablesDisponibles;

    SqlMultiCompleter *completers;

    QVector<QTableView*> vectorPrestables;
    QVector<int> prestablesSeleccionadas;



signals:
    void tableMdified();

private slots:
    void on_pbIngresar_clicked();
    void tbBalanzasPageChanged(int index);
    void tbBalanzasDeletePage();
    void comboBoxPrestablesIndexChanged(int index);
    void checkBoxPrestable(bool enabled);
    void updateComboPrestables();
};

#endif // NUEVOINGRESO_H
