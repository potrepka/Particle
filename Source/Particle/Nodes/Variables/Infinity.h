#pragma once

#include "../../../DSP/src/Nodes/Core/Producer.h"

namespace dsp {

class Infinity : public Producer {

public:
    struct Mode {
        static const int MIN = 0;
        static const int MAX = 1;
        static const int POSITIVE = 0;
        static const int NEGATIVE = 1;
    };

    Infinity(Space type = Space::TIME);

    std::shared_ptr<Input> getMode() const;

protected:
    void processNoLock() override;

private:
    const std::shared_ptr<Input> mode;
};

} // namespace dsp
