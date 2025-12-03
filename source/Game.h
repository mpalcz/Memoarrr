#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include <vector>
#include <cstddef>

class Game {
    private:
        Board board;
        std::vector<Player> players;
        int round = 0;
        const Card* previousCard = nullptr;
        const Card* currentCard  = nullptr;
        size_t currentPlayerIdx = 0;

    public:
        int getRound() const { return round; }

        void addPlayer(const Player& p) { players.push_back(p); }

        Player& getPlayer(Player::Side s);
        const Player& getPlayer(Player::Side s) const;

        const Card* getPreviousCard() const { return previousCard; }
        const Card* getCurrentCard() const { return currentCard; }
        void setCurrentCard(const Card* c) { previousCard = currentCard; currentCard = c; }

        Card* getCard(Board::Letter l, Board::Number n) { return board.getCard(l, n); }
        const Card* getCard(Board::Letter l, Board::Number n) const { return board.getCard(l, n); }
        void setCard(Board::Letter l, Board::Number n, Card* c) { board.setCard(l, n, c); }

        // ADDED methods

        bool turnFaceUp(Board::Letter l, Board::Number n) { return board.turnFaceUp(l, n); }
        bool turnFaceDown(Board::Letter l, Board::Number n) { return board.turnFaceDown(l, n); }
        const Board& getBoard() const { return board; }

        void allFacesDown() { board.allFacesDown(); }

        Player& getCurrentPlayer() { return players[currentPlayerIdx]; }
        size_t getCurrentPlayerIndex() const { return currentPlayerIdx; }
        const Player& getCurrentPlayer() const { return players[currentPlayerIdx]; }
        void nextPlayer() { currentPlayerIdx = (currentPlayerIdx + 1) % players.size(); }

        void startNewRound() {
            round++;
            allFacesDown();
            for (auto& p : players) p.setActive(true);
            previousCard = currentCard = nullptr;
            currentPlayerIdx = 0;
        }

        std::vector<Player>& getPlayers() { return players; }
        const std::vector<Player>& getPlayers() const { return players; }

        friend std::ostream& operator<<(std::ostream& os, const Game& g);
};

#endif