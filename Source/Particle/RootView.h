#pragma once

#include "Data.h"

#include "Frames/Settings/AudioSettings.h"
#include "Frames/Status.h"
#include "Frames/NodeEditor.h"

namespace particle {

class RootView {

public:
    RootView(juce::AudioProcessor *audioProcessor,
             juce::AudioDeviceManager *audioDeviceManager,
             dsp::NodeProcessor *nodeProcessor);
    
    Data &getData();

    void draw();

private:
    Data data;
    AudioSettings audioSettings;
    Status status;
    NodeEditor nodeEditor;
};

} // namespace particle
