//
// Created by KoTz on 24/08/2026.
//

#ifndef QTWIDGETSTOOLKIT_GEOMETRY_H
#define QTWIDGETSTOOLKIT_GEOMETRY_H

#include <QPoint>
#include <QWidget>

namespace QtToolkit
{
namespace geometry
{

QPoint centeredPosition(QWidget* parent, QWidget* child, int centerDivisor = 2);

}  // namespace geometry
}  // namespace QtToolkit

#endif  // QTWIDGETSTOOLKIT_GEOMETRY_H
