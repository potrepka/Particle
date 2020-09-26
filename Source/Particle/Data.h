#pragma once

#include "NodeProcessor.h"

#include "Style.h"

namespace particle {

class Data {

public:
    Data(juce::AudioProcessor *audioProcessor,
         juce::AudioDeviceManager *audioDeviceManager,
         dsp::NodeProcessor *nodeProcessor);
    
    juce::AudioProcessor *getAudioProcessor();
    juce::AudioDeviceManager *getAudioDeviceManager();
    dsp::NodeProcessor *getNodeProcessor();
    Style &getStyle();

    void setAudioProcessor(juce::AudioProcessor *audioProcessor);
    void setAudioDeviceManager(juce::AudioDeviceManager *audioDeviceManager);
    void setNodeProcessor(dsp::NodeProcessor *nodeProcessor);

private:
    juce::AudioProcessor *audioProcessor;
    juce::AudioDeviceManager *audioDeviceManager;
    dsp::NodeProcessor *nodeProcessor;
    Style style;
};

} // namespace particle
