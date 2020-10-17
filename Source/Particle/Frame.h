#pragma once

#include "Data.h"
#include "Named.h"

#include "imgui.h"

namespace particle {

class Frame : public Named {

public:
    Frame(Data &data, std::string name);

    Data &getData();

    bool &isVisible();
    void show();
    void hide();
    void toggle();

    void draw();

private:
    Data &data;
    bool visible;

    virtual void drawInternal() {}
};

} // namespace particle
