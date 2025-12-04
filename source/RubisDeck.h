// RubisDeck.h
#ifndef RUBISDECK_H
#define RUBISDECK_H

#include "DeckFactory.h"
#include "Rubis.h"

// Deck of Rubis tokens, built from GameParameters distribution.
class RubisDeck : public DeckFactory<Rubis> {
  private:
    // private constructor, same as CardDeck
    RubisDeck();

  public:
    // Builds or returns the single shared RubisDeck.
    // Params: none.
    // Returns: reference to static RubisDeck.
    static RubisDeck &make_RubisDeck(); // method belongs to the class, not an instance (singleton pattern)
};

#endif
