#ifndef BOARD_H
#define BOARD_H
#include <Card.h>
#include <GameParameters.h>

class Board {

  private:
    Card* board[Game::boardSize][Game::boardSize]; // 5x5 board of cards
    bool checkPositionValidity(int, int) const;

  public:
    // enums for coordinate system
    // public because Board needs access (could be a friend function I suppose)
    enum class Letter { A, B, C, D, E };
    enum class Number { One, Two, Three, Four, Five }; // enum elements have to be identifiers not integers
    
    template<typename Enum>
    int toIndex(Enum e) const { return static_cast<int>(e); }

    // Constructor
    Board(); // public constructor bc idk why not
    bool isFaceUp(const Letter &, const Number &) const;
    bool turnFaceUp(const Letter &, const Number &);
    bool turnFaceDown(const Letter &, const Number &);
    Card *getCard(const Letter &, const Number &);
    void setCard(const Letter &, const Number &, Card *);
    void allFacesDown();

    friend std::ostream &operator<<(std::ostream &os, const Board &b);
};

#endif