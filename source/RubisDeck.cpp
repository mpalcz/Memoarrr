#include <Rubis.h>
#include <RubisDeck.h>
#include <vector>
#include <GameParameters.h>

// constructor
RubisDeck::RubisDeck() {
    // Iterate over the rubisValues map defined in the game parameters
    for (const auto& [value, count] : Game::rubisValues) {
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

// for printing rubis
std::ostream &operator<<(std::ostream &os, const Rubis &r) {
    os << r.numRubis;
    return os;
}