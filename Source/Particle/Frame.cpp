#include "Frame.h"

particle::Frame::Frame(Data &data, std::string title)
        : data(data)
        , title(title) {}

void particle::Frame::draw() {
    ImGui::Begin(title.c_str());
    drawInternal();
    ImGui::End();
}
