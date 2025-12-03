// Card.h
#ifndef CARD_H
#define CARD_H

#include "GameParameters.h"
#include <iostream>
#include <string>

// Forward declarations
class CardDeck;
class Board;
class Game;

class Card {
  friend class CardDeck;
  friend class Board; // So Board can construct blank card

  public:
    // Card Enums
    enum class FaceAnimal { Crab, Penguin, Octopus, Turtle, Walrus };
    enum class FaceBackground { Red, Green, Purple, Blue, Yellow };

  private:
    // Instance variables
    FaceAnimal animal;
    FaceBackground background;
    bool faceUp = false;

    // Constructors
  protected:
    Card(FaceAnimal a, FaceBackground b) : animal(a), background(b) {} // private constructor
   
  public:
    virtual ~Card() = default; // virtual destructor

    // Conversion operators
    operator FaceAnimal() const { return animal; }
    operator FaceBackground() const { return background; }

    // function operator take a row and return a string to output
    std::string operator()(int row) const;

    bool isFaceUp() const { return faceUp; }
    void turnFaceUp() { faceUp = true; }
    void turnFaceDown() { faceUp = false; }

    static constexpr int getNRows() { return GameParameters::NumRowsCard; }

    // For expert modes
    virtual void applyEffect(Game&) const {}

    // make Card "printable"
    friend std::ostream &operator<<(std::ostream &os, const Card &c);

};

#endif