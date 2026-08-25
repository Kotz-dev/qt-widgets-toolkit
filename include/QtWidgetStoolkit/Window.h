//
// Created by KoTz on 23/07/2026.
//

#ifndef QTWIDGETSTOOLKIT_WINDOW_H
#define QTWIDGETSTOOLKIT_WINDOW_H

#include <QObject>
#include <QPoint>
#include <QRect>
#include <QWidget>

QT_BEGIN_NAMESPACE
class QScreen;
QT_END_NAMESPACE

namespace QtToolkit
{
namespace Window
{

class Maximizer : public QWidget
{
private:
    static bool m_isMaximized;
    static QRect m_normalGeometry;

public:
    static QScreen* oldScreen;
    static QWidget* oldWidget;

    void toggle(QWidget* widget, int msec = 500);
    static void resync(QWidget* widget);
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
}  // namespace QtToolkit

#endif  // QTWIDGETSTOOLKIT_WINDOW_H