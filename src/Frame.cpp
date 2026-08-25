//
// Created by KoTz on 23/07/2026.
//

#include "QtWidgetStoolkit/Frame.h"

bool QtToolkit::Frame::ClickHelper::m_enabled;

void QtToolkit::Frame::makeClickable(QFrame* frame, std::function<void()> onClick)
{
    if (frame == nullptr)
        return;

    frame->setCursor(Qt::PointingHandCursor);
    new ClickHelper(frame, onClick);
}