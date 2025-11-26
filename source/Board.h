#ifndef BOARD_H
#define BOARD_H
#include <Card.h>

class Board {
  private:
    Card board[5][5]; // 5x5 board of cards

  public:
    // enums for coordinate system
    // public because Board needs access (could be a friend function I suppose)
    enum Letter { A = 1, B = 2, C = 3, D = 4, E = 5 };
    enum Number { One = 1, Two = 2, Three = 3, Four = 4, Five = 5 }; // enum elements have to be identifiers not integers

    Board(); // public constructor bc idk why not
    bool isFaceUp(const Letter &, const Number &);
    bool turnFaceUp(const Letter &, const Number &);
    bool turnFaceDown(const Letter &, const Number &);
    Card *getCard(const Letter &, const Number &);
    void allFacesDown();
    friend std::ostream &operator<<(std::ostream &os, const Board &b);
};

#endif