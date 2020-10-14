#include "BeatRate.h"

dsp::BeatRate::BeatRate(juce::AudioProcessor *audioProcessor)
        : Producer(Type::HERTZ)
        , audioProcessor(audioProcessor) {}

void dsp::BeatRate::processNoLock() {
    if (audioProcessor) {
        juce::AudioPlayHead::CurrentPositionInfo info;
        audioProcessor->getPlayHead()->getCurrentPosition(info);
        getOutput()->getWrapper().fill(info.bpm * 0.01666666666666667);
    }
}
