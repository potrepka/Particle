#include "Frame.h"

particle::Frame::Frame(Data &data, std::string title)
        : data(data)
        , title(title)
        , visible(false) {}

particle::Data &particle::Frame::getData() {
    return data;
}

std::string particle::Frame::getTitle() const {
    return title;
}

void particle::Frame::setTitle(std::string title) {
    this->title = title;
}

void particle::Frame::show() {
    visible = true;
}

void particle::Frame::hide() {
    visible = false;
}

void particle::Frame::draw() {
    if (visible) {
        ImGui::Begin(title.c_str(), &visible);
        drawInternal();
        ImGui::End();
    }
}
