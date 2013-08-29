#ifndef BASEDEDATOS_H
#define BASEDEDATOS_H

#include <QWidget>
#include "complementos/qextendedtable.h"

namespace Ui {
class BaseDeDatos;
}

class BaseDeDatos : public QWidget
{
    Q_OBJECT
    
public:
    explicit BaseDeDatos(QWidget *parent = 0);
    ~BaseDeDatos();
    
private:
    Ui::BaseDeDatos *ui;

private slots:
    void cbTableChanged(int index);

public slots:
    void updateView();

};

#endif // BASEDEDATOS_H
