#include "combodelegate.h"
#include <QComboBox>

ComboDelegate::ComboDelegate(QObject *parent,QStringList comboValues) :
    QStyledItemDelegate(parent), texts(comboValues)
{
}

QWidget *ComboDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QComboBox *cbEditor = new QComboBox(parent);
    cbEditor->addItems(texts);
    return cbEditor;
}

void ComboDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
   QString data = index.model()->data(index,Qt::EditRole).toString();
   int currentIndex = texts.indexOf(data);

   QComboBox *cbEditor = static_cast<QComboBox*>(editor);

   cbEditor->setCurrentIndex(currentIndex);
}

void ComboDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QComboBox *cbEditor = static_cast<QComboBox*>(editor);
    model->setData(index,cbEditor->currentText(),Qt::EditRole);
}

void ComboDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
