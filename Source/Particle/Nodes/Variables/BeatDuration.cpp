#include "BeatDuration.h"

dsp::BeatDuration::BeatDuration(juce::AudioProcessor *audioProcessor)
        : Producer(Type::SECONDS) {
    this->audioProcessor = audioProcessor;
}

void dsp::BeatDuration::processNoLock() {
    if (audioProcessor) {
        juce::AudioPlayHead::CurrentPositionInfo info;
        audioProcessor->getPlayHead()->getCurrentPosition(info);
        getOutput()->getWrapper().fill(60.0 / info.bpm);
    }
}
