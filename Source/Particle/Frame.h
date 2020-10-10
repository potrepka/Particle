#pragma once

#include "Data.h"

#include <string>

#include "imgui.h"

namespace particle {

class Frame {

public:
    Frame(Data &data, std::string name);

    Data &getData();

    std::string getName() const;
    void setName(std::string name);

    bool &isVisible();
    void show();
    void hide();
    void toggle();

    void draw();

private:
    Data &data;
    std::string name;
    bool visible;

    virtual void drawInternal() {}
};

} // namespace particle
