// DeckFactory.h: Template class for creating decks of cards or rubis.
#ifndef DECKFACTORY_H
#define DECKFACTORY_H

#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

template<typename C> class DeckFactory {
  protected:
    std::vector<C*> deck;

  public:
    virtual ~DeckFactory() { for (auto p : deck) delete p; }

    void shuffle() {
        auto seed = std::chrono::system_clock::now().time_since_epoch().count(); // MAY NEED TO CHANGE!!!!!!!!!
        std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
        pos = 0;
    }

    C* getNext() { 
      if (deck.empty()) return nullptr;
      C* c = deck.back();
      deck.pop_back();
      return c;
    }

    bool isEmpty() const { return deck.empty(); }
};

#endif