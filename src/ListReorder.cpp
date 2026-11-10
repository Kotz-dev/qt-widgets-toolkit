//
// Created by KoTz on 10/11/2026.
//

#include "QtWidgetStoolkit/ListReorder.h"

#include <QAbstractItemView>
#include <QModelIndex>

QtToolkit::ListReorder::Reorderer::Reorderer(QObject* parent) : QObject(parent)
{
}

QtToolkit::ListReorder::Reorderer* QtToolkit::ListReorder::Reorderer::attach(QListWidget* listView)
{
    if (listView == nullptr)
    {
        return nullptr;
    }

    listView->setDragDropMode(QAbstractItemView::InternalMove);
    listView->setDefaultDropAction(Qt::MoveAction);

    Reorderer* reorderer = new Reorderer(listView);

    if (reorderer != nullptr)
    QObject::connect(
            listView->model(),
            &QAbstractItemModel::rowsMoved,
            reorderer,
            [reorderer](const QModelIndex&, int start, int, const QModelIndex&, int destRow)
            {
                int toIndex = destRow > start ? destRow - 1 : destRow;
                emit reorderer->itemMoved(start, toIndex);
            });

    return reorderer;
}
