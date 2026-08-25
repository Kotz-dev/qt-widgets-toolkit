//
// Created by KoTz on 23/07/2026.
//

#ifndef QTWIDGETSTOOLKIT_SPLITTER_H
#define QTWIDGETSTOOLKIT_SPLITTER_H

#include <QFrame>
#include <QString>
#include <QWidget>

namespace QtToolkit
{
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

#endif  // QTWIDGETSTOOLKIT_SPLITTER_H