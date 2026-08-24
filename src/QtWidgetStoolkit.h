//
// Created by KoTz on 23/07/2026.
//

#ifndef KEEPCOLD_QTWIDGETSTOOLKIT_H
#define KEEPCOLD_QTWIDGETSTOOLKIT_H

#include <QEvent>
#include <QFrame>
#include <QGraphicsBlurEffect>
#include <QGraphicsOpacityEffect>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QLabel>
#include <QLayout>
#include <QMainWindow>
#include <QMouseEvent>
#include <QPainter>
#include <QParallelAnimationGroup>
#include <QProgressBar>
#include <QPropertyAnimation>
#include <QSizeGrip>
#include <QSplitter>
#include <QString>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QWidget>

namespace QtToolkit
{

namespace geometry
{
   QPoint centeredPosition(QWidget * parent, QWidget * child, int centerDivisor = 2);
}

namespace Animation
{
void fadeSlideIn(QWidget* widget);
}

namespace Window
{
class Maximizer : public QWidget
{
private:
    static bool m_isMaximized;
    static QRect m_normalGeometry;
    static QLabel* m_frameSnapshot;

public:
    void toggle(QWidget* widget, int msec = 500);
};

class Dragger : public QObject
{
    bool m_dragging = false;
    QPoint m_dragStartPosition;
    static QWidget* s_target;
    static Dragger* s_instance;

private:
    bool eventFilter(QObject* watched, QEvent* event) override;

public:
    static void attach(QWidget* widget);
};
}  // namespace Window

namespace Blur
{
QLabel* render(QWidget* parent, qreal blurRadius = 3);
}

namespace ProgessBar
{
class SegmentedProgressBar : public QProgressBar
{
    Q_OBJECT
    Q_PROPERTY(QColor animatedColor READ animatedColor WRITE setAnimatedColor)

public:
    explicit SegmentedProgressBar(QWidget* parent = nullptr);
    ~SegmentedProgressBar();
    void setSegments(int count);

    QColor animatedColor() const
    {
        return m_animatedColor;
    }

    void setAnimatedColor(const QColor& color);

    static void render(int value, QWidget* ProgressBar);

protected:
    void paintEvent(QPaintEvent* event) override;

private:
    int m_segments = 5;
    QColor m_animatedColor;
    QPropertyAnimation* m_colorAnimation;

    static SegmentedProgressBar* s_instance;

    QColor colorForLevel(int filledCount) const;
    void onValueChanged(int value);
};
}  // namespace ProgessBar

namespace Splitter
{
// Remove firstChild e secondChild do layout de parent e os recoloca lado a lado dentro de um
// QSplitter.
void setupSplitter(
    QWidget* parent,
    QWidget* firstChild,
    QWidget* secondChild,
    QFrame::Shape shape = QFrame::NoFrame,
    QString styleSheet = "");
}  // namespace Splitter

}  // namespace QtToolkit
#endif  // KEEPCOLD_QTWIDGETSTOOLKIT_H
