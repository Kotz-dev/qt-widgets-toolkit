//
// Created by KoTz on 23/07/2026.
//

#include "QtWidgetStoolkit/Splitter.h"

#include <QLayout>
#include <QSplitter>

void QtToolkit::Splitter::setupSplitter(
    QWidget* parent,
    QWidget* firstChild,
    QWidget* secondChild,
    QFrame::Shape shape,
    QString styleSheet)
{
    if (parent != nullptr && firstChild != nullptr && secondChild != nullptr)
    {
        QLayout* mainLayout = parent->layout();

        mainLayout->removeWidget(firstChild);
        mainLayout->removeWidget(secondChild);

        QSplitter* splitter = new QSplitter(Qt::Horizontal, parent);
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