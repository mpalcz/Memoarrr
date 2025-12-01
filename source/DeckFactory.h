#ifndef DECKFACTORY_H
#define DECKFACTORY_H
#include <algorithm> // required for std::random_shuffle
#include <vector>

// Potentially add virtual functions (pure virtual functions)
template <typename C> class DeckFactory {
  protected: // so child classes can access these
    DeckFactory(std::vector<C> &d) : deck(d), current(deck.begin());

    // could maybe make these private actually
    std::vector<C*> deck;                       // deck stored as a vector of C
    typename std::vector<C*>::iterator current; // use an iterator for easier implemetation with vectors

  public:
    void shuffle();
    C *getNext();
    bool isEmpty() const { return current == deck.end(); }
};

#endif
