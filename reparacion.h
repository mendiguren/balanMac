#ifndef REPARACION_H
#define REPARACION_H

#include <QWidget>
#include <QSqlRecord>

namespace Ui {
class Reparacion;
}

class Reparacion : public QWidget
{
    Q_OBJECT
    
public:
    explicit Reparacion(QWidget *parent = 0);
    ~Reparacion();

    void initializeTransaccion(QSqlRecord rec);
    
private:
    Ui::Reparacion *ui;

private slots:

    void on_pbCancelar_clicked();
    void on_pbAceptar_clicked();
};

#endif // REPARACION_H
