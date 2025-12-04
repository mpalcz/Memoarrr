// Rules.cpp: Implements the Rules class for validating game moves.

#include "Rules.h"
#include "Card.h"
#include "GameParameters.h"

// Checks if currentCard matches previousCard in animal or background.
// Params: g (const Game&).
// Returns: true if valid (or first card), false otherwise.
bool Rules::isValid(const Game &g) const{
    const Card *current = g.getCurrentCard();
    const Card *previous = g.getPreviousCard();

    if (!previous) return true;  // first card of round is always valid

    bool animal_equal = Card::FaceAnimal(*current) == Card::FaceAnimal(*previous);
    bool bg_equal     = Card::FaceBackground(*current) == Card::FaceBackground(*previous);

    return animal_equal || bg_equal;
}

// Checks if number of rounds reached the limit.
// Params: g (const Game&).
// Returns: true if game done.
bool Rules::gameOver(const Game &g) const {
    return g.getRound() >= GameParameters::NumberOfRounds;
}

// Checks if only one (or zero) players are still active.
// Params: g (const Game&).
// Returns: true if round finished.
bool Rules::roundOver(const Game &g) const {
    int activeCount = 0;
    const std::vector<Player>& players = g.getPlayers();
    for (std::size_t i = 0; i < players.size(); ++i) {
        if (players[i].isActive()) activeCount++;
    }
    return activeCount <= 1;
}

// Returns next player in order (without modifying Game).
// Params: g (const Game&).
// Returns: const Player& for the next index.
const Player &Rules::getNextPlayer(const Game &g) const {
    size_t idx = g.getCurrentPlayerIndex();
    return g.getPlayers()[(idx + 1) % g.getPlayers().size()];
}
