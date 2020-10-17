#include "Named.h"

particle::Named::Named(std::string name)
        : name(name) {}

std::string particle::Named::getName() const {
    return name;
}

void particle::Named::setName(std::string name) {
    this->name = name;
}
