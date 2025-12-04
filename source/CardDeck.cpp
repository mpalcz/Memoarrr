// CardDeck.cpp: Implements the CardDeck class for creating and managing a deck of cards.

#include "Behaviours.h"     // make sure derived cards are visible first
#include "CardDeck.h"
#include "GameParameters.h"

// Builds all 25 cards, depending on expert rules flag.
// Params: expertRules (bool).
// Returns: CardDeck object.
CardDeck::CardDeck(bool expertRules) {
    for (int animalIdx = 0; animalIdx < GameParameters::NumAnimals; ++animalIdx) {
        for (int backgroundIdx = 0; backgroundIdx < GameParameters::NumBackgrounds; ++backgroundIdx) {
            Card::FaceAnimal animal = static_cast<Card::FaceAnimal>(animalIdx);
            Card::FaceBackground background = static_cast<Card::FaceBackground>(backgroundIdx);

            if (expertRules) {
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
            } else {
                deck.push_back(new Card(animal, background));
            }
        }
    }
    shuffle();
}

// singleton pattern to only allow access to a single object of the class
// Params: expertRules (bool).
// Returns: reference to static CardDeck.
CardDeck &CardDeck::make_CardDeck(bool expertRules) {
    static CardDeck instance(expertRules);
    return instance;
}
