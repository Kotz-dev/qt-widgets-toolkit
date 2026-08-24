//
// Created by KoTz on 23/07/2026.
//

#include "QtWidgetStoolkit.h"


QtToolkit::ProgessBar::SegmentedProgressBar *QtToolkit::ProgessBar::SegmentedProgressBar::s_instance = nullptr;
QWidget *QtToolkit::Window::Dragger::s_target = nullptr;
QtToolkit::Window::Dragger *QtToolkit::Window::Dragger::s_instance = nullptr;
bool QtToolkit::Window::Maximizer::m_isMaximized = false;
QRect QtToolkit::Window::Maximizer::m_normalGeometry;
QLabel *QtToolkit::Window::Maximizer::m_frameSnapshot = nullptr;


bool QtToolkit::Window::Dragger::eventFilter(QObject* watched, QEvent* event)
{
    if (s_target != nullptr)
    {
        if (watched == s_target) {
            if (event->type() == QEvent::MouseButtonPress) {
                auto *mouseEvent = static_cast<QMouseEvent*>(event);
                if (mouseEvent->button() == Qt::LeftButton) {
                    m_dragging = true;
                    m_dragStartPosition = mouseEvent->globalPosition().toPoint() - s_target->frameGeometry().topLeft();
                    return true;
                }
            }
            else if (event->type() == QEvent::MouseMove) {
                auto *mouseEvent = static_cast<QMouseEvent*>(event);
                if (m_dragging && (mouseEvent->buttons() & Qt::LeftButton)) {
                    s_target->move(mouseEvent->globalPosition().toPoint() - m_dragStartPosition);
                    return true;
                }
            }
            else if (event->type() == QEvent::MouseButtonRelease) {
                m_dragging = false;
                return true;
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

QLabel *QtToolkit::Blur::render(QWidget* parent,qreal blurRadius)
{
    if (parent == nullptr || blurRadius <= 0.0) {
        return nullptr;
    }

    QPixmap original = parent->grab();
    if (original.isNull()) {
        return nullptr;
    }

    QGraphicsScene scene;
    QGraphicsPixmapItem item(original);

    std::unique_ptr<QGraphicsBlurEffect> blur = std::make_unique<QGraphicsBlurEffect>();
    blur->setBlurRadius(blurRadius);
    item.setGraphicsEffect(blur.release());

    scene.addItem(&item);

    QPixmap blurred(original.size());
    blurred.fill(Qt::transparent);

    QPainter painter(&blurred);
    scene.render(
        &painter,
        QRectF(0, 0, blurred.width(), blurred.height()),
        QRectF(0, 0, original.width(), original.height()));
    painter.end();

    if (blurred.isNull()) {
        return nullptr;
    }

       QLabel *label = new QLabel(parent);
        label->setPixmap(blurred);
        label->setGeometry(parent->rect());
        label->show();
        label->raise();

    return label;
}

void QtToolkit::Window::Maximizer::toggle(QWidget* widget,int msec)
{
    if (widget != nullptr)
    {
        auto *anim = new QPropertyAnimation(widget, "geometry");
        anim->setDuration(msec);
        anim->setEasingCurve(QEasingCurve::OutCubic);

        if (!m_isMaximized) {
            m_normalGeometry = widget->geometry();
            QRect screenGeometry = this->screen()->availableGeometry();
            anim->setStartValue(widget->geometry());
            anim->setEndValue(screenGeometry);
            m_isMaximized = true;
        } else {
            anim->setStartValue(widget->geometry());
            anim->setEndValue(m_normalGeometry);
            m_isMaximized = false;
        }
        anim->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

QtToolkit::ProgessBar::SegmentedProgressBar::SegmentedProgressBar(QWidget *parent)
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


void QtToolkit::ProgessBar::SegmentedProgressBar::setSegments(int count) {
    m_segments = count;
    update();
}

void QtToolkit::ProgessBar::SegmentedProgressBar::setAnimatedColor(const QColor &color) {
    if (m_animatedColor == color) {
        return;
    }
    m_animatedColor = color;
    update();
}

void QtToolkit::ProgessBar::SegmentedProgressBar::onValueChanged(int value) {
    Q_UNUSED(value);

    int filledCount = m_segments > 0
        ? (this->value() * m_segments) / qMax(1, maximum())
        : 0;

    QColor target = colorForLevel(filledCount);
    if (target == m_animatedColor) {
        return;
    }

    m_colorAnimation->stop();
    m_colorAnimation->setStartValue(m_animatedColor);
    m_colorAnimation->setEndValue(target);
    m_colorAnimation->start();
}

QColor QtToolkit::ProgessBar::SegmentedProgressBar::colorForLevel(int filledCount) const {
    switch (filledCount) {
        case 0: return QColor("#3a4368");
        case 1: return QColor("#ef4444");
        case 2: return QColor("#f97316");
        case 3: return QColor("#3b82f6");
        case 4: return QColor("#22c55e");
        case 5: return QColor("#22c55e");
        default: return QColor("#22c55e");
    }
}

void QtToolkit::ProgessBar::SegmentedProgressBar::paintEvent(QPaintEvent *event) {
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    int spacing = 4;
    int totalSpacing = spacing * (m_segments - 1);
    int segmentWidth = (width() - totalSpacing) / m_segments;

    int filledCount = m_segments > 0
        ? (value() * m_segments) / qMax(1, maximum())
        : 0;

    for (int i = 0; i < m_segments; i++) {
        int x = i * (segmentWidth + spacing);
        QRect rect(x, 0, segmentWidth, height());

        QColor color = (i < filledCount) ? m_animatedColor : QColor("#3a4368");

        painter.setBrush(color);
        painter.setPen(Qt::NoPen);
        painter.drawRoundedRect(rect, 2, 2);
    }
}

void QtToolkit::Splitter::setupSplitter(
        QWidget* parent,
        QWidget* firstChild,
        QWidget* secondChild,
        QFrame::Shape shape,
        QString styleSheet)
{
    if (parent != nullptr && firstChild != nullptr && secondChild != nullptr)
    {
        QLayout *mainLayout = parent->layout();

        mainLayout->removeWidget(firstChild);
        mainLayout->removeWidget(secondChild);

        QSplitter *splitter = new QSplitter(Qt::Horizontal, parent);
        splitter->addWidget(firstChild);
        splitter->addWidget(secondChild);
        splitter->setHandleWidth(4);
        splitter->setStretchFactor(0, 1);
        splitter->setStretchFactor(1, 3);

        mainLayout->addWidget(splitter);

        if (styleSheet.isEmpty() == false)
        {
            splitter->setStyleSheet(styleSheet);
        }
        splitter->setFrameShape(QFrame::NoFrame);
    }

}

void QtToolkit::Animation::fadeSlideIn(QWidget* widget) {

    if (widget != nullptr)
    {
        QPoint endPos = widget->pos();
        widget->move(endPos.x(), endPos.y() + 20);

        auto *effect = new QGraphicsOpacityEffect(widget);
        widget->setGraphicsEffect(effect);

        QEasingCurve customCurve(QEasingCurve::BezierSpline);
        customCurve.addCubicBezierSegment(
            QPointF(0.34, -0.04),
            QPointF(0.49, 0.93),
            QPointF(1.0, 1.0)
        );
        auto *fade = new QPropertyAnimation(effect, "opacity");
        fade->setDuration(750);
        fade->setStartValue(0.0);
        fade->setEndValue(1.0);
        fade->setEasingCurve(customCurve);

        auto *slide = new QPropertyAnimation(widget, "pos");
        slide->setDuration(740);
        slide->setEndValue(endPos);
        slide->setEasingCurve(customCurve);

        auto *group = new QParallelAnimationGroup(widget);
        group->addAnimation(fade);
        group->addAnimation(slide);
        group->start(QAbstractAnimation::DeleteWhenStopped);
    }
}

QPoint QtToolkit::geometry::centeredPosition(QWidget * parent, QWidget * child, int centerDivisor)
{
    if (parent != nullptr && child != nullptr)
    {
       return  parent->geometry().center() -
            QPoint(child->width() / centerDivisor,  child->height() / centerDivisor);
    }
    return QPoint();
}