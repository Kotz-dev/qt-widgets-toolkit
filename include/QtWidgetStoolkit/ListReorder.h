//
// Created by KoTz on 10/11/2026.
//

#ifndef QTWIDGETSTOOLKIT_LISTREORDER_H
#define QTWIDGETSTOOLKIT_LISTREORDER_H

#include <QListWidget>
#include <QObject>

namespace QtToolkit
{
namespace ListReorder
{

class Reorderer : public QObject
{
    Q_OBJECT

private:
    explicit Reorderer(QObject* parent = nullptr);

public:
    // Habilita arrastar e soltar (InternalMove) em listView e emite itemMoved() a cada
    // reordenacao. Retorna nullptr se listView for nullptr. A instancia pertence a listView.
    static Reorderer* attach(QListWidget* listView);

signals:
    // fromIndex e toIndex ja sao os indices finais do item na lista (corrigidos).
    void itemMoved(int fromIndex, int toIndex);
};

}  // namespace ListReorder
}  // namespace QtToolkit

#endif  // QTWIDGETSTOOLKIT_LISTREORDER_H
