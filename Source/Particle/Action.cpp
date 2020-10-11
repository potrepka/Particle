#include "Action.h"

particle::Action::Action(Data &data)
        : data(data) {}

particle::Data &particle::Action::getData() {
    return data;
}
