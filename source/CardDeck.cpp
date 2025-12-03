// CardDeck.cpp: Implements the CardDeck class for creating and managing a deck of cards.
#include "CardDeck.h"
#include "GameParameters.h"
#include "Behaviours.h" // For expert derived cards

CardDeck::CardDeck(bool expertRules) {
    for (int animalIdx = 0; animalIdx < GameParameters::NumAnimals; ++animalIdx) {
        for (int backgroundIdx = 0; backgroundIdx < GameParameters::NumBackgrounds; ++backgroundIdx) {
            FaceAnimal animal = (Card::FaceAnimal)animalIdx;
            FaceBackground background = (Card::FaceBackground)backgroundIdx;
            if (expertRules) {
                switch (animal) {
                    case FaceAnimal::Crab: deck.push_back(new CrabCard(background)); break;
                    case FaceAnimal::Penguin: deck.push_back(new PenguinCard(background)); break;
                    case FaceAnimal::Octopus: deck.push_back(new OctopusCard(background)); break;
                    case FaceAnimal::Turtle: deck.push_back(new TurtleCard(background)); break;
                    case FaceAnimal::Walrus: deck.push_back(new WalrusCard(background)); break;
                }
            } else {
                deck.push_back(new Card(animal, background));
            }
        }
    }
    shuffle();
}

// singleton pattern to only allow access to a single object of the class
CardDeck &CardDeck::make_CardDeck(bool expertRules) {
    static CardDeck instance(expertRules);
    return instance;
}