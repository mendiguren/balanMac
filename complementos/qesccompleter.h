#ifndef QESCCOMPLETER_H
#define QESCCOMPLETER_H

#include <QCompleter>
#include <QEvent>


class QEscCompleter : public QCompleter
{
    Q_OBJECT
public:
    explicit QEscCompleter(QObject *parent = 0);
    
signals:
    
public slots:

protected:
    bool eventFilter(QObject *o, QEvent *e);

    
};

#endif // QESCCOMPLETER_H
