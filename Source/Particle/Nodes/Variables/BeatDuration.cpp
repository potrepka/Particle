#include "BeatDuration.h"

dsp::BeatDuration::BeatDuration(juce::AudioPlayHead *playHead)
        : Producer(Type::SECONDS) {
    this->playHead = playHead;
}

void dsp::BeatDuration::processNoLock() {
    if (playHead) {
        juce::AudioPlayHead::CurrentPositionInfo info;
        playHead->getCurrentPosition(info);
        getOutput()->getWrapper().fill(60.0 / info.bpm);
    }
}
