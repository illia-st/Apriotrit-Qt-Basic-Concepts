#include "Counter.h"

Counter::Counter(qint64 startValue, QObject *parent): QObject(parent)
    , m_counter(startValue), current_id(id_counter)
{
    connected_counters.push_back(this);
    qInfo() << "A new counter with id " << id_counter << " is created";
    ++id_counter;
    connect(this, &Counter::NotifyOnCounterChange, this, &Counter::onNotifyOnCounterChange);
}
Counter::~Counter(){
    for(std::size_t i {}; i < connected_counters.size(); ++i){
        if(connected_counters[i] == this){
            connected_counters.erase(connected_counters.begin() + i);
            break;
        }
    }
}
qint64 Counter::Increment(){
    qInfo() << "Counter with id " << current_id << " is incremented";
    qInfo() << "Counter::Increment() was called";
    qInfo() << "========================================";
    ++m_counter;
    emit NotifyOnCounterChange(SignalType::INCREMENT);
    return m_counter;
}
qint64 Counter::Decrement(){
    qInfo() << "Counter with id " << current_id << " is decremented";
    qInfo() << "Counter::Decrement() was called";
    qInfo() << "========================================";
    --m_counter;
    emit NotifyOnCounterChange(SignalType::DECREMENT);
    return m_counter;
}
void Counter::ShowValues(){
    qInfo() << "Counter::ShowValues()";
    for(const auto& counter: connected_counters){
        qInfo() << "A counter with id " << counter->current_id;
        qInfo() << "Value " << counter->m_counter;
        qInfo() << "========================================";
    }
}
// slots
void Counter::onNotifyOnCounterChange(SignalType type){
    if(connected_counters.empty()) return;
    for(auto& counter: connected_counters){
        if(counter->current_id == this->current_id) continue;
        switch (type){
            case SignalType::INCREMENT:{
                ++counter->m_counter;
                qInfo() << "Counter with id " << counter->current_id << " was incremented by " << this->current_id;
                break;
            }
            case SignalType::DECREMENT:{
                --counter->m_counter;
                qInfo() << "Counter with id " << counter->current_id << " was decremented by " << this->current_id;
                break;
            }
        }
    }
}

