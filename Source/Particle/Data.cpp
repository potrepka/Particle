#include "Data.h"

particle::Data::Data(juce::AudioProcessor *audioProcessor,
                     juce::AudioDeviceManager *audioDeviceManager,
                     dsp::NodeProcessor *nodeProcessor)
        : audioProcessor(audioProcessor)
        , audioDeviceManager(audioDeviceManager)
        , nodeProcessor(nodeProcessor) {}

juce::AudioProcessor *particle::Data::getAudioProcessor() {
    return audioProcessor;
}

juce::AudioDeviceManager *particle::Data::getAudioDeviceManager() {
    return audioDeviceManager;
}

dsp::NodeProcessor *particle::Data::getNodeProcessor() {
    return nodeProcessor;
}

particle::Style &particle::Data::getStyle() {
    return style;
}

void particle::Data::setAudioProcessor(juce::AudioProcessor *audioProcessor) {
    this->audioProcessor = audioProcessor;
}

void particle::Data::setAudioDeviceManager(juce::AudioDeviceManager *audioDeviceManager) {
    this->audioDeviceManager = audioDeviceManager;
}

void particle::Data::setNodeProcessor(dsp::NodeProcessor *nodeProcessor) {
    this->nodeProcessor = nodeProcessor;
}

bool particle::Data::hasUndo() const {
    return !history.empty();
}

bool particle::Data::hasRedo() const {
    return !forward.empty();
}

void particle::Data::pushAction(std::shared_ptr<Action> action) {
    action->perform();
    history.push_back(action);
    forward.clear();
}

void particle::Data::undo() {
    if (!history.empty()) {
        std::shared_ptr<Action> action = history.back();
        action->undo();
        forward.push_back(action);
        history.pop_back();
    }
}

void particle::Data::redo() {
    if (!forward.empty()) {
        std::shared_ptr<Action> action = forward.back();
        action->perform();
        history.push_back(action);
        forward.pop_back();
    }
}
