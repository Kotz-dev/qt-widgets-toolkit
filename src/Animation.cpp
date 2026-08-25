//
// Created by KoTz on 23/07/2026.
//

#include "QtWidgetStoolkit/Animation.h"

#include <QEasingCurve>
#include <QGraphicsOpacityEffect>
#include <QParallelAnimationGroup>
#include <QPropertyAnimation>

void QtToolkit::Animation::fadeSlideIn(QWidget* widget, int OpDuration, int posDuration)
{
    if (widget != nullptr)
    {
        QPoint endPos = widget->pos();
        widget->move(endPos.x(), endPos.y() + 20);

        auto* effect = new QGraphicsOpacityEffect(widget);
        widget->setGraphicsEffect(effect);

        QEasingCurve customCurve(QEasingCurve::BezierSpline);
        customCurve.addCubicBezierSegment(QPointF(0.34, -0.04), QPointF(0.49, 0.93), QPointF(1.0, 1.0));

        auto* fade = new QPropertyAnimation(effect, "opacity");
        fade->setDuration(OpDuration);
        fade->setStartValue(0.0);
        fade->setEndValue(1.0);
        fade->setEasingCurve(customCurve);

        auto* slide = new QPropertyAnimation(widget, "pos");
        slide->setDuration(posDuration);
        slide->setEndValue(endPos);
        slide->setEasingCurve(customCurve);

        auto* group = new QParallelAnimationGroup(widget);
        group->addAnimation(fade);
        group->addAnimation(slide);
        group->start(QAbstractAnimation::DeleteWhenStopped);
    }
}