// Game.cpp: Implements the Game class for managing game state.

#include "Game.h"
#include "GameParameters.h"
#include <algorithm>

// Finds a player by side (non-const).
// Params: s (Player::Side).
// Returns: reference to Player.
// Throws: out_of_range if side not found.
Player& Game::getPlayer(Player::Side s) {
    for (std::size_t i = 0; i < players.size(); ++i) {
        if (players[i].getSide() == s) return players[i];
    }
    throw std::out_of_range("No player on that side");
}

// Finds a player by side (const).
// Params: s (Player::Side).
// Returns: const reference to Player.
// Throws: out_of_range if side not found.
const Player& Game::getPlayer(Player::Side s) const {
    for (std::size_t i = 0; i < players.size(); ++i) {
        if (players[i].getSide() == s) return players[i];
    }
    throw std::out_of_range("No player on that side");
}

// Prints either the board or the expert display view plus players.
// Params: os (output stream), g (const Game).
// Returns: os for chaining.
std::ostream& operator<<(std::ostream& os, const Game& g) {
    if (g.expertDisplayMode) {
        std::vector<std::pair<const Card*, std::string> > faceUps;
        for (int r = 0; r < GameParameters::BoardSize; ++r) {
            for (int c = 0; c < GameParameters::BoardSize; ++c) {
                if (r == GameParameters::CenterRow && c == GameParameters::CenterCol) continue;
                const Card* card = g.board.getCard(static_cast<Board::Letter>(r), static_cast<Board::Number>(c));
                if (card && card->isFaceUp()) {
                    char let = static_cast<char>('A' + r);
                    std::string pos(1, let);
                    pos += std::to_string(c + 1);
                    faceUps.push_back(std::make_pair(card, pos));
                }
            }
        }
        for (int cr = 0; cr < GameParameters::NumRowsCard; ++cr) {
            for (std::size_t i = 0; i < faceUps.size(); ++i) {
                os << (*faceUps[i].first)(cr) << ' ';
            }
            os << '\n';
        }

        // Center positions under each card in the display
        for (std::size_t i = 0; i < faceUps.size(); ++i) {
            int cardWidth = GameParameters::NumRowsCard;  
            int totalWidth = cardWidth + 2;                
            std::string pos = faceUps[i].second;          

            int padding = (totalWidth - static_cast<int>(pos.size())) / 2;
            if (padding < 0) padding = 0;

            os << std::string(padding, ' ') << pos << std::string(padding, ' ');
        }
        os << '\n';

    } else {
        os << g.board;
    }
    os << '\n';
    for (std::size_t i = 0; i < g.players.size(); ++i) {
        os << g.players[i];
    }
    return os;
}
