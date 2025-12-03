// Player.cpp: Implements the Player class for managing player info, status, and rubis.

#include "Player.h"
#include "Rubis.h"

void Player::addRubis(const Rubis &rubisToAdd) { numRubies += int(rubisToAdd); };

// Toggles display mode for end-of-game rubis reveal.
// Params: endOfGame (bool).
// Result: Sets endOfGameDisplay flag.
void Player::setDisplayMode(bool endOfGame) {
    endOfGameDisplay = endOfGame;
}

// Converts Side enum to string for printing.
// Returns: String like "left".
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
        os << obj.getNRubies() << " rubis" << std::endl;
    }
    return os;
}