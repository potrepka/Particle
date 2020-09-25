#pragma once

#include "Data.h"

#include <string>

#include "imgui.h"

namespace particle {

class Frame {

public:
    Frame(Data &data, std::string title);

    void draw();

private:
    Data &data;
    std::string title;

    virtual void drawInternal() {}
};

} // namespace particle
