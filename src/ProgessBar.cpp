//
// Created by KoTz on 23/07/2026.
//

#include "QtWidgetStoolkit/ProgessBar.h"

#include <QEasingCurve>
#include <QLayout>
#include <QPainter>
#include <QPropertyAnimation>
#include <QVBoxLayout>

QtToolkit::ProgessBar::SegmentedProgressBar* QtToolkit::ProgessBar::SegmentedProgressBar::s_instance = nullptr;

QtToolkit::ProgessBar::SegmentedProgressBar::SegmentedProgressBar(QWidget* parent)
    : QProgressBar(parent)
{
    m_animatedColor = colorForLevel(0);

    m_colorAnimation = new QPropertyAnimation(this, "animatedColor", this);
    m_colorAnimation->setDuration(700);
    m_colorAnimation->setEasingCurve(QEasingCurve::InCurve);

    connect(this, &QProgressBar::valueChanged, this, &SegmentedProgressBar::onValueChanged);
}

QtToolkit::ProgessBar::SegmentedProgressBar::~SegmentedProgressBar()
{
    if (s_instance == this)
    {
        s_instance = nullptr;
    }
}

void QtToolkit::ProgessBar::SegmentedProgressBar::render(int value, QWidget* ProgressBar)
{
    if (ProgressBar != nullptr)
    {
        if (s_instance == nullptr)
        {
            s_instance = new SegmentedProgressBar(ProgressBar);
        }
        s_instance->setSegments(5);
        s_instance->setRange(0, 5);
        s_instance->setTextVisible(false);
        s_instance->setValue(value);
        s_instance->setFixedHeight(7);
        QLayout* existingLayout = ProgressBar->layout();
        if (existingLayout == nullptr)
        {
            existingLayout = new QVBoxLayout(ProgressBar);
            existingLayout->setContentsMargins(0, 0, 0, 0);
        }
        existingLayout->addWidget(s_instance);
    }
}

void QtToolkit::ProgessBar::SegmentedProgressBar::setSegments(int count)
{
    m_segments = count;
    update();
}

void QtToolkit::ProgessBar::SegmentedProgressBar::setAnimatedColor(const QColor& color)
{
    if (m_animatedColor == color)
    {
        return;
    }
    m_animatedColor = color;
    update();
}

void QtToolkit::ProgessBar::SegmentedProgressBar::onValueChanged(int value)
{
    Q_UNUSED(value);

    int filledCount = m_segments > 0 ? (this->value() * m_segments) / qMax(1, maximum()) : 0;

    QColor target = colorForLevel(filledCount);
    if (target == m_animatedColor)
    {
        return;
    }

    m_colorAnimation->stop();
    m_colorAnimation->setStartValue(m_animatedColor);
    m_colorAnimation->setEndValue(target);
    m_colorAnimation->start();
}

QColor QtToolkit::ProgessBar::SegmentedProgressBar::colorForLevel(int filledCount) const
{
    switch (filledCount)
    {
        case 0: return QColor("#3a4368");
        case 1: return QColor("#ef4444");
        case 2: return QColor("#f97316");
        case 3: return QColor("#3b82f6");
        case 4: return QColor("#22c55e");
        case 5: return QColor("#22c55e");
        default: return QColor("#22c55e");
    }
}

void QtToolkit::ProgessBar::SegmentedProgressBar::paintEvent(QPaintEvent* event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int spacing = 4;
    int totalSpacing = spacing * (m_segments - 1);
    int segmentWidth = (width() - totalSpacing) / m_segments;

    int filledCount = m_segments > 0 ? (value() * m_segments) / qMax(1, maximum()) : 0;

    for (int i = 0; i < m_segments; i++)
    {
        int x = i * (segmentWidth + spacing);
        QRect rect(x, 0, segmentWidth, height());

        QColor color = (i < filledCount) ? m_animatedColor : QColor("#3a4368");

        painter.setBrush(color);
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(rect, 2, 2);
    }
}