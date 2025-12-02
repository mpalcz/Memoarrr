#include "Game.h"

Player& Game::getPlayer(Player::Side s) {
    for (auto& p : players)
        if (p.getSide() == s) return p;
    throw std::out_of_range("No player on that side");
}

const Player& Game::getPlayer(Player::Side s) const {
    for (const auto& p : players)
        if (p.getSide() == s) return p;
    throw std::out_of_range("No player on that side");
}

std::ostream& operator<<(std::ostream& os, const Game& g) {
    os << g.board << '\n';
    for (const auto& p : g.players)
        os << p << '\n';
    return os;
}