#include "Frame.h"

particle::Frame::Frame(Data &data, std::string name)
        : data(data)
        , name(name)
        , visible(false) {}

particle::Data &particle::Frame::getData() {
    return data;
}

std::string particle::Frame::getName() const {
    return name;
}

void particle::Frame::setName(std::string name) {
    this->name = name;
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
        ImGui::Begin(name.c_str(), &visible);
        drawInternal();
        ImGui::End();
    }
}
