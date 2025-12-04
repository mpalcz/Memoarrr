// Game.h
#ifndef GAME_H
#define GAME_H

#include "Board.h"
#include "Player.h"
#include "Card.h"
#include <vector>
#include <cstddef>
#include <utility>
#include <optional>

// Holds the full game state: board, players, round, expert flags, etc.
class Game {
  private:
    // ==== Instance variables ====
    Board board;
    std::vector<Player> players;
    int round = 0;
    const Card* previousCard = nullptr;
    const Card* currentCard  = nullptr;
    size_t currentPlayerIdx = 0;
    bool expertDisplayMode = false;
    bool expertRulesMode = false;
    bool extraTurn       = false;
    std::pair<Board::Letter, Board::Number> currentPosition = {Board::Letter::A, Board::Number::One};

    // Walrus effect: block one position for the *next* active player's turn
    std::optional<std::pair<Board::Letter, Board::Number> > blockedPosition;
    int walrusTurnsRemaining = 0; // counts down: 2 (set) -> 1 -> 0 (clear)

  public:
    // ==== Constructors ====
    Game(bool ed = false, bool er = false)
        : board(),
          players(),
          round(0),
          previousCard(nullptr),
          currentCard(nullptr),
          currentPlayerIdx(0),
          expertDisplayMode(ed),
          expertRulesMode(er),
          extraTurn(false),
          currentPosition(Board::Letter::A, Board::Number::One),
          blockedPosition(std::nullopt),
          walrusTurnsRemaining(0) {}

    // ==== Basic getters/setters ====
    int getRound() const { return round; }

    void addPlayer(const Player& p) { players.push_back(p); }

    Player& getPlayer(Player::Side s);
    const Player& getPlayer(Player::Side s) const;

    const Card* getPreviousCard() const { return previousCard; }
    const Card* getCurrentCard() const  { return currentCard; }

    // Moves currentCard into previousCard and sets new current.
    // Params: c (const Card*).
    // Returns: nothing.
    void setCurrentCard(const Card* c) {
        previousCard = currentCard;
        currentCard  = c;
    }

    Card* getCard(Board::Letter l, Board::Number n) { return board.getCard(l, n); }
    const Card* getCard(Board::Letter l, Board::Number n) const { return board.getCard(l, n); }

    void setCard(Board::Letter l, Board::Number n, Card* c) { board.setCard(l, n, c); }

    // Swaps two cards on the underlying Board.
    // Params: l1,n1 and l2,n2.
    // Returns: nothing.
    void swapCards(Board::Letter l1, Board::Number n1, Board::Letter l2, Board::Number n2) {
        board.swapCards(l1, n1, l2, n2);
    }

    bool turnFaceUp(Board::Letter l, Board::Number n) { return board.turnFaceUp(l, n); }
    bool turnFaceDown(Board::Letter l, Board::Number n) { return board.turnFaceDown(l, n); }
    bool isFaceUp(Board::Letter l, Board::Number n) const { return board.isFaceUp(l, n); }
    const Board& getBoard() const { return board; }

    void allFacesDown() { board.allFacesDown(); }

    // ==== Player turn helpers ====
    Player& getCurrentPlayer() { return players[currentPlayerIdx]; }
    size_t getCurrentPlayerIndex() const { return currentPlayerIdx; }
    const Player& getCurrentPlayer() const { return players[currentPlayerIdx]; }

    // Goes to the next index (wrap around).
    // Params: none.
    // Returns: nothing.
    void nextPlayer() { currentPlayerIdx = (currentPlayerIdx + 1) % players.size(); }

    // Starts a fresh round: resets board face state, players active, round counters, walrus info.
    // Params: none.
    // Returns: nothing.
    void startNewRound() {
        round++;
        allFacesDown();
        for (std::size_t i = 0; i < players.size(); ++i) {
            players[i].setActive(true);
        }
        previousCard        = nullptr;
        currentCard         = nullptr;
        currentPlayerIdx    = 0;
        blockedPosition     = std::nullopt;
        walrusTurnsRemaining = 0;
    }

    // ==== Player list access ====
    std::vector<Player>& getPlayers() { return players; }
    const std::vector<Player>& getPlayers() const { return players; }

    // ==== Expert flags ====
    bool isExpertRules() const { return expertRulesMode; }

    void setExtraTurn(bool et) { extraTurn = et; }
    bool getExtraTurn() const { return extraTurn; }

    void setCurrentPosition(Board::Letter l, Board::Number n) { currentPosition = std::make_pair(l, n); }
    std::pair<Board::Letter, Board::Number> getCurrentPosition() const { return currentPosition; }

    // ==== Walrus helpers ====
    // Stores a blocked position and sets countdown to 2 turns.
    void setBlockedPosition(Board::Letter l, Board::Number n) {
        blockedPosition = std::make_pair(l, n);
        walrusTurnsRemaining = 2;
    }

    // Clears blocked position and resets counter.
    void clearBlockedPosition() {
        blockedPosition = std::nullopt;
        walrusTurnsRemaining = 0;
    }

    // Should be called once at the *end* of each player's turn.
    // Decrements and clears walrus block when done.
    void advanceWalrusEffect() {
        if (!blockedPosition.has_value()) return;
        if (walrusTurnsRemaining > 0) {
            walrusTurnsRemaining--;
            if (walrusTurnsRemaining == 0) {
                blockedPosition = std::nullopt;
            }
        } else {
            blockedPosition = std::nullopt; // safety, shouldn't really happen
        }
    }

    std::optional<std::pair<Board::Letter, Board::Number> > getBlockedPosition() const {
        return blockedPosition;
    }

    // ==== Operators ====
    friend std::ostream& operator<<(std::ostream& os, const Game& g);
};

#endif
