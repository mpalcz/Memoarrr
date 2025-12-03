// Game.cpp
#include "Game.h"
#include <algorithm>

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
    if (g.expertDisplayMode) {
        std::vector<std::pair<const Card*, std::string>> faceUps;
        for (int r = 0; r < GameParameters::BoardSize; ++r) {
            for (int c = 0; c < GameParameters::BoardSize; ++c) {
                if (r == GameParameters::CenterRow && c == GameParameters::CenterCol) continue;
                const Card* card = g.board.getCard(static_cast<Board::Letter>(r), static_cast<Board::Number>(c));
                if (card && card->isFaceUp()) {
                    char let = 'A' + r;
                    std::string pos = std::string(1, let) + std::to_string(c + 1);
                    faceUps.emplace_back(card, pos);
                }
            }
        }
        for (int cr = 0; cr < GameParameters::NumRowsCard; ++cr) {
            for (const auto& p : faceUps) os << (*p.first)(cr) << ' ';
            os << '\n';
        }
        for (const auto& p : faceUps) os << p.second << ' ';
        os << '\n';
    } else {
        os << g.board;
    }
    os << '\n';
    for (const auto& p : g.players) os << p;
    return os;
}
