#include "BeatRate.h"

dsp::BeatRate::BeatRate(juce::AudioProcessor *audioProcessor)
        : Producer(Type::HERTZ)
        , audioProcessor(audioProcessor) {}

void dsp::BeatRate::processNoLock() {
    juce::AudioPlayHead *playHead = audioProcessor->getPlayHead();
    if (playHead) {
        juce::AudioPlayHead::CurrentPositionInfo info;
        playHead->getCurrentPosition(info);
        getOutput()->getWrapper().fill(info.bpm * 0.01666666666666667);
    }
}
