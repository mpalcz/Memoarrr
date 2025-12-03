// Player.cpp: Implements the Player class for managing player info, status, and rubies.

#include "Player.h"
#include "Rubis.h"

void Player::addRubis(const Rubis &rubisToAdd) { numRubies += int(rubisToAdd); }

// Toggles display mode for end-of-game ruby reveal.
// Params: endOfGame (bool).
// Result: Sets endOfGameDisplay flag.
void Player::setDisplayMode(bool endOfGame) {
    endOfGameDisplay = endOfGame;
}

// Converts Side enum to string for printing.
// Returns: String like "left".
std::string Player::sideToString() const {
    switch (side) {
    case Side::left: return "left";
    case Side::right: return "right";
    case Side::top: return "top";
    case Side::bottom: return "bottom";
    default: return "unknown";
    }
}

// Prints the player (name, side, status or rubies).
// Params: os (output stream), obj (const Player).
// Returns: os for chaining.
std::ostream &operator<<(std::ostream &os, const Player &obj) {
    os << obj.name << ": ";
    if (!obj.endOfGameDisplay) {
        os << obj.sideToString() << (obj.active ? " (active)" : " (inactive)") << std::endl;
    } else {
        os << obj.getNRubies() << " rubies" << std::endl;
    }
    return os;
}