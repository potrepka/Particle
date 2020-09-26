#pragma once

#include "Frame.h"

namespace particle {

class Status : public Frame, public juce::Timer {

public:
    Status(Data &data);

private:
    double cpu;
    double fps;

    void drawInternal() override;
    void timerCallback() override;
};

} // namespace particle
