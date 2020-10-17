#pragma once

#include "Named.h"

namespace particle {

class Action : public Named {

public:
    Action(std::string name);

    virtual void perform() {}
    virtual void undo() {}
};

} // namespace particle