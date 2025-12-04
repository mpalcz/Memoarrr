// CardDeck.cpp: Implements the CardDeck class for creating and managing a deck of cards.

#include "CardDeck.h"
#include "GameParameters.h"
#include "Behaviours.h" // For expert derived cards

// Builds all 25 cards for the deck (5 animals x 5 backgrounds).
// Note: we always build the "expert" card types, and let the Game
// decide if effects are used or not based on expertRules flag.
// Params: expertRules (bool, currently unused).
// Returns: CardDeck object.
CardDeck::CardDeck(bool expertRules) {
    (void)expertRules; // just to avoid unused warning, base/expert uses same deck

    for (int animalIdx = 0; animalIdx < GameParameters::NumAnimals; ++animalIdx) {
        for (int backgroundIdx = 0; backgroundIdx < GameParameters::NumBackgrounds; ++backgroundIdx) {
            Card::FaceAnimal animal = static_cast<Card::FaceAnimal>(animalIdx);
            Card::FaceBackground background = static_cast<Card::FaceBackground>(backgroundIdx);

            // always create the proper behaviour card type
            switch (animal) {
                case Card::FaceAnimal::Crab:
                    deck.push_back(new CrabCard(background));
                    break;
                case Card::FaceAnimal::Penguin:
                    deck.push_back(new PenguinCard(background));
                    break;
                case Card::FaceAnimal::Octopus:
                    deck.push_back(new OctopusCard(background));
                    break;
                case Card::FaceAnimal::Turtle:
                    deck.push_back(new TurtleCard(background));
                    break;
                case Card::FaceAnimal::Walrus:
                    deck.push_back(new WalrusCard(background));
                    break;
            }
        }
    }
    shuffle();
}

// singleton pattern to only allow access to a single object of the class
// Params: expertRules (bool, kept for compatibility but ignored inside ctor).
// Returns: reference to static CardDeck.
CardDeck &CardDeck::make_CardDeck(bool expertRules) {
    static CardDeck instance(expertRules);
    return instance;
}