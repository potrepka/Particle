#pragma once

#include "Frame.h"

#include "imnodes.h"

namespace particle {

class NodeEditor : public Frame {

public:
    NodeEditor(Data &data);

private:
    void drawInternal() override;
};

} // namespace particle
