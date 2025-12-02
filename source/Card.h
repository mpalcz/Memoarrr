#ifndef CARD_H
#define CARD_H

#include <iostream>
#include <string>

// could also define enums inside the class since it is only being used on cards

class CardDeck; // forward declaration of card deck

class Card {
  friend class CardDeck; // establish friendship for access to private

  public:
  // Card Enums
    enum class FaceAnimal { Crab, Penguin, Octopus, Turtle, Walrus, COUNT };
    enum class FaceBackground { Red, Green, Purple, Blue, Yellow, COUNT };

  private:
    // Constructors 
    Card(FaceAnimal a, FaceBackground b) : animal(a), background(b) {} // private constructor
    Card() : isBlank(true) {}             // when using default constructor, make a blank card
    
    // Instance variables
    FaceAnimal animal;
    FaceBackground background;
    static constexpr int numRows = 3; // might need to change for expert levelgames but for now cards are always 3 rows
    bool faceUp = false;
    bool isBlank = false; // for printing the middle card in the board

  public:
    
    int getNRows() const { return numRows; }
    bool isFaceUp() const { return faceUp; }
    void turnFaceUp() { faceUp = true; }
    void turnFaceDown() { faceUp = false; }
  

    // Conversion operators
    operator FaceAnimal() const { return animal; }
    operator FaceBackground() const { return background; }

    // function operator take a row and return a string to output
    std::string operator()(int row) const;

    // make Card "printable"
    friend std::ostream &operator<<(std::ostream &os, const Card &c);

};

#endif