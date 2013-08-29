#ifndef NUEVOSTOCKREPUESTOS_H
#define NUEVOSTOCKREPUESTOS_H

#include <QWidget>

namespace Ui {
class NuevoStockRepuestos;
}

class NuevoStockRepuestos : public QWidget
{
    Q_OBJECT
    
public:
    explicit NuevoStockRepuestos(QWidget *parent = 0);
    ~NuevoStockRepuestos();
    
private:
    Ui::NuevoStockRepuestos *ui;
};

#endif // NUEVOSTOCKREPUESTOS_H
