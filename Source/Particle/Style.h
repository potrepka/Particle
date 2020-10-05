#pragma once

#include "imgui.h"
#include "imnodes.h"

namespace particle {

class Style {

public:
    ImVec4 backgroundColor = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);

    void apply();
    
};

} // namespace particle
