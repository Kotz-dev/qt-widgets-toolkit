//
// Created by KoTz on 23/07/2026.
//

#ifndef QTWIDGETSTOOLKIT_SIGNAL_H
#define QTWIDGETSTOOLKIT_SIGNAL_H

#include <QObject>

namespace QtToolkit
{
namespace Signal
{

template <typename T>
T* getObjet(QObject* get = QObject::sender())
{
    if (get != nullptr)
        return qobject_cast<T*>(get);
}

}  // namespace Signal
}  // namespace QtToolkit

#endif  // QTWIDGETSTOOLKIT_SIGNAL_H