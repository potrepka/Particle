#pragma once

#include "Frame.h"

namespace particle {

class NodeEditor : public Frame {

public:
    NodeEditor(Data &data);

private:
    void drawInternal() override;
};

} // namespace particle
