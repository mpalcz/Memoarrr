// Behaviors.h (new for expert rules polymorphism)
#ifndef BEHAVIOURS_H
#define BEHAVIOURS_H

#include "Card.h"
#include "Game.h"
#include "Exceptions.h"
#include "UserInput.h"
#include <string>
#include <iostream>
#include <cctype>

class CrabCard : public Card {
public:
    CrabCard(Card::FaceBackground b) : Card(Card::FaceAnimal::Crab, b) {}
    std::string applyEffect(Game& g) const override {
        std::cout << "Crab card in effect! Turn over another card!" << std::endl;
        g.setExtraTurn(true);
        return "";
    }
};

class PenguinCard : public Card {
public:
    PenguinCard(Card::FaceBackground b) : Card(Card::FaceAnimal::Penguin, b) {}
    std::string applyEffect(Game& g) const override {
        if (!g.getPreviousCard()) return "Penguin card has no effect for the first turn!";  // No action if first card turned over
        std::cout << "Penguin card in effect! Choose a face-up card to turn down!" << std::endl;
        bool validCard = false;
        while (!validCard) {
            auto [l, n] = getUserInputCard(g);
            if (!g.isFaceUp(l, n)) {
                std::cout << "Card chosen must be face-up. Try again" << std::endl;
            } else if (l == g.getCurrentPosition().first && n == g.getCurrentPosition().second) {
                std::cout << "Card chosen cannot be current position. Try again" << std::endl;
            } else {
                g.turnFaceDown(l, n);
                validCard = true;
            }
            
        }
        return "Card turned down!";
    }

};

class OctopusCard : public Card {
public:
    OctopusCard(Card::FaceBackground b) : Card(Card::FaceAnimal::Octopus, b) {}
    std::string applyEffect(Game& g) const override {
        auto [cl, cn] = g.getCurrentPosition();
        int currentLetter = static_cast<int>(cl), currentNumber = static_cast<int>(cn);

        std::cout << "Octopus card in effect! Choose an adjacent card to swap!" << std::endl;
        bool validCard = false;
        while (!validCard) {
            auto [l, n] = getUserInputCard(g);
            int chosenLetter = static_cast<int>(l), chosenNumber = static_cast<int>(n);
            if (!(((currentLetter == chosenLetter) && (abs(currentNumber - chosenNumber) == 1)) || ((currentNumber == chosenNumber) && (abs(currentLetter - chosenLetter) == 1)))) {
                std::cout << "Card chosen must be adjacent. Try again" << std::endl;
            } else {
                g.swapCards(cl, cn, l, n);
                validCard = true;
            } 
        }
        return "Card swapped!";
    }
};

class TurtleCard : public Card {
public:
    TurtleCard(Card::FaceBackground b) : Card(Card::FaceAnimal::Turtle, b) {}
    std::string applyEffect(Game& g) const override {
        std::cout << "Turtle card in effect! Skip the next player!" << std::endl;
        g.nextPlayer();  // Skip next
        return "";
    }
};

class WalrusCard : public Card {
public:
    WalrusCard(Card::FaceBackground b) : Card(Card::FaceAnimal::Walrus, b) {}
    std::string applyEffect(Game& g) const override {
        std::cout << "Walrus card in effect! Choose a face-down card to block!" << std::endl;
        bool validCard = false;
        while (!validCard) {
            auto [l, n] = getUserInputCard(g);
            if (g.isFaceUp(l, n)) {
                std::cout << "Card chosen must be face-down. Try again" << std::endl;
            } else {
                g.setBlockedPosition(l, n);
                validCard = true;
            } 
        }
        return "Card blocked!";
    }
};

#endif