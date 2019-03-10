#pragma once

#include <QEvent>
#include <QObject>
#include <functional>

namespace ab
{
    /// Handle QObject's `eventFilter` using lambdas.
    class FunctionEventFilter : public QObject
    {
        Q_OBJECT

    public:
        FunctionEventFilter(
            QObject* parent, std::function<bool(QObject*, QEvent*)> function);

    protected:
        bool eventFilter(QObject* watched, QEvent* event) override;

    private:
        std::function<bool(QObject*, QEvent*)> function_;
    };
}  // namespace ab
