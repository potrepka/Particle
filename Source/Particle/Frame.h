#pragma once

#include "Data.h"

#include <string>

#include "imgui.h"

namespace particle {

class Frame {

public:
    Frame(Data &data, std::string title);

    Data &getData();

    std::string getTitle() const;
    void setTitle(std::string title);

    void show();
    void hide();

    void draw();

private:
    Data &data;
    std::string title;
    bool visible;

    virtual void drawInternal() {}
};

} // namespace particle
