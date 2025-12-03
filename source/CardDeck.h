#ifndef CARDDECK_H
#define CARDDECK_H

#include "DeckFactory.h"
#include "Card.h"

class CardDeck : public DeckFactory<Card> {
    CardDeck(bool expertRules);
public:
    static CardDeck& make_CardDeck(bool expertRules = false);
};

#endif