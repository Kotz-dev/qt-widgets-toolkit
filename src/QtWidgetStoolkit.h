//
// Created by KoTz on 23/07/2026.
//

#ifndef KEEPCOLD_QTWIDGETSTOOLKIT_H
#define KEEPCOLD_QTWIDGETSTOOLKIT_H

#include <QFrame>
#include <QLayout>
#include <QProgressBar>
#include <QPropertyAnimation>
#include <QSplitter>
#include <QString>
#include <QWidget>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

namespace QtToolkitAnimation
{
    void animateIn(QWidget *widget);
}


namespace QtToolkit
{
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
void setupSplitter(
    QWidget* pai,
    QWidget* irmao_1,
    QWidget* irmao_2,
    QFrame::Shape shape = QFrame::NoFrame,
    QString StyleSheets = "");
}
}  // namespace QtToolkit
#endif  // KEEPCOLD_QTWIDGETSTOOLKIT_H
