#pragma once

#include "../../../DSP/src/Nodes/Core/Producer.h"

#include <JuceHeader.h>

namespace dsp {

class BeatRate : public Producer {

public:
    BeatRate(juce::AudioProcessor *audioProcessor);

protected:
    void processNoLock() override;

private:
    juce::AudioProcessor *audioProcessor;
};

} // namespace dsp
