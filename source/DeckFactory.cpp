#include "DeckFactory.h"
#include <random>

template <typename C> void DeckFactory<C>::shuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
    current = deck.begin();
}

template <typename C> C *DeckFactory<C>::getNext() {
    if (current == deck.end()) return nullptr;
    return *current++;
}