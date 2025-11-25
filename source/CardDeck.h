#ifndef CARDDECK_H
#define CARDDECK_H

#include "Card.h"
#include "DeckFactory.h"

class CardDeck : public DeckFactory<Card> {
  private:
    CardDeck(); // private constructor

  public:
    // only access point to a single CardDeck
    static CardDeck &make_CardDeck();
};

#endif