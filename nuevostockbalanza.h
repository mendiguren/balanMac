#ifndef NUEVOSTOCKBALANZA_H
#define NUEVOSTOCKBALANZA_H

#include <QWidget>

namespace Ui {
class NuevoStockBalanza;
}

class NuevoStockBalanza : public QWidget
{
    Q_OBJECT
    
public:
    explicit NuevoStockBalanza(QWidget *parent = 0);
    ~NuevoStockBalanza();
    
private:
    Ui::NuevoStockBalanza *ui;
};

#endif // NUEVOSTOCKBALANZA_H
