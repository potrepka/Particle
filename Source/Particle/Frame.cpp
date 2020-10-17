#include "Frame.h"

particle::Frame::Frame(Data &data, std::string name)
        : Named(name)
        , data(data)
        , visible(false) {}

particle::Data &particle::Frame::getData() {
    return data;
}

bool &particle::Frame::isVisible() {
    return visible;
}

void particle::Frame::show() {
    visible = true;
}

void particle::Frame::hide() {
    visible = false;
}

void particle::Frame::toggle() {
    visible = !visible;
}

void particle::Frame::draw() {
    if (visible) {
        ImGui::Begin(getName().c_str(), &visible);
        drawInternal();
        ImGui::End();
    }
}
