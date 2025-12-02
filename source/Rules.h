#ifndef RULES_H
#define RULES_H

#include "Game.h"
#include "Card.h"

class Rules {
  public:
    bool isValid(const Game &) const;
    bool gameOver(const Game &) const;
    bool roundOver(const Game &) const;
    const Player &getNextPlayer(const Game &) const;
};

#endif