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
    size_t pos = 0;

  public:
    virtual ~DeckFactory() { for (auto p : deck) delete p; }

    void shuffle() {
        auto seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::shuffle(deck.begin(), deck.end(), std::default_random_engine(seed));
        pos = 0;
    }

    C* getNext() { return pos < deck.size() ? deck[pos++] : nullptr; }

    bool isEmpty() const { return pos >= deck.size(); }
};

#endif