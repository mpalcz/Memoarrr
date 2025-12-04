// RubisDeck.cpp: Implements the RubisDeck class for creating and managing a deck of rubies.

#include "Rubis.h"
#include "RubisDeck.h"
#include "GameParameters.h"

// constructor
// Builds Rubis tokens based on the distribution in GameParameters.
// Params: none.
// Returns: RubisDeck object.
RubisDeck::RubisDeck() {
    for (std::size_t value = 1; value < GameParameters::RubisDistribution.size(); ++value) {
        int count = GameParameters::RubisDistribution[value];
        for (int i = 0; i < count; ++i) {
            deck.push_back(new Rubis(static_cast<int>(value)));
        }
    }
    shuffle();
}

// Returns the singleton instance of RubisDeck.
// Params: none.
// Returns: reference to static RubisDeck.
RubisDeck &RubisDeck::make_RubisDeck() {
    static RubisDeck instance;
    return instance;
}
