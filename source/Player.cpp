#include "Player.h"
#include "Rubis.h"

void Player::setDisplayMode(bool endOfGame) {
    // TODO probably for expert mode or smth
}

// Converts Side enum to string
std::string Player::sideToString() const {
    switch (side) {
    case Player::Side::left: return "left";
    case Player::Side::right: return "right";
    case Player::Side::top: return "top";
    case Player::Side::bottom: return "bottom";
    default: return "unknown";
    }
}

// Operator<< overload definition
std::ostream &operator<<(std::ostream &os, const Player &obj) {
    os << obj.name << ": ";
    if (!obj.endOfGameDisplay) {
        os << obj.sideToString() << (obj.active ? " (active)" : " (inactive)") << std::endl;
    } else {
        os << obj.getNRubies() << (obj.getNRubies() > 1 ? " rubies" : " ruby") << std::endl;
    }
    return os;
}