// Behaviors.h (new for expert rules polymorphism)
#ifndef BEHAVIOURS_H
#define BEHAVIOURS_H

#include "Card.h"
#include "Game.h"
#include "Exceptions.h"
#include <iostream>
#include <cctype>

class CrabCard : public Card {
public:
    CrabCard(Card::FaceBackground b) : Card(Card::FaceAnimal::Crab, b) {}
    void applyEffect(Game& g) const override {
        g.setExtraTurn(true);
    }
};

class PenguinCard : public Card {
public:
    PenguinCard(Card::FaceBackground b) : Card(Card::FaceAnimal::Penguin, b) {}
    void applyEffect(Game& g) const override {
        if (!g.getPreviousCard()) return;  // No action if first
        std::cout << "Penguin: choose face-up card to turn down (L N): ";
        char let; int num;
        std::cin >> let >> num;
        let = toupper(let);
        Board::Letter l = static_cast<Board::Letter>(let - 'A');
        Board::Number n = static_cast<Board::Number>(num - 1);
        try {
            while (!g.turnFaceDown(l, n) || (l == g.getCurrentPosition().first && n == g.getCurrentPosition().second)) {
                std::cout << "Invalid (must be face up, not current), choose again: ";
                std::cin >> let >> num;
                let = toupper(let);
                l = static_cast<Board::Letter>(let - 'A');
                n = static_cast<Board::Number>(num - 1);
            }
        } catch (const OutOfRange&) {
            std::cout << "Invalid position - no change.\n";
        }
    }
};

class OctopusCard : public Card {
public:
    OctopusCard(Card::FaceBackground b) : Card(Card::FaceAnimal::Octopus, b) {}
    void applyEffect(Game& g) const override {
        auto [cl, cn] = g.getCurrentPosition();
        int cr = static_cast<int>(cl), cc = static_cast<int>(cn);
        std::cout << "Octopus: choose adjacent to swap (L N): ";
        char let; int num;
        std::cin >> let >> num;
        let = toupper(let);
        Board::Letter l = static_cast<Board::Letter>(let - 'A');
        Board::Number n = static_cast<Board::Number>(num - 1);
        int ar = static_cast<int>(l), ac = static_cast<int>(n);
        try {
            while (!((std::abs(ar - cr) + std::abs(ac - cc) == 1) && ar >= 0 && ar < 5 && ac >= 0 && ac < 5 && !(ar == 2 && ac == 2))) {
                std::cout << "Invalid adjacent, choose again: ";
                std::cin >> let >> num;
                let = toupper(let);
                l = static_cast<Board::Letter>(let - 'A');
                n = static_cast<Board::Number>(num - 1);
                ar = static_cast<int>(l); ac = static_cast<int>(n);
            }
            Card* curr = g.getCard(cl, cn);
            Card* adj = g.getCard(l, n);
            g.setCard(cl, cn, adj);
            g.setCard(l, n, curr);
        } catch (const OutOfRange&) {
            std::cout << "Invalid position - no swap.\n";
        }
    }
};

class TurtleCard : public Card {
public:
    TurtleCard(Card::FaceBackground b) : Card(Card::FaceAnimal::Turtle, b) {}
    void applyEffect(Game& g) const override {
        g.nextPlayer();  // Skip next
    }
};

class WalrusCard : public Card {
public:
    WalrusCard(Card::FaceBackground b) : Card(Card::FaceAnimal::Walrus, b) {}
    void applyEffect(Game& g) const override {
        std::cout << "Walrus: choose face-down to block (L N): ";
        char let; int num;
        std::cin >> let >> num;
        let = toupper(let);
        Board::Letter l = static_cast<Board::Letter>(let - 'A');
        Board::Number n = static_cast<Board::Number>(num - 1);
        try {
            while (g.isFaceUp(l, n)) {
                std::cout << "Invalid (must be face down), choose again: ";
                std::cin >> let >> num;
                let = toupper(let);
                l = static_cast<Board::Letter>(let - 'A');
                n = static_cast<Board::Number>(num - 1);
            }
            g.setBlockedPosition(l, n);
        } catch (const OutOfRange&) {
            std::cout << "Invalid position - no block.\n";
        }
    }
};

#endif