#include "TransportState.h"

dsp::TransportState::TransportState(juce::AudioProcessor *audioProcessor)
        : playing(std::make_shared<Output>(Type::BOOLEAN))
        , recording(std::make_shared<Output>(Type::BOOLEAN))
        , timeElapsed(std::make_shared<Output>(Type::SECONDS))
        , audioProcessor(audioProcessor) {}

std::shared_ptr<dsp::Output> dsp::TransportState::isPlaying() const {
    return playing;
}

std::shared_ptr<dsp::Output> dsp::TransportState::isRecording() const {
    return recording;
}

std::shared_ptr<dsp::Output> dsp::TransportState::getTimeElapsed() const {
    return timeElapsed;
}

void dsp::TransportState::processNoLock() {
    if (audioProcessor) {
        juce::AudioPlayHead::CurrentPositionInfo info;
        audioProcessor->getPlayHead()->getCurrentPosition(info);
        isPlaying()->getWrapper().fill(info.isPlaying);
        isRecording()->getWrapper().fill(info.isRecording);
        getTimeElapsed()->getWrapper().fill(info.timeInSeconds);
    }
}
