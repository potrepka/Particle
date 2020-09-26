#pragma once

#include "imgui.h"
#include "imnodes.h"

namespace particle {

class Style {

public:
    ImVec4 backgroundColor = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    void apply();
    
};

} // namespace particle
