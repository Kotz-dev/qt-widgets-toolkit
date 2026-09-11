//
// Created by KoTz on 23/07/2026.
//

#ifndef QTWIDGETSTOOLKIT_FRAME_H
#define QTWIDGETSTOOLKIT_FRAME_H

#include <QEvent>
#include <QFrame>
#include <QObject>
#include <functional>

namespace QtToolkit
{
namespace Frame
{

class ClickHelper : public QObject
{
public:
    ClickHelper(QFrame* target, std::function<void()> callback)
        : QObject(target), m_callback(callback)
    {
        target->installEventFilter(this);
        m_enabled = true;
    }

    static void setEnabled(bool enable)
    {
        m_enabled = enable;
    }

protected:
    bool eventFilter(QObject* watched, QEvent* event) override
    {
        if (!m_enabled)
            return false;

        if (event->type() == QEvent::MouseButtonPress)
        {
            if (m_callback)
                m_callback();
            return true;
        }
        return QObject::eventFilter(watched, event);
    }

private:
    static bool m_enabled;
    std::function<void()> m_callback;
};

void makeClickable(QFrame* frame, std::function<void()> onClick);

}  // namespace Frame
}  // namespace QtToolkit

#endif  // QTWIDGETSTOOLKIT_FRAME_H