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
