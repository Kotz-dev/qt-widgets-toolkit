//
// Created by KoTz on 13/11/2026.
//

#include "QtWidgetStoolkit/Badge.h"

namespace
{

constexpr int kBadgeSize = 20;
constexpr int kBadgeWideSize = 28;
constexpr int kBadgeMargin = 2;

using QtToolkit::Badge::Position;

// Calcula a posição do badge dentro do pai conforme a property "badgePosition".
void reposition(QLabel* badge)
{
    QWidget* parent = badge->parentWidget();
    if (parent == nullptr)
        return;

    const auto position = static_cast<Position>(badge->property("badgePosition").toInt());

    const int left = kBadgeMargin;
    const int right = parent->width() - badge->width() - kBadgeMargin;
    const int centerX = (parent->width() - badge->width()) / 2;
    const int top = kBadgeMargin;
    const int bottom = parent->height() - badge->height() - kBadgeMargin;
    const int centerY = (parent->height() - badge->height()) / 2;

    int x = centerX;
    int y = centerY;

    switch (position)
    {
        case QtToolkit::Badge::TOP_LEFT:     x = left;    y = top;     break;
        case QtToolkit::Badge::TOP:          x = centerX; y = top;     break;
        case QtToolkit::Badge::TOP_RIGHT:    x = right;   y = top;     break;
        case QtToolkit::Badge::LEFT:         x = left;    y = centerY; break;
        case QtToolkit::Badge::CENTER:       x = centerX; y = centerY; break;
        case QtToolkit::Badge::RIGHT:        x = right;   y = centerY; break;
        case QtToolkit::Badge::BOTTOM_LEFT:  x = left;    y = bottom;  break;
        case QtToolkit::Badge::BOTTOM:       x = centerX; y = bottom;  break;
        case QtToolkit::Badge::BOTTOM_RIGHT: x = right;   y = bottom;  break;
    }

    badge->move(x, y);
    badge->raise();
}

// Reposiciona o badge sempre que o botão for redimensionado ou mostrado.
// Filho do badge, então é destruído junto com ele.
class BadgeFilter : public QObject
{
public:
    explicit BadgeFilter(QLabel* badge) : QObject(badge), badge_(badge) {}

protected:
    bool eventFilter(QObject* watched, QEvent* event) override
    {
        if (event->type() == QEvent::Resize || event->type() == QEvent::Show)
            reposition(badge_);
        return QObject::eventFilter(watched, event);
    }

private:
    QLabel* badge_;
};

}  // namespace

QString normalizeHexColor(const QString & get);

QString normalizeHexColor(const QString& get) {
    QString str = get.trimmed();
    if (!str.startsWith('#'))
        str.prepend('#');
    return str;
}


QLabel *QtToolkit::Badge::attach(QPushButton *button, int count,
                                 BADGE_PRODPY OBJ = BADGE_PRODPY{}) {
    if (button == nullptr)
        return nullptr;


    QLabel* badge = new QLabel(button);
    badge->setFixedSize(kBadgeSize, kBadgeSize);
    badge->setAlignment(Qt::AlignCenter);
    badge->setStyleSheet
    (
        "background-color: " + normalizeHexColor(OBJ.BACKGROUND_COLOR)+ ";"
        "color:            " + normalizeHexColor(OBJ.COLOR_TEXT_BADGE) + ";"
        "font-weight:      " + OBJ.FONTE_WEIGHT + ";"
        "font-size:        " + QString::number(OBJ.FONT_SIZE) + "px;"
        "border-radius:    " + OBJ.BORDER_RADIUS + ";"
        );
    badge->setAttribute(Qt::WA_TransparentForMouseEvents);
    badge->setProperty("badgePosition", static_cast<int>(OBJ.BADGE_POSITION));

    button->installEventFilter(new BadgeFilter(badge));

    setCount(badge, count);
    return badge;
}



QLabel * QtToolkit::Badge::attach(QPushButton* button, int count, const QString COLOR_BACKGROUND,
const QString COLOR_TEXT_BADGE, Position BADGE_POSITION, QString FONT_WEIGHT,
int FONT_SIZE, QString BORDER_RADIUS)
{
    if (button == nullptr)
        return nullptr;

    QString BG_COLOR_BACKGROUND  = normalizeHexColor(COLOR_BACKGROUND);
    QString BG_COLOR_TEXT_BADGE  = normalizeHexColor(COLOR_TEXT_BADGE);

    QLabel* badge = new QLabel(button);
    badge->setFixedSize(kBadgeSize, kBadgeSize);
    badge->setAlignment(Qt::AlignCenter);
    badge->setStyleSheet(
        "background-color: " + BG_COLOR_BACKGROUND + ";"
        "color:            " + BG_COLOR_TEXT_BADGE + ";"
        "font-weight:      " + FONT_WEIGHT + ";"
        "font-size:        " + QString::number(FONT_SIZE) + "px;"
        "border-radius:    " + BORDER_RADIUS + ";");
    badge->setAttribute(Qt::WA_TransparentForMouseEvents);
    badge->setProperty("badgePosition", static_cast<int>(BADGE_POSITION));

    button->installEventFilter(new BadgeFilter(badge));

    setCount(badge, count);
    return badge;
}

void QtToolkit::Badge::setCount(QLabel* badge, int count)
{
    if (badge == nullptr)
        return;

    if (count <= 0)
    {
        badge->hide();
        return;
    }

    const bool overflow = count > 99;
    badge->setText(overflow ? QStringLiteral("99+") : QString::number(count));
    badge->setFixedWidth(overflow ? kBadgeWideSize : kBadgeSize);

    reposition(badge);

    badge->show();
}
