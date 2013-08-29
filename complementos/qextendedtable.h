#ifndef QEXTENDEDTABLE_H
#define QEXTENDEDTABLE_H

#include <QWidget>
#include <QTableView>
#include <QSqlTableModel>
#include <QSortFilterProxyModel>
#include "complementos/wwWidgets/widgets/qwwclearlineedit/QwwClearLineEdit"
#include <QPrinter>
#include "complementos/QSpreadsheetHeaderView.h"
#include <QAbstractItemDelegate>

namespace Ui {
class QExtendedTable;
}

class QExtendedTable : public QWidget
{
    Q_OBJECT
    
public:
    explicit QExtendedTable(QWidget *parent = 0);
    ~QExtendedTable();

    void setTable(QString tableName);
    void showComboBox(bool show);
    void submit();
    void setColumnDelegate(int column, QAbstractItemDelegate *delegate);
    QSqlTableModel* getModel();
    QTableView *getTableView();

private slots:
    void on_pushButton_clicked();
    void clearSearch();
    void checkClear(QString text);




public slots:
    void ShowContextMenu(const QPoint& pos);
    void updateTable();

private:
    Ui::QExtendedTable *ui;
    QSqlTableModel *model;
    QSortFilterProxyModel *proxy;
    QPrinter *printer;
    QSpreadsheetHeaderView *header;


signals:
    void rowShowContextMenu(QPoint menuPos);


};

#endif // QEXTENDEDTABLE_H
