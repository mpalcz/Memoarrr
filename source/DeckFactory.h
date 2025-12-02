#ifndef DECKFACTORY_H
#define DECKFACTORY_H
#include <algorithm> // required for std::random_shuffle
#include <vector>

// Potentially add virtual functions (pure virtual functions)
template <typename C> class DeckFactory {

  protected: // so child classes can access these
    DeckFactory(std::vector<C*> &d) : deck(d), current(deck.begin()); // IS THIS NECESSARY
    DeckFactory() : current(deck.begin());
    virtual ~DeckFactory() { for (auto p : deck) delete p; }
    
    // INSTANCE VARIABLES
    std::vector<C*> deck;                       // deck stored as a vector of C
    typename std::vector<C*>::iterator current; // use an iterator for easier implemetation with vectors

  public:
    void shuffle();
    C *getNext();
    bool isEmpty() const { return current == deck.end(); }
    // do a make_deck function as a virtual function
};

#endif
