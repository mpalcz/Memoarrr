// Game.h
#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include "Card.h"
#include <vector>
#include <cstddef>
#include <utility>

class Game {
private:
    Board board;
    std::vector<Player> players;
    int round = 0;
    Card* previousCard = nullptr;
    Card* currentCard = nullptr;
    size_t currentPlayerIdx = 0;
    bool expertDisplayMode;
    bool expertRulesMode;
    bool extraTurn = false;
    std::pair<Board::Letter, Board::Number> currentPosition;
    std::pair<Board::Letter, Board::Number> blockedPosition = {Board::Letter::A, Board::Number::One}; // Invalid initial

public:
    Game(bool ed = false, bool er = false) : expertDisplayMode(ed), expertRulesMode(er) {}

    int getRound() const { return round; }

    void addPlayer(const Player& p) { players.push_back(p); }

    Player& getPlayer(Player::Side s);
    const Player& getPlayer(Player::Side s) const;

    const Card* getPreviousCard() const { return previousCard; }
    const Card* getCurrentCard() const { return currentCard; }
    void setCurrentCard(const Card* c) { previousCard = currentCard; currentCard = const_cast<Card*>(c); }

    Card* getCard(Board::Letter l, Board::Number n) { return board.getCard(l, n); }
    const Card* getCard(Board::Letter l, Board::Number n) const { return board.getCard(l, n); }
    void setCard(Board::Letter l, Board::Number n, Card* c) { board.setCard(l, n, c); }

    bool turnFaceUp(Board::Letter l, Board::Number n) { return board.turnFaceUp(l, n); }
    bool turnFaceDown(Board::Letter l, Board::Number n) { return board.turnFaceDown(l, n); }
    bool isFaceUp(Board::Letter l, Board::Number n) const { return board.isFaceUp(l, n); }
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
        blockedPosition = {Board::Letter::A, Board::Number::One}; // Reset
    }

    std::vector<Player>& getPlayers() { return players; }
    const std::vector<Player>& getPlayers() const { return players; }

    bool isExpertRules() const { return expertRulesMode; }
    void setExtraTurn(bool et) { extraTurn = et; }
    bool getExtraTurn() const { return extraTurn; }
    void setCurrentPosition(Board::Letter l, Board::Number n) { currentPosition = {l, n}; }
    std::pair<Board::Letter, Board::Number> getCurrentPosition() const { return currentPosition; }
    void setBlockedPosition(Board::Letter l, Board::Number n) { blockedPosition = {l, n}; }
    std::pair<Board::Letter, Board::Number> getBlockedPosition() const { return blockedPosition; }

    friend std::ostream& operator<<(std::ostream& os, const Game& g);
};

#endif