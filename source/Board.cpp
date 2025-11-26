#include <Board.h>
#include <CardDeck.h>

Board::Board() {
    // generate deck of cards and shuffle them
    CardDeck boardDeck = CardDeck::make_CardDeck();
    boardDeck.shuffle();

    // add each card to the board but skip the middle one
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            // if its not the middle spot then add the card (0 indexed here)
            if (!(i == 2 && j == 2)) {
                board[i][j] = *boardDeck.getNext(); // get next returns a card pointer so dereference it
            }
        }
    }
}

bool Board::isFaceUp(const Letter &l, const Number &n) {
    const Card &card = board[l - 1][n - 1]; // enums are 1-indexed so subtract 1 for board position
    return card.isFaceUp();
}

bool Board::turnFaceUp(const Letter &l, const Number &n) {
    Card &card = board[l - 1][n - 1]; // needs to be reference to change the board's card rather than the copy's
    return card.turnFaceUp();
}

bool Board::turnFaceDown(const Letter &l, const Number &n) {
    Card &card = board[l - 1][n - 1];
    return card.turnFaceDown();
}

Card *Board::getCard(const Letter &l, const Number &n) {
    Card *card = &board[l - 1][n - 1];
    return card;
}

void Board::allFacesDown() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++i) {
            // skip middle card again
            if (!(i == 2 && j == 2)) {
                Card card = board[i][j];
                card.turnFaceDown();
            }
        }
    }
}