#include "Game.h"
#include <cstdlib>
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

void Game::startRound() {
    round++;
    currentPlayerIndex = 0;
    allFacesDown();

    // activate all players for the round
    for (Player &p : players) {
        p.setActive(true);
    }

    // might need to change this for other game modes to keep track of previous card (expert mode perhaps)
    current = nullptr;
    previous = nullptr;
}

void Game::peekCards(int boardSize) {
    const int size = boardSize;
    const int mid = size / 2; // integer division rounds down

    for (Player &player : players) {
        // get player side
        Player::Side side = player.getSide();

        // flip 3 cards depending on the side
        switch (side) {
        case Player::top:
            getCard(static_cast<Board::Letter>(1), static_cast<Board::Number>(mid))->turnFaceUp();
            getCard(static_cast<Board::Letter>(1), static_cast<Board::Number>(mid + 1))->turnFaceUp();
            getCard(static_cast<Board::Letter>(1), static_cast<Board::Number>(mid + 2))->turnFaceUp();
            break;
        case Player::bottom:
            getCard(static_cast<Board::Letter>(5), static_cast<Board::Number>(mid))->turnFaceUp();
            getCard(static_cast<Board::Letter>(5), static_cast<Board::Number>(mid + 1))->turnFaceUp();
            getCard(static_cast<Board::Letter>(5), static_cast<Board::Number>(mid + 2))->turnFaceUp();
            break;
        case Player::left:
            getCard(static_cast<Board::Letter>(mid), static_cast<Board::Number>(1))->turnFaceUp();
            getCard(static_cast<Board::Letter>(mid + 1), static_cast<Board::Number>(1))->turnFaceUp();
            getCard(static_cast<Board::Letter>(mid + 2), static_cast<Board::Number>(1))->turnFaceUp();
            break;
        case Player::right:
            getCard(static_cast<Board::Letter>(mid), static_cast<Board::Number>(5))->turnFaceUp();
            getCard(static_cast<Board::Letter>(mid + 1), static_cast<Board::Number>(5))->turnFaceUp();
            getCard(static_cast<Board::Letter>(mid + 2), static_cast<Board::Number>(5))->turnFaceUp();
            break;
        }

        std::cout << player.getName() << "'s turn to peek at the 3 closest cards" << std::endl;

        std::cout << gameBoard << std::endl;

        std::cout << "\nPress Enter when you're ready to move on...";
        std::cin.get();
        system("cls");
        allFacesDown(); // turn them back down after they look
    }
}