#ifndef BEHAVIOURS_H
#define BEHAVIOURS_H

#include "Card.h"
#include "Game.h"
#include <cctype>
#include <iostream>
#include <limits>
#include <string>

// Crab - extra turn
class CrabCard : public Card {
  public:
    CrabCard(Card::FaceBackground b) : Card(Card::FaceAnimal::Crab, b) {}

    void applyEffect(Game &g) const override {
        g.setExtraTurn(true);
        std::cout << "CRAB! You get an extra turn!\n";
    }
};

// Penguin - turn a card face down
class PenguinCard : public Card {
  public:
    PenguinCard(Card::FaceBackground b) : Card(Card::FaceAnimal::Penguin, b) {}

    void applyEffect(Game &g) const override {
        // Skip the penguin if it is the first card flipped
        if (!g.getPreviousCard()) return;

        std::cout << "PENGUIN! Choose a face-up card to turn down (Letter Number, e.g., A 1 or B 3): ";

        char letter;
        int number;
        Board::Letter l;
        Board::Number n;
        Card *chosen;

        while (true) {
            std::cin.clear();

            std::cin >> letter;
            std::cin >> number;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            letter = static_cast<char>(std::toupper(static_cast<unsigned char>(letter)));

            if (letter < 'A' || letter > 'E' || number < 1 || number > 5) {
                std::cout << "Invalid position! Try again (A-E, 1-5): ";
                continue;
            }

            l = static_cast<Board::Letter>(letter - 'A');
            n = static_cast<Board::Number>(number - 1);

            try {
                chosen = g.getCard(l, n);

                if (!chosen->isFaceUp()) {
                    std::cout << "That card is face down! Choose a face-up card: ";
                    continue;
                }
                if (l == g.getCurrentPosition().first && n == g.getCurrentPosition().second) {
                    std::cout << "You can't turn down the card you just flipped! Try again: ";
                    continue;
                }

                chosen->turnFaceDown();
                std::cout << "Card at " << letter << number << " turned face down!\n";
                break;

            } catch (...) {
                std::cout << "Invalid position! Try again: ";
            }
        }
    }
};

// OCTOPUS - swap with adjacent (fixed so it does NOT corrupt previousCard/currentCard)
class OctopusCard : public Card {
  public:
    OctopusCard(Card::FaceBackground b) : Card(Card::FaceAnimal::Octopus, b) {}

    void applyEffect(Game &g) const override {
        Board::Letter currL = g.getCurrentPosition().first;
        Board::Number currN = g.getCurrentPosition().second;
        int currRow = static_cast<int>(currL);
        int currCol = static_cast<int>(currN);

        std::cout << "OCTOPUS! Choose an adjacent card to swap with (Letter Number, e.g., B 2): ";

        char letter;
        int number;
        Board::Letter l;
        Board::Number n;

        while (true) {
            std::cin >> letter;
            std::cin >> number;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            letter = static_cast<char>(std::toupper(static_cast<unsigned char>(letter)));

            if (letter < 'A' || letter > 'E' || number < 1 || number > 5) {
                std::cout << "Invalid position! Try again: ";
                continue;
            }

            l = static_cast<Board::Letter>(letter - 'A');
            n = static_cast<Board::Number>(number - 1);
            int targetRow = static_cast<int>(l);
            int targetCol = static_cast<int>(n);

            // Must be exactly one step away (up/down/left/right)
            if (std::abs(currRow - targetRow) + std::abs(currCol - targetCol) != 1) {
                std::cout << "Must be directly adjacent! Try again: ";
                continue;
            }

            try {
                // Swap only the board pointers; the current card object is the same,
                // just now located at (l, n). We do NOT change currentCard/previousCard here.
                g.swapCards(currL, currN, l, n);

                g.setCurrentPosition(l, n);

                std::cout << "Swapped with " << letter << number << "!\n";
                break;
            } catch (...) {
                std::cout << "Invalid swap! Try again: ";
            }
        }
    }
};

// Turtle - skip next player
class TurtleCard : public Card {
  public:
    TurtleCard(Card::FaceBackground b) : Card(Card::FaceAnimal::Turtle, b) {}

    void applyEffect(Game &g) const override {
        std::cout << "TURTLE! The next player is skipped!\n";
        g.nextPlayer(); // skip the next player
    }
};

// Walrus - Block a face down card (for the next active player's turn)
class WalrusCard : public Card {
  public:
    WalrusCard(Card::FaceBackground b) : Card(Card::FaceAnimal::Walrus, b) {}

    void applyEffect(Game &g) const override {
        std::cout << "WALRUS! Choose a face-down card to block (Letter Number, e.g., C 4): ";

        char letter;
        int number;
        Board::Letter l;
        Board::Number n;
        Card *chosen;

        while (true) {
            std::cin >> letter;
            std::cin >> number;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            letter = static_cast<char>(std::toupper(static_cast<unsigned char>(letter)));

            if (letter < 'A' || letter > 'E' || number < 1 || number > 5) {
                std::cout << "Invalid position! Try again: ";
                continue;
            }

            l = static_cast<Board::Letter>(letter - 'A');
            n = static_cast<Board::Number>(number - 1);

            try {
                chosen = g.getCard(l, n);

                if (chosen->isFaceUp()) {
                    std::cout << "Card must be face down! Try again: ";
                    continue;
                }

                // Now Game tracks this as "blocked for next active player's turn"
                g.setBlockedPosition(l, n);
                std::cout << "Card at " << letter << number << " is now BLOCKED for the next player!\n";
                break;

            } catch (...) {
                std::cout << "Invalid position! Try again: ";
            }
        }
    }
};

#endif