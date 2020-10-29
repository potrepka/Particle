#include "Variable.h"

dsp::Variable::Variable(Sample value, Type type)
        : Producer(type)
        , value(value) {}

dsp::Sample dsp::Variable::get() const {
    return value;
}

void dsp::Variable::set(Sample value) {
    lock();
    this->value = value;
    unlock();
}

void dsp::Variable::processNoLock() {
    getOutput()->getWrapper().fill(value);
}
