#pragma once

#include <string>

namespace particle {

class Named {

public:
    Named(std::string name);

    std::string getName() const;
    void setName(std::string name);

private:
    std::string name;
};

} // namespace particle