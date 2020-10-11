#pragma once

#include "Data.h"

namespace particle {

class Action {

public:
    Action(Data &data);

    Data &getData();

    virtual void perform() = 0;
    virtual void undo() = 0;

private:
    Data &data;
};

} // namespace particle
