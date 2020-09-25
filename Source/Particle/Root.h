#pragma once

#include "Data.h"
#include "Frames/NodeEditor.h"

#include "imnodes.h"

namespace particle {

class Root {

public:
    Root();
    ~Root();

    Data &getData();

    void draw();

private:
    Data data;
    NodeEditor nodeEditor;
};

} // namespace particle
