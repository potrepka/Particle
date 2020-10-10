#pragma once

#include "Frame.h"

namespace particle {

class Status : public Frame {

public:
    Status(Data &data);

private:
    double cpu;
    double fps;

    void drawInternal() override;
};

} // namespace particle
