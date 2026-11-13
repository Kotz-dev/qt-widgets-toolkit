//
// Created by KoTz on 10/11/2026.
//

#ifndef QTWIDGETSTOOLKIT_LISTREORDER_H
#define QTWIDGETSTOOLKIT_LISTREORDER_H

#include <QListWidget>
#include <QObject>
#include <algorithm>
#include <memory>
#include <vector>

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
    static Reorderer* attach(QListWidget* listView);

    /// Mantém `data` sincronizado com a ordem da lista, guardando-o POR REFERÊNCIA.
    ///
    /// ATENÇÃO: `data` precisa viver mais que `listView`. Passar um vetor local
    /// (destruído ao sair do escopo) ou um membro de objeto que morre antes da lista
    /// causa use-after-free no próximo arrastar. Nesses casos use a sobrecarga
    /// com std::shared_ptr abaixo. Para vetores globais/estáticos esta é segura.
    template <typename T>
    static Reorderer* attach(QListWidget* listView, std::vector<T>& data)
    {
        Reorderer* reorderer = attach(listView);
        if (reorderer == nullptr)
        {
            return nullptr;
        }

        QObject::connect(
                reorderer,
                &Reorderer::itemMoved,
                reorderer,
                [&data](int from, int to) { moveElement(data, from, to); });
        return reorderer;
    }

    /// Variante segura: o Reorderer compartilha a posse do vetor, que vive enquanto
    /// a lista existir, mesmo que o dono original saia de escopo.
    /// Se `data` for nulo, apenas habilita o arrastar e emite `itemMoved`.
    template <typename T>
    static Reorderer* attach(QListWidget* listView, std::shared_ptr<std::vector<T>> data)
    {
        Reorderer* reorderer = attach(listView);
        if (reorderer == nullptr || !data)
        {
            return reorderer;
        }

        QObject::connect(
                reorderer,
                &Reorderer::itemMoved,
                reorderer,
                [data = std::move(data)](int from, int to) { moveElement(*data, from, to); });
        return reorderer;
    }

private:
    template <typename T>
    static void moveElement(std::vector<T>& data, int from, int to)
    {
        const int size = static_cast<int>(data.size());
        if (from == to || from < 0 || to < 0 || from >= size || to >= size)
        {
            return;
        }

        auto it = data.begin();
        if (from < to)
        {
            std::rotate(it + from, it + from + 1, it + to + 1);
        }
        else
        {
            std::rotate(it + to, it + from, it + from + 1);
        }
    }

signals:
    void itemMoved(int fromIndex, int toIndex);
};

}  // namespace ListReorder
}  // namespace QtToolkit

#endif  // QTWIDGETSTOOLKIT_LISTREORDER_H
