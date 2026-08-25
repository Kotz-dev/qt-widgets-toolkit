//
// Created by KoTz on 23/07/2026.
//

#ifndef QTWIDGETSTOOLKIT_BLUR_H
#define QTWIDGETSTOOLKIT_BLUR_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

namespace QtToolkit
{
namespace Blur
{
QLabel* render(QWidget* parent, qreal blurRadius = 3);
}  // namespace Blur
}  // namespace QtToolkit

#endif  // QTWIDGETSTOOLKIT_BLUR_H