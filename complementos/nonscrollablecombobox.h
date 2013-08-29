#ifndef NONSCROLLABLECOMBOBOX_H
#define NONSCROLLABLECOMBOBOX_H

#include <QComboBox>

class NonScrollableComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit NonScrollableComboBox(QWidget *parent = 0);
    bool eventFilter(QObject *obj, QEvent *event);

    
signals:
    
public slots:

private:
    
};

#endif // NONSCROLLABLECOMBOBOX_H
