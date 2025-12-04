// Board.h
#ifndef BOARD_H
#define BOARD_H

#include "Card.h"
#include "GameParameters.h"
#include <iostream>

// Class that holds all the cards and handles the visual grid.
class Board {

  public:
    // Enums
    enum class Letter { A, B, C, D, E };
    enum class Number { One, Two, Three, Four, Five };

    // Enum helper functions
    template<typename Enum>
    static int toIndex(Enum e) { return static_cast<int>(e); }

    template <typename Enum>
    static Enum getEnumAt(int i) {
        if (i < 0 || i >= GameParameters::BoardSize) throw std::out_of_range("Enum index out of range");
        return static_cast<Enum>(i);
    }
   
    // Constructor and Destructor
    Board();
    ~Board();

    //Public interface
    bool isFaceUp(const Letter &l, const Number &n) const;
    bool turnFaceUp(const Letter &, const Number &);
    bool turnFaceDown(const Letter &, const Number &);
    Card *getCard(const Letter &, const Number &);
    const Card *getCard(const Letter &, const Number &) const;
    void setCard(const Letter &, const Number &, Card *);
    void swapCards(const Letter &l1, const Number &n1, const Letter &l2, const Number &n2);
    void allFacesDown();

    //Operators
    friend std::ostream &operator<<(std::ostream &os, const Board &b);

  private:
    //Instance variables
    Card* board[GameParameters::BoardSize][GameParameters::BoardSize] = {}; // 5x5 board of cards

    // Helpers
    void validatePosition(const Letter&, const Number&) const;
};

#endif