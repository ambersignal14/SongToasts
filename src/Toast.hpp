#include <Geode/Geode.hpp>

using namespace geode::prelude;

class Toast : public CCNode {
public:
    bool init(std::string name, std::string artist);
    static Toast* create(std::string name, std::string artist);
    void animate();
};
