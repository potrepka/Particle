#pragma once

#include "Data.h"

#include "Frames/Nodes/NodeGraph.h"
#include "Frames/Settings/AudioSettings.h"
#include "Frames/Utility/Status.h"

namespace particle {

class RootView {

public:
    RootView(juce::AudioProcessor *audioProcessor,
             juce::AudioDeviceManager *audioDeviceManager,
             dsp::NodeProcessor *nodeProcessor);
    
    Data &getData();

    void setup();
    void draw();

private:
    Data data;
    NodeGraph nodeGraph;
    AudioSettings audioSettings;
    Status status;

    std::vector<const char *> ttf;
    std::vector<int> ttfSize;
    std::vector<void *> fontData;
    std::vector<ImFont *> font;
};

} // namespace particle
