// DeckFactory.h: Template class for creating decks of cards or rubis.

#ifndef DECKFACTORY_H
#define DECKFACTORY_H

#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

// Simple generic deck holder + shuffler.
// Template param C is the card/rubis type.
template<typename C> class DeckFactory {
  protected:
    // ==== Instance variables ====
    std::vector<C*> deck;

  public:
    // ==== Destructor ====
    // Deletes all remaining pointers in deck.
    virtual ~DeckFactory() {
        for (auto p : deck) delete p;
    }

    // Shuffles the deck using a time-based seed.
    // Params: none.
    // Returns: nothing.
    void shuffle() {
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(deck.begin(), deck.end(), std::default_random_engine(static_cast<unsigned int>(seed)));
    }

    // Pops and returns the next card from the deck (top/back).
    // Params: none.
    // Returns: pointer to C, or nullptr if empty.
    C* getNext() {
      if (deck.empty()) return 0;
      C* c = deck.back();
      deck.pop_back();
      return c;
    }

    // Checks if the deck is empty.
    // Params: none.
    // Returns: true if empty.
    bool isEmpty() const { return deck.empty(); }
};

#endif
