#pragma once

#include "Frame.h"

namespace particle {

class AudioSettings : public Frame {

public:
    AudioSettings(Data &data);

private:
    void drawInternal() override;
};

} // namespace particle
