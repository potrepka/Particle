#pragma once

#include <JuceHeader.h>

#include "Action.h"
#include "Style.h"

#include <deque>

#include "NodeProcessor.h"

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

    bool hasUndo() const;
    bool hasRedo() const;

    void pushAction(std::shared_ptr<Action> action);
    void undo();
    void redo();

private:
    juce::AudioProcessor *audioProcessor;
    juce::AudioDeviceManager *audioDeviceManager;
    dsp::NodeProcessor *nodeProcessor;
    Style style;
    std::deque<std::shared_ptr<Action>> history;
    std::deque<std::shared_ptr<Action>> forward;
};

} // namespace particle
