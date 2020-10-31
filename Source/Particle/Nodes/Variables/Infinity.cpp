#include "Infinity.h"

dsp::Infinity::Infinity(Space space)
        : Producer(Type::RATIO, space)
        , mode(std::make_shared<Input>(Type::INTEGER, space, Mode::MAX)) {
    getInputs().push_back(mode);
}

std::shared_ptr<dsp::Input> dsp::Infinity::getMode() const {
    return mode;
}

void dsp::Infinity::processNoLock() {
    getOutput()->getWrapper().replaceWithApplicationOf(
            [](Sample x) {
                switch (static_cast<int>(x)) {
                    case Mode::POSITIVE: return std::numeric_limits<Sample>::infinity();
                    case Mode::NEGATIVE: return -std::numeric_limits<Sample>::infinity();
                }
            },
            getMode()->getWrapper());
}
