#include "QtWidgetStoolkit/Geometry.h"

QPoint QtToolkit::geometry::centeredPosition(QWidget* parent, QWidget* child, int centerDivisor)
{
    if (parent != nullptr && child != nullptr)
    {
        return parent->geometry().center() -
            QPoint(child->width() / centerDivisor, child->height() / centerDivisor);
    }
    return QPoint();
}
