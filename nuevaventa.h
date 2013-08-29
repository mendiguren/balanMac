#ifndef NUEVAVENTA_H
#define NUEVAVENTA_H

#include <QWidget>

namespace Ui {
class NuevaVenta;
}

class NuevaVenta : public QWidget
{
    Q_OBJECT
    
public:
    explicit NuevaVenta(QWidget *parent = 0);
    ~NuevaVenta();
    
private:
    Ui::NuevaVenta *ui;
};

#endif // NUEVAVENTA_H
