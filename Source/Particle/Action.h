#pragma once

#include "Named.h"

namespace particle {

class Action : public Named {

public:
    Action(std::string name);

    virtual void perform() = 0;
    virtual void undo() = 0;
};

} // namespace particle
