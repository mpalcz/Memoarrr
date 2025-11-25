#include <Card.h>
#include <CardDeck.h>

CardDeck::CardDeck() {
    // Create one of each card
    std::vector<Card> cards; // to be passed to deck class variable

    for (int a = 0; a < 5; ++a) {
        for (int c = 0; c < 5; ++c) {
            Card card = Card((FaceAnimal)a, (FaceBackground)c);
            cards.push_back(card); // default copy constructor is fine since no pointers
        }
    }

    // set class variables (inherited from DeckFactory)
    deck = cards;
    current = deck.begin();
}

// singleton pattern to only allow access to a single object of the class
CardDeck &CardDeck::make_CardDeck() {
    static CardDeck instance; // calls the constructor if it doesnt yet exist, otherwise uses existing instance
    return instance;
}