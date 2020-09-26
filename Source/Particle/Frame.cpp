#include "Frame.h"

particle::Frame::Frame(Data &data, std::string title)
        : data(data)
        , title(title) {}

particle::Data &particle::Frame::getData() {
    return data;
}

std::string particle::Frame::getTitle() {
    return title;
}

void particle::Frame::setTitle(std::string title) {
    this->title = title;
}

void particle::Frame::draw() {
    ImGui::Begin(title.c_str());
    drawInternal();
    ImGui::End();
}
