#include "nonscrollablecombobox.h"
#include <QWheelEvent>
#include <QDebug>

NonScrollableComboBox::NonScrollableComboBox(QWidget *parent) :
    QComboBox(parent)
{
    installEventFilter(this);
}

bool NonScrollableComboBox::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::Wheel)
        {
            qDebug() << "Wheel event blocked";
            return true;
        }
        return false;
}
