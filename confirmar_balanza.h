#ifndef CONFIRMAR_BALANZA_H
#define CONFIRMAR_BALANZA_H

#include <QWidget>

namespace Ui {
class Confirmar_balanza;
}

class Confirmar_balanza : public QWidget
{
    Q_OBJECT
    
public:
    explicit Confirmar_balanza(QWidget *parent = 0);
    ~Confirmar_balanza();
    
    void setBalanza(int idtransaccion);//TODO modify this so it takes idbalanza and extracts idcliente from idtransaccion
    bool checkCompletness();
    void commit();

private slots:
    void setRedBackground();

private:
    Ui::Confirmar_balanza *ui;
};

#endif // CONFIRMAR_BALANZA_H
