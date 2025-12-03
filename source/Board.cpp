// Board.cpp: Implements the Board class for managing the game board display and card states.

#include "Board.h"
#include "CardDeck.h"
#include "Exceptions.h"

// Validates if a position is within board bounds and not the center.
// Params: l (Letter enum), n (Number enum).
// Throws: OutOfRange if invalid.
void Board::validatePosition(const Letter &l, const Number &n) const {
    int row = toIndex<Board::Letter>(l), column = toIndex<Board::Number>(n);
    std::tuple<int, int> cardPosition(row, column);
    if (row < 0 || row >= GameParameters::BoardSize || column < 0 || column >= GameParameters::BoardSize || cardPosition == GameParameters::CenterPosition) {
        throw OutOfRange();
    }
};

// Constructs a Board by populating it with shuffled cards from CardDeck.
// Throws: NoMoreCards if deck is empty.
Board::Board() {
    CardDeck &boardDeck = CardDeck::make_CardDeck();
    for (int i = 0; i < GameParameters::BoardSize; ++i) {
        for (int j = 0; j < GameParameters::BoardSize; ++j) {
            if (i == GameParameters::CenterRow && j == GameParameters::CenterCol) {
                board[i][j] = std::make_unique<Card>(); // blank center
            } else {
                Card* card = boardDeck.getNext();
                if (!card) throw NoMoreCards();
                board[i][j] = std::unique_ptr<Card>(card);
            }
        }
    }
}

// Gets the card at a position (non-const version).
// Params: l (Letter), n (Number).
// Returns: Pointer to Card.
// Throws: OutOfRange if invalid.
Card *Board::getCard(const Letter &l, const Number &n) {
    validatePosition(l, n);
    int row = toIndex<Board::Letter>(l), column = toIndex<Board::Number>(n);
    return board[row][column].get();
}

// Gets the card at a position (const version).
// Params: l (Letter), n (Number).
// Returns: Const pointer to Card.
// Throws: OutOfRange if invalid.
const Card *Board::getCard(const Letter &l, const Number &n) const {
    validatePosition(l, n);
    int row = toIndex<Board::Letter>(l), column = toIndex<Board::Number>(n);
    return board[row][column].get();
}

// Turns a card face up if it was down.
// Params: l (Letter), n (Number).
// Returns: true if flipped, false if already up.
// Throws: OutOfRange if invalid.
bool Board::turnFaceUp(const Letter &l, const Number &n) {
    Card *card = getCard(l, n);
    if (card->isFaceUp()) return false;
    card->turnFaceUp();
    return true;
}

// Turns a card face down if it was up.
// Params: l (Letter), n (Number).
// Returns: true if flipped, false if already down.
// Throws: OutOfRange if invalid.
bool Board::turnFaceDown(const Letter &l, const Number &n) {
    Card *card = getCard(l, n);
    if (!card->isFaceUp()) return false;
    card->turnFaceDown();
    return true;
}

// Sets a card at a position.
// Params: l (Letter), n (Number), c (pointer to Card).
// Throws: OutOfRange if invalid.
void Board::setCard(const Letter &l, const Number &n, Card *c) {
    validatePosition(l, n);
    int row = toIndex<Board::Letter>(l), column = toIndex<Board::Number>(n);
    board[row][column].reset(c);
}

// Turns all cards face down (except center).
void Board::allFacesDown() {
    for (int i = 0; i < GameParameters::BoardSize; ++i) {
        for (int j = 0; j < GameParameters::BoardSize; ++j) {
            if (!(i == GameParameters::CenterRow && j == GameParameters::CenterCol)) {
                board[i][j]->turnFaceDown();
            }
        }
    }
}

// Prints the board line by line.
// Params: os (output stream), b (const Board).
// Returns: os for chaining.
std::ostream& operator<<(std::ostream& os, const Board& b) {
    for (int row = 0; row < GameParameters::BoardSize; ++row) {
        for (int cardRow = 0; cardRow < GameParameters::NumRowsCard; ++cardRow) {
            os << ((cardRow == GameParameters::NumRowsCard/2) ? std::string(1, 'A' + row) : " ");
            os << std::string(GameParameters::BoardPadding, ' ');
            for (int col = 0; col < GameParameters::BoardSize; ++col) {
                const Card* card = b.board[row][col].get();
                os << (*card)(cardRow);
                if (col < 4) os << ' ';
            }
            os << '\n';
        }
        os << std::string(GameParameters::BoardPadding, '\n');
    }
    os << std::string(GameParameters::BoardPadding, ' ') << " 1   2   3   4   5\n";
    return os;
}