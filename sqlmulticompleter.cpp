#include "sqlmulticompleter.h"
#include <QDebug>
#include <QSqlRecord>
#include <QListView>
#include <QAction>
#include <QTimer>
#include <QString>
#include <QSqlField>
#include <QSqlQuery>

SqlMultiCompleter::SqlMultiCompleter(QString tableName, QObject *parent) :
    QObject(parent) ,m_tableName(tableName)
{
    m_model = new QSqlTableModel(this);
    m_model->setTable(tableName);
    m_model->select();


    //populate the vectors
    m_widgets.resize(m_model->columnCount());
    for(int col = 0; col < m_model->columnCount(); col++)
    {
        QCompleter *com = new QCompleter(m_model,this);
        com->setCaseSensitivity(Qt::CaseInsensitive);
        com->setCompletionColumn(col);
        m_completers.append(com);
        connect(com,SIGNAL(highlighted(QModelIndex)),this,SLOT(onHighlighted(QModelIndex)));
        connect(com,SIGNAL(activated(QModelIndex)),this,SLOT(clearAllBackgrounds(QModelIndex)));
    }

}

void SqlMultiCompleter::attachColumn(QLineEdit *lineEdit, int column)
{
    lineEdit->setCompleter(m_completers.at(column));

    m_completers.at(column)->setObjectName("QLineEdit");
    m_widgets[column] = lineEdit;
    connect(lineEdit,SIGNAL(editingFinished()),this,SLOT(exitViewPort()));
}

void SqlMultiCompleter::attachColumn(QComboBox *comboBox, int column)
{
    comboBox->setCompleter(m_completers.at(column));
    m_completers.at(column)->setObjectName("QComboBox");
    m_widgets[column] = comboBox;

    //connect(comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(exitViewPort()));
}

void SqlMultiCompleter::onHighlighted(QModelIndex index)
{

    QCompleter *completer = static_cast<QCompleter*>(QObject::sender());

    qDebug() << "index = " << index;
    qDebug() << "this maps to" << completer->popup()->model()->data(index).toInt();

    QSqlQuery query;
    query.exec(QString("SELECT * FROM "+m_tableName+" WHERE "+m_model->headerData(0, Qt::Horizontal, Qt::DisplayRole).toString()+" = '%1';").arg(completer->popup()->model()->data(index).toInt()));

    query.next();

    qDebug() <<  query.record();
    QSqlRecord rec = query.record();

    QStringList row;
    for(int i = 0; i < rec.count() ; i++)
    {
        if(rec.value(i).toString() == "0")
        {
            row << "";
        }
        else row << rec.value(i).toString();
    }

    setAllText(row);

}

void SqlMultiCompleter::clearAllBackgrounds(QModelIndex)
{

    for(int nCompleter = 0; nCompleter < m_completers.size() ; nCompleter++)
    {
        if(m_completers.at(nCompleter)->objectName() == "QLineEdit")
        {
            QLineEdit* le = static_cast<QLineEdit*>(m_completers.at(nCompleter)->widget());
            if(le)
            {
                le->setStyleSheet("");
            }
        }
        else if(m_completers.at(nCompleter)->objectName() == "QComboBox")
        {
            QComboBox* cb = qobject_cast<QComboBox*>(m_widgets.at(nCompleter));
            qDebug() << "cb = " << cb;
            if(cb) //Check if is le is a null pointer
            {
                cb->setStyleSheet("");
            }
        }
    }
}

void SqlMultiCompleter::changeFilter()
{
    filter = "";
    for(int i = 0; i <  m_completers.size() ; i++)
    {
        QLineEdit* le = static_cast<QLineEdit*>(m_completers.at(i)->widget());
        if(le != NULL && !le->text().isEmpty())
        {
            QString header = m_model->headerData(m_completers.at(i)->completionColumn(), Qt::Horizontal, Qt::DisplayRole).toString();
            filter = filter +"( " + header + " LIKE \'" + le->text() + "%\' OR "+ header+" IS NULL ) AND ";
        }
    }
    filter.remove(filter.size()-4,filter.size());
     m_model->setFilter(filter);
     m_model->select();

}

void SqlMultiCompleter::exitViewPort()
{
    clearAllBackgrounds(QModelIndex());
    changeFilter();


}
void SqlMultiCompleter::setAllText(QStringList values)
{
    for(int nCompleter = 0; nCompleter < m_completers.size() ; ++nCompleter)
    {
        if(m_completers.at(nCompleter)->objectName() == "QLineEdit")
        {
            QLineEdit* le = qobject_cast<QLineEdit*>(m_completers.at(nCompleter)->widget());
            if(le) //Check if is le is a null pointer
            {
                if(le->text().isEmpty() || le->styleSheet() == "QLineEdit{background: CornflowerBlue;}")
                {
                    le->setText(values.at(nCompleter));
                    if(values.at(nCompleter) == "")
                    {
                        le->setStyleSheet("");
                    }
                    else
                    {
                        le->setStyleSheet("QLineEdit{background: CornflowerBlue;}");
                    }

                }
            }
        }
        else if(m_completers.at(nCompleter)->objectName() == "QComboBox")
        {
            QComboBox* cb = qobject_cast<QComboBox*>(m_widgets.at(nCompleter));
            if(cb) //Check if is le is a null pointer
            {
                if(cb->currentIndex()==-1 || cb->styleSheet() == "QComboBox{background: CornflowerBlue;}")
                {
                    qDebug() << "Find " << cb->findText(values.at(nCompleter));
                    cb->setCurrentIndex(cb->findText(values.at(nCompleter)));
                    if(values.at(nCompleter) == "")
                    {
                        cb->setStyleSheet("");
                    }
                    else
                    {
                        cb->setStyleSheet("QComboBox{background: CornflowerBlue;}");
                    }

                }
            }
        }
    }
}
