// Rules.cpp: Implements the Rules class for validating game moves.

#include "Rules.h"
#include "Card.h"
#include "GameParameters.h"

bool Rules::isValid(const Game &g) const{
    const Card *current = g.getCurrentCard();
    const Card *previous = g.getPreviousCard();

    if (!previous) return true;  // first card of round is always valid

    // equal if either the background colour or the animal are the same
    bool animal_equal = Card::FaceAnimal(*current) == Card::FaceAnimal(*previous);
    bool bg_equal = Card::FaceBackground(*current) == Card::FaceBackground(*previous);

    return animal_equal || bg_equal;
}

bool Rules::gameOver(const Game &g) const { return g.getRound() >= GameParameters::NumberOfRounds; }

bool Rules::roundOver(const Game &g) const {
    int activeCount = 0;
    for (const auto& player : g.getPlayers()) {
        if (player.isActive()) activeCount++;
    }
    return activeCount <= 1;  // round over when only one (or zero) player remains
}

const Player &Rules::getNextPlayer(const Game &g) const {
    size_t idx = g.getCurrentPlayerIndex();
    return g.getPlayers()[(idx + 1) % g.getPlayers().size()];
}