//
// Created by KoTz on 23/07/2026.
//

#ifndef QTWIDGETSTOOLKIT_BLUR_H
#define QTWIDGETSTOOLKIT_BLUR_H

#include <QLabel>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

using BlurredLabel = QLabel;

namespace QtToolkit
{
namespace Blur
{

BlurredLabel * applyBlur(QWidget* target, qreal blurRadius = 3);
void removeBlur(BlurredLabel* blurred);
}  // namespace Blur
}  // namespace QtToolkit

#endif  // QTWIDGETSTOOLKIT_BLUR_H