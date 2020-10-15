#include "Variable.h"

dsp::Variable::Variable(Type type)
        : Producer(type)
        , value(0.0) {}

dsp::Sample dsp::Variable::get() const {
    return value;
}

void dsp::Variable::set(Sample value) {
    lock();
    this->value = value;
    unlock();
}

void dsp::Variable::apply(std::function<Sample(Sample)> f) {
    lock();
    value = f(value);
    unlock();
}

void dsp::Variable::processNoLock() {
    getOutput()->getWrapper().fill(value);
}
