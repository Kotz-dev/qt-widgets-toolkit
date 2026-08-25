//
// Created by KoTz on 23/07/2026.
//

#ifndef QTWIDGETSTOOLKIT_PROGESSBAR_H
#define QTWIDGETSTOOLKIT_PROGESSBAR_H

#include <QProgressBar>

QT_BEGIN_NAMESPACE
class QPropertyAnimation;
QT_END_NAMESPACE

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
}  // namespace QtToolkit

#endif  // QTWIDGETSTOOLKIT_PROGESSBAR_H