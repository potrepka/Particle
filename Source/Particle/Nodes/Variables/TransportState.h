#pragma once

#include "../../../DSP/src/Node.h"

#include <JuceHeader.h>

namespace dsp {

class TransportState : public Node {

public:
    TransportState(juce::AudioProcessor *audioProcessor);

    std::shared_ptr<Output> getTimeElapsed() const;
    std::shared_ptr<Output> isPlaying() const;
    std::shared_ptr<Output> isRecording() const;

protected:
    void processNoLock() override;

private:
    const std::shared_ptr<Output> timeElapsed;
    const std::shared_ptr<Output> playing;
    const std::shared_ptr<Output> recording;
    juce::AudioProcessor *audioProcessor;
};

} // namespace dsp
