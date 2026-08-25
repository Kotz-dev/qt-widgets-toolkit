//
// Created by KoTz on 23/07/2026.
//

#include "QtWidgetStoolkit/Blur.h"

#include <QGraphicsBlurEffect>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QLabel>
#include <QPainter>
#include <memory>

QLabel* QtToolkit::Blur::render(QWidget* parent, qreal blurRadius)
{
    if (parent == nullptr || blurRadius <= 0.0)
    {
        return nullptr;
    }

    QPixmap original = parent->grab();
    if (original.isNull())
    {
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

    if (blurred.isNull())
    {
        return nullptr;
    }

    QLabel* label = new QLabel(parent);
    label->setPixmap(blurred);
    label->setGeometry(parent->rect());
    label->show();
    label->raise();

    return label;
}