#include <Rubis.h>
#include <RubisDeck.h>
#include <vector>

// constructor
RubisDeck::RubisDeck() {
    std::vector<Rubis> cards;          // will be passed to deck class variable
    int arr[] = {1, 1, 1, 2, 2, 3, 4}; // rubi value for cards (3 cards with 1 etc.)

    for (int elem : arr) {
        Rubis card(elem);
        cards.push_back(card);
    }

    deck = cards;
    current = deck.begin();
}

RubisDeck &RubisDeck::make_RubisDeck() {
    static RubisDeck instance;
    return instance;
}