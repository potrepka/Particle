#pragma once

#include "Data.h"
#include "Frames/Frames.h"

namespace particle {

class View {

public:
    View(juce::AudioProcessor *audioProcessor,
         juce::AudioDeviceManager *audioDeviceManager,
         dsp::NodeProcessor *nodeProcessor);
    
    Data &getData();

    void setup();
    void draw();

private:
    Data data;
    bool showFrames;
    std::vector<std::shared_ptr<Frame>> frames;

    std::shared_ptr<dsp::Node> projectContainer;
    std::shared_ptr<NodeGraph> nodeGraph;
    std::shared_ptr<AudioSettings> audioSettings;
    std::shared_ptr<Status> status;

    std::vector<const char *> ttf;
    std::vector<int> ttfSize;
    std::vector<void *> fontData;
    std::vector<ImFont *> font;
};

} // namespace particle
