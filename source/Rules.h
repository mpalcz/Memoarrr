// Rules.h
#ifndef RULES_H
#define RULES_H

#include "Game.h"
#include "Card.h"

// Contains basic rule checks: matching, round over, etc.
class Rules {
  public:
    // Checks if the current move is valid (match on animal or background).
    bool isValid(const Game &) const;

    // Checks if the whole game is over (after N rounds).
    bool gameOver(const Game &) const;

    // Checks if the current round is over (<=1 active player).
    bool roundOver(const Game &) const;

    // Returns the next player (based on index), without changing game state.
    const Player &getNextPlayer(const Game & ) const;
};

#endif
