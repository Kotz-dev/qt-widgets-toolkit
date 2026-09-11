//
// Created by KoTz on 23/07/2026.
//

#include "QtWidgetStoolkit/Window.h"

#include <QEasingCurve>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QScreen>

QWidget* QtToolkit::Window::Dragger::s_target = nullptr;
QtToolkit::Window::Dragger* QtToolkit::Window::Dragger::s_instance = nullptr;
bool QtToolkit::Window::Maximizer::m_isMaximized = false;
QRect QtToolkit::Window::Maximizer::m_normalGeometry;
QWidget* QtToolkit::Window::Maximizer::oldWidget;
QScreen* QtToolkit::Window::Maximizer::oldScreen;

bool QtToolkit::Window::Dragger::eventFilter(QObject* watched, QEvent* event)
{
    if (s_target != nullptr)
    {
        if (watched == s_target)
        {
            if (event->type() == QEvent::MouseButtonPress)
            {
                auto* mouseEvent = static_cast<QMouseEvent*>(event);
                if (mouseEvent->button() == Qt::LeftButton)
                {
                    m_dragging = true;
                    m_dragStartPosition = mouseEvent->globalPosition().toPoint() - s_target->frameGeometry().topLeft();
                    return true;
                }
            }
            else if (event->type() == QEvent::MouseMove)
            {
                auto* mouseEvent = static_cast<QMouseEvent*>(event);
                if (m_dragging && (mouseEvent->buttons() & Qt::LeftButton))
                {
                    s_target->move(mouseEvent->globalPosition().toPoint() - m_dragStartPosition);
                    return true;
                }
            }
            else if (event->type() == QEvent::MouseButtonRelease)
            {
                m_dragging = false;
                return true;
            }
            else if (event->type() == QEvent::WindowStateChange)
            {
                if (!(s_target->windowState() & Qt::WindowMinimized))
                {
                    Maximizer::resync(s_target);
                }
            }
        }

        return QObject::eventFilter(watched, event);
    }
    return false;
}

void QtToolkit::Window::Dragger::attach(QWidget* widget)
{
    if (widget != nullptr)
    {
        s_target = widget;
        if (s_instance == nullptr)
        {
            s_instance = new Dragger();
        }
        widget->installEventFilter(s_instance);
    }
}

void QtToolkit::Window::Maximizer::toggle(QWidget* widget, int msec)
{
    if (widget != nullptr && msec > 0)
    {
        auto* anim = new QPropertyAnimation(widget, "geometry");
        anim->setDuration(msec);
        anim->setEasingCurve(QEasingCurve::OutCubic);
        if (!m_isMaximized)
        {
            m_normalGeometry = widget->geometry();
            QRect screenGeometry = widget->screen()->availableGeometry();
            anim->setStartValue(widget->geometry());
            anim->setEndValue(screenGeometry);
            m_isMaximized = true;
        }
        else
        {
            anim->setStartValue(widget->geometry());
            anim->setEndValue(m_normalGeometry);
            m_isMaximized = false;
        }

        anim->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

void QtToolkit::Window::Maximizer::resync(QWidget* widget)
{
    if (widget == nullptr || widget->screen() == nullptr)
    {
        return;
    }

    m_isMaximized = (widget->geometry() == widget->screen()->availableGeometry());
}