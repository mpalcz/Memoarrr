#ifndef CARD_H
#define CARD_H

#include "GameParameters.h"
#include <iostream>
#include <string>

// Forward declarations
class CardDeck;
class Game;

class Card {
  friend class CardDeck;

  public:
    // Card Enums
    enum class FaceAnimal { Crab, Penguin, Octopus, Turtle, Walrus };
    enum class FaceBackground { Red, Green, Purple, Blue, Yellow };

  protected: // Protected for potential derived classes in expert mode (MAY NEED TO CHANGE)
    Card(FaceAnimal a, FaceBackground b) : animal(a), background(b) {}

  private:
    // Instance variables
    FaceAnimal animal;
    FaceBackground background;
    bool faceUp = false;

    // Constructors
    //Card(FaceAnimal a, FaceBackground b) : animal(a), background(b) {} // private constructor !!!!!!!!!!!!!!!!!!! MAY NEED TO REIMPLEMENT

  public:
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
    virtual void applyEffect(Game& g) const {}

    // make Card "printable"
    friend std::ostream &operator<<(std::ostream &os, const Card &c);

};

#endif
