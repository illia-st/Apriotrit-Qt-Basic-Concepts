#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "Counter.h"

quint64 Counter::id_counter = 1;
QVector<Counter*> Counter::connected_counters { };

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/QTApriorit/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);
    // test
    Counter c1(100);
    Counter c2(23);
    c1.Increment();
    Counter::ShowValues();
    c2.Increment();
    Counter::ShowValues();
    c1.Decrement();
    Counter::ShowValues();
    c2.Decrement();
    Counter::ShowValues();

    return app.exec();
}
