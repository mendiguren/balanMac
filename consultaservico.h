#ifndef CONSULTASERVICO_H
#define CONSULTASERVICO_H

#include <QWidget>
#include "complementos/qextendedtable.h"
#include "reparacion.h"
#include "confirmar.h"


namespace Ui {
class consultaServico;
}

class ConsultaServico : public QWidget
{
    Q_OBJECT
    
public:
    explicit ConsultaServico(QWidget *parent = 0);
    ~ConsultaServico();
    

private:
    Ui::consultaServico *ui;

    QStringList listaTablas;
    QStringList descripcionTabla;

    Reparacion *reparacion;
    confirmar *confirmacion;



private slots:
    void reparacionDestoyed();
    void confirmacionDestroyed();


public slots:
    void updateView();
    void showCustomRowMenu(QPoint position);
    void cbTableChanged(int index);


};

#endif // CONSULTASERVICO_H
