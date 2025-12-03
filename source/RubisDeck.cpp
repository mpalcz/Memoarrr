// RubisDeck.cpp
#include "Rubis.h"
#include "RubisDeck.h"
#include "GameParameters.h"

RubisDeck::RubisDeck() {
    for (std::size_t value = 1; value < GameParameters::RubisDistribution.size(); ++value) {
        int count = GameParameters::RubisDistribution[value];
        for (int i = 0; i < count; ++i) {
            deck.push_back(new Rubis(static_cast<int>(value)));
        }
    }
    shuffle();
}

RubisDeck &RubisDeck::make_RubisDeck() {
    static RubisDeck instance;
    return instance;
}