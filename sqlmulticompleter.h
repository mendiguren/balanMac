#ifndef SQLMULTICOMPLETER_H
#define SQLMULTICOMPLETER_H

#include <QObject>
#include <QSqlTableModel>
#include <QCompleter>
#include <QLineEdit>
#include <QModelIndex>
#include <QStringList>
#include <QComboBox>
#include <QPlainTextEdit>

class SqlMultiCompleter : public QObject
{
    Q_OBJECT
public:
    explicit SqlMultiCompleter(QString tableName,QObject *parent = 0);
    void attachColumn(QLineEdit* lineEdit,int column);
    void attachColumn(QComboBox* comboBox,int column);

    QSqlTableModel *m_model; //So it can be reflesh when user submit new data



signals:
    void setText(QString text);
public slots:
    void onHighlighted(QModelIndex index);
    void clearAllBackgrounds(QModelIndex);
    void changeFilter();
    void exitViewPort();

private:
    QString m_tableName;
    QVector<QCompleter*> m_completers;
    QVector<QWidget*> m_widgets;
    void setAllText(QStringList values);
    QString filter;




};

#endif // SQLMULTICOMPLETER_H
