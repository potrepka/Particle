#include "TransportState.h"

dsp::TransportState::TransportState(juce::AudioProcessor *audioProcessor)
        : timeElapsed(std::make_shared<Output>(Type::SECONDS))
        , playing(std::make_shared<Output>(Type::BOOLEAN))
        , recording(std::make_shared<Output>(Type::BOOLEAN))
        , audioProcessor(audioProcessor) {}

std::shared_ptr<dsp::Output> dsp::TransportState::getTimeElapsed() const {
    return timeElapsed;
}

std::shared_ptr<dsp::Output> dsp::TransportState::isPlaying() const {
    return playing;
}

std::shared_ptr<dsp::Output> dsp::TransportState::isRecording() const {
    return recording;
}

void dsp::TransportState::processNoLock() {
    juce::AudioPlayHead *playHead = audioProcessor->getPlayHead();
    if (playHead) {
        juce::AudioPlayHead::CurrentPositionInfo info;
        playHead->getCurrentPosition(info);
        getTimeElapsed()->getWrapper().fill(info.timeInSeconds);
        isPlaying()->getWrapper().fill(info.isPlaying);
        isRecording()->getWrapper().fill(info.isRecording);
    }
}
