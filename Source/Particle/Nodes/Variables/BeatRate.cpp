#include "BeatRate.h"

dsp::BeatRate::BeatRate(juce::AudioPlayHead *playHead)
        : Producer(Type::HERTZ) {
    this->playHead = playHead;
}

void dsp::BeatRate::processNoLock() {
    if (playHead) {
        juce::AudioPlayHead::CurrentPositionInfo info;
        playHead->getCurrentPosition(info);
        getOutput()->getWrapper().fill(info.bpm / 60.0);
    }
}
