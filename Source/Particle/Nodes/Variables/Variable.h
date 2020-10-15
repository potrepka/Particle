#pragma once

#include "../../../DSP/src/Nodes/Core/Producer.h"

namespace dsp {

class Variable : public Producer {

public:
    Variable(Type type = Type::RATIO);

    Sample get() const;
    void set(Sample value);
    void apply(std::function<Sample(Sample)> f);

protected:
    void processNoLock() override;

private:
    Sample value;
};

} // namespace dsp
