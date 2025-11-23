#include "DeckFactory.h"

template <typename C> void DeckFactory<C>::shuffle() {
    std::shuffle(deck.begin(), deck.end()); // random_shuffle was removed in newer C++ versions
    current = deck.begin();
}
template <typename C> C *DeckFactory<C>::getNext() {
    if (current == deck.end()) {
        return nullptr;
    }
    // return the current card then increment the pointer
    return &(*current++); // derefernce the iterator to get the actual object in the vector, then take the address (giving you the pointer)
}
