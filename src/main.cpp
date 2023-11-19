#include <cstdlib>

#include <QCoreApplication>
#include <QDebug>
#include <QTimer>

#include "LibUvEventDispatcher.h"

int main(int argc, char** argv)
{
    auto dispatcher = new iz::Eventing::LibUvEventDispatcher{};
    QCoreApplication::setEventDispatcher(dispatcher);

    QCoreApplication app(argc, argv);

    std::size_t const timeoutsToEnd{ 10 };
    std::size_t currentTimeouts{ 0 };

    auto timer = new QTimer(&app);
    timer->setInterval(1000);

    QObject::connect(timer, &QTimer::timeout, &app, [&]() {
        currentTimeouts++;
        qDebug() << "timeout" << currentTimeouts << "\\" << timeoutsToEnd;

        if (currentTimeouts >= timeoutsToEnd) {
            qDebug() << "goodbye :]";

            app.exit(EXIT_SUCCESS);
        }
    });

    timer->start();

    return app.exec();
}
