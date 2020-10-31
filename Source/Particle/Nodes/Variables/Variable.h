#pragma once

#include "../../../DSP/src/Nodes/Core/Producer.h"

namespace dsp {

class Variable : public Producer {

public:
    Variable(Sample value = 0.0, Type type = Type::RATIO, Space space = Space::TIME);

    Sample get() const;
    void set(Sample value);

protected:
    void processNoLock() override;

private:
    Sample value;
};

} // namespace dsp
