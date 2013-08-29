#include "qesccompleter.h"

QEscCompleter::QEscCompleter(QObject *parent) :
    QCompleter(parent)
{
}

bool QEscCompleter::eventFilter(QObject *o, QEvent *e)
{
//    Q_D(QCompleter);
//    if (d->eatFocusOut && o == d->widget && e->type() == QEvent::FocusOut) {

//        d->hiddenBecauseNoMatch = false;

//        if (d->popup && d->popup->isVisible())

//            return true;

//    }


//    if (o != d->popup)

//        return QObject::eventFilter(o, e);


//    switch (e->type()) {

//    case QEvent::KeyPress: {

//        QKeyEvent *ke = static_cast<QKeyEvent *>(e);


//        QModelIndex curIndex = d->popup->currentIndex();

//        QModelIndexList selList = d->popup->selectionModel()->selectedIndexes();


//        const int key = ke->key();

//        // In UnFilteredPopup mode, select the current item

//        if ((key == Qt::Key_Up || key == Qt::Key_Down) && selList.isEmpty() && curIndex.isValid()

//                && d->mode == QCompleter::UnfilteredPopupCompletion) {

//            d->setCurrentIndex(curIndex);

//            return true;

//        }


//        // Handle popup navigation keys. These are hardcoded because up/down might make the

//        // widget do something else (lineedit cursor moves to home/end on mac, for instance)

//        switch (key) {

//        case Qt::Key_End:

//        case Qt::Key_Home:

//            if (ke->modifiers() & Qt::ControlModifier)

//                return false;

//            break;


//        case Qt::Key_Up:

//            if (!curIndex.isValid()) {

//                int rowCount = d->proxy->rowCount();

//                QModelIndex lastIndex = d->proxy->index(rowCount - 1, d->column);

//                d->setCurrentIndex(lastIndex);

//                return true;

//            } else if (curIndex.row() == 0) {

//                if (d->wrap)

//                    d->setCurrentIndex(QModelIndex());

//                return true;

//            }

//            return false;


//        case Qt::Key_Down:

//            if (!curIndex.isValid()) {

//                QModelIndex firstIndex = d->proxy->index(0, d->column);

//                d->setCurrentIndex(firstIndex);

//                return true;

//            } else if (curIndex.row() == d->proxy->rowCount() - 1) {

//                if (d->wrap)

//                    d->setCurrentIndex(QModelIndex());

//                return true;

//            }

//            return false;


//        case Qt::Key_PageUp:

//        case Qt::Key_PageDown:

//            return false;

//        }


//        // Send the event to the widget. If the widget accepted the event, do nothing

//        // If the widget did not accept the event, provide a default implementation

//        d->eatFocusOut = false;

//        (static_cast<QObject *>(d->widget))->event(ke);

//        d->eatFocusOut = true;

//        if (!d->widget || e->isAccepted() || !d->popup->isVisible()) {

//            // widget lost focus, hide the popup

//            if (d->widget && (!d->widget->hasFocus()

//                  #ifdef QT_KEYPAD_NAVIGATION

//                              || (QApplication::keypadNavigationEnabled() && !d->widget->hasEditFocus())

//                  #endif

//                              ))

//                d->popup->hide();

//            if (e->isAccepted())

//                return true;

//        }


//        // default implementation for keys not handled by the widget when popup is open

//        switch (key) {

//#ifdef QT_KEYPAD_NAVIGATION

//        case Qt::Key_Select:

//            if (!QApplication::keypadNavigationEnabled())

//                break;

//#endif

//        case Qt::Key_Return:

//        case Qt::Key_Enter:

//        case Qt::Key_Tab:

//            d->popup->hide(); //TODO change this so when I pressed this key the current index is -1

//            if (curIndex.isValid())

//                d->_q_complete(curIndex);

//            break;


//        case Qt::Key_F4:

//            if (ke->modifiers() & Qt::AltModifier)

//                d->popup->hide();

//            break;


//        case Qt::Key_Backtab:

//        case Qt::Key_Escape:

//            d->popup->hide();

//            break;


//        default:

//            break;

//        }


//        return true;


    }

