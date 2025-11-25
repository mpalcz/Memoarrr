#include <Board.h>
#include <CardDeck.h>

Board::Board() {
    // generate deck of cards and shuffle them
    CardDeck boardDeck = CardDeck::make_CardDeck();
    boardDeck.shuffle();

    // add each card to the board but skip the middle one
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++i) {
            // if its not the middle spot then add the card
            if (!(i == 3 && j == 3)) {
                board[i][j] = *boardDeck.getNext(); // get next returns a card pointer so dereference it
            }
        }
    }
}

bool Board::isFaceUp(const Letter &l, const Number &n) {
    Card card = board[l - 1][n - 1]; // enums are 1-indexed (start at 1)
    return card.isFaceUp();
}

bool Board::turnFaceUp(const Letter &l, const Number &n) {
    Card card = board[l - 1][n - 1];
    return card.turnFaceUp();
}

bool Board::turnFaceDown(const Letter &l, const Number &n) {
    Card card = board[l - 1][n - 1];
    return card.turnFaceDown();
}

Card Board::*getCard(const Letter &l, const Number &n) {}

void Board::allFacesDown() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++i) {
            // skip middle card again
            if (!(i == 3 && j == 3)) {
                Card card = board[i][j];
                card.turnFaceDown();
            }
        }
    }
}