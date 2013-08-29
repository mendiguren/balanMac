#ifndef CONFIRMAR_H
#define CONFIRMAR_H

#include <QWidget>
#include "confirmar_balanza.h"


namespace Ui {
class confirmar;
}

class confirmar : public QWidget
{
    Q_OBJECT
    
public:
    explicit confirmar(QWidget *parent = 0);
    ~confirmar();

    bool initializeTransaccion(int idtransaccion);
    void setLEClientes(QStringList values);
private slots:
    void on_pbIngresar_clicked();

    void on_pbCancelar_clicked();


private:

    QVector<Confirmar_balanza*> vectorBalanzas;
    Ui::confirmar *ui;
};

#endif // CONFIRMAR_H
