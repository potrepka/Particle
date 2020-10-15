#include "BeatDuration.h"

dsp::BeatDuration::BeatDuration(juce::AudioProcessor *audioProcessor)
        : Producer(Type::SECONDS)
        , audioProcessor(audioProcessor) {}

void dsp::BeatDuration::processNoLock() {
    juce::AudioPlayHead *playHead = audioProcessor->getPlayHead();
    if (playHead) {
        juce::AudioPlayHead::CurrentPositionInfo info;
        playHead->getCurrentPosition(info);
        getOutput()->getWrapper().fill(60.0 / info.bpm);
    }
}
