#pragma once

#include "../../../DSP/src/Nodes/Core/Producer.h"

#include <JuceHeader.h>

namespace dsp {

class BeatDuration : public Producer {

public:
    BeatDuration(juce::AudioPlayHead *playHead);

protected:
    void processNoLock() override;

private:
    juce::AudioPlayHead *playHead;
};

} // namespace dsp
