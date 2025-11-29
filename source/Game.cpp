#include "Game.h"
#include <string>

void Game::addPlayer(const Player &p) {
    players.push_back(p); // apend to vector
}
Player &Game::getPlayer(Player::Side s) {
    return players[static_cast<int>(s)]; // operator[] on a vector returns a reference
}

void Game::setCurrentCard(const Card *c) {
    previous = current;
    current = c;
}

Card *Game::getCard(const Board::Letter &l, const Board::Number &n) {
    Card *card = gameBoard.getCard(l, n);
    return card;
}
void Game::setCard(const Board::Letter &l, const Board::Number &n, Card *c) { gameBoard.setCard(l, n, c); }

std::ostream &operator<<(std::ostream &os, const Game &g) {
    // display board using Board ostream
    os << g.gameBoard << std::endl;

    // display players names (not scores so skip using Player ostream)
    for (int i = 0; i < g.players.size(); i++) {
        const Player &player = g.players[i];
        os << player.getName() << ": " << player.getSide() << std::endl;
    }
}