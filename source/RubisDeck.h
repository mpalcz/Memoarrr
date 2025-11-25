#ifndef RUBISDECK_H
#define RUBISDECK_H

#include <DeckFactory.h>
#include <Rubis.h>

class RubisDeck : public DeckFactory<Rubis> {
  private:
    RubisDeck(); // private constructor, same as CardDeck
  public:
    static RubisDeck &make_RubisDeck(); // method belongs to the class, not an instance
};

#endif