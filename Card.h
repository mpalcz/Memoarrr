#ifndef CARD_H
#define CARD_H
#include <iostream>

enum class FaceAnimal;
enum class FaceBackground;

class CardDeck; // forward declaration of card deck

class Card {

    private:
        friend class CardDeck; // give access to constructor to private constructor
        Card(); // give CardDeck friend access

        FaceAnimal face;
        FaceBackground background;

    public:

        // Conversions
        // Public interface (include conversion operators to type FaceAnimal and FaceBackground)

        int getNRows() const;

        // Friend functions
        friend std::ostream& operator<<(std::ostream& os, const Card& obj);
};

#endif