// CardDeck.h
#ifndef CARDDECK_H
#define CARDDECK_H

#include "DeckFactory.h"
#include "Card.h"

// Factory that builds the 25 card deck (base or expert).
class CardDeck : public DeckFactory<Card> {
  private:
    // ==== Constructor ====
    CardDeck(bool expertRules);

  public:
    // Factory (singleton-style)
    // Builds or returns the single shared CardDeck.
    // Params: expertRules (bool) - if true use derived behaviour cards.
    // Returns: reference to static deck.
    static CardDeck& make_CardDeck(bool expertRules = false);
};

#endif
