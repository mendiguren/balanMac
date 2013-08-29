#include "datetimedelegate.h"
#include <QDateTimeEdit>
#include <QDebug>

DateTimeDelegate::DateTimeDelegate(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QWidget *DateTimeDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    //qDebug() << "Type" << index.data().typeName();

    if (index.data().type() == QVariant::DateTime)
    {
        QDateTimeEdit *dTEditor = new QDateTimeEdit(parent);
        dTEditor->setCalendarPopup(true);

        return dTEditor;
    }
    else
        return QStyledItemDelegate::createEditor(parent, option, index);
}

void DateTimeDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.data().type() == QVariant::DateTime)
    {
        QDateTime dateTime = index.model()->data(index,Qt::EditRole).toDateTime();
        if(dateTime.isNull()){ dateTime = QDateTime::currentDateTime();}
        QDateTimeEdit *dTEditor = static_cast<QDateTimeEdit*>(editor);

        dTEditor->setDateTime(dateTime);
    }
    else
    {
        QStyledItemDelegate::setEditorData(editor,index);
    }
}

void DateTimeDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    if(index.data().type() == QVariant::DateTime)
    {
        QDateTimeEdit *dTEditor = static_cast<QDateTimeEdit*>(editor);
        dTEditor->interpretText();
        model->setData(index,dTEditor->dateTime(),Qt::EditRole);
    }
    else
    {
        QStyledItemDelegate::setModelData(editor,model,index);
    }
}

void DateTimeDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
