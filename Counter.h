#pragma once
#include <QObject>
#include <QSharedPointer>
#include <QDebug>
#include <QVector>
#include <cstdint>

enum class SignalType: uint8_t{
    INCREMENT,
    DECREMENT
};

class Counter: public QObject
{
    Q_OBJECT
public:
    Counter(qint64 startValue, QObject *parent = nullptr);
    ~Counter();
    qint64 Increment();
    qint64 Decrement();
    static void ShowValues();
signals:
    void NotifyOnCounterChange(SignalType type);
private slots:
    void onNotifyOnCounterChange(SignalType type);
private:
    qint64 m_counter;
    quint64 current_id;
    static QVector<Counter*> connected_counters;

    static quint64 id_counter;
};
