// RubisDeck.cpp: Implements the RubisDeck class for creating and managing a deck of rubis.

#include "Rubis.h"
#include "RubisDeck.h"
#include <vector>
#include <GameParameters.h>

// constructor
RubisDeck::RubisDeck() {
    // Iterate over the rubisValues map defined in the game parameters
    for (std::size_t value = 1; value < GameParameters::RubisDistribution.size(); ++value) {
        int count = GameParameters::RubisDistribution[value];
        for (int i = 0; i < count; ++i) {
            deck.push_back(new Rubis(value));
        }
    }
    shuffle();
}

RubisDeck &RubisDeck::make_RubisDeck() {
    static RubisDeck instance;
    return instance;
}
