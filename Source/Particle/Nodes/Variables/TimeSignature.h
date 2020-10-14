#pragma once

#include "../../../DSP/src/Node.h"

#include <JuceHeader.h>

namespace dsp {

class TimeSignature : public Node {

public:
    TimeSignature(juce::AudioProcessor *audioProcessor);

    std::shared_ptr<Output> getNumerator() const;
    std::shared_ptr<Output> getDenominator() const;

protected:
    void processNoLock() override;

private:
    const std::shared_ptr<Output> numerator;
    const std::shared_ptr<Output> denominator;
    juce::AudioProcessor *audioProcessor;
};

} // namespace dsp
