#include <Card.h>
#include <CardDeck.h>
#include <GameParameters.h>

CardDeck::CardDeck() {
    for (int animalIdx = 0; animalIdx < enumCount<Card::FaceAnimal>(); ++animalIdx) {
        for (int backgroundIdx = 0; backgroundIdx < enumCount<Card::FaceBackground>(); ++backgroundIdx) {
            deck.push_back(new Card((Card::FaceAnimal)animalIdx, (Card::FaceBackground)backgroundIdx));
        }
    }
    shuffle();
}

// singleton pattern to only allow access to a single object of the class
CardDeck &CardDeck::make_CardDeck() {
    static CardDeck instance; // calls the constructor if it doesnt yet exist, otherwise uses existing instance
    return instance;
}