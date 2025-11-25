#ifndef CARD_H
#define CARD_H
#include <iostream>
#include <string>

// could also define enums inside the class since it is only being used on cards
enum FaceAnimal { Crab, Penguin, Octopus, Turtle, Walrus };
enum FaceBackground { Red, Green, Purple, Blue, Yellow };

class CardDeck; // forward declaration of card deck

class Card {
    friend class CardDeck; // establish friendship for access to private

  private:
    Card(FaceAnimal a, FaceBackground b); // private constructor
    FaceAnimal animal;
    FaceBackground background;
    static constexpr int numRows = 3; // might need to change for expert levelgames but for now cards are always 3 rows
    bool faceUp = false;

  public:
    int getNRows() const { return numRows; };
    bool isFaceUp() const { return faceUp; }
    bool turnFaceUp();
    bool turnFaceDown();

    // conversions
    operator FaceAnimal() const { return animal; }
    operator FaceBackground() const { return background; }

    // function operator take a row and return a string to output
    std::string operator()(int row) const;

    // make Card "printable"
    friend std::ostream &operator<<(std::ostream &os, const Card &c);
};

#endif