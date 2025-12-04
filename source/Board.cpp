// Board.cpp: Implements the Board class for managing the game board display and card states.

#include "Board.h"
#include "CardDeck.h"
#include "Exceptions.h"

// Validates if a position is within board bounds and not the center.
// Params: l (Letter enum), n (Number enum).
// Throws: OutOfRange if invalid.
void Board::validatePosition(const Letter &l, const Number &n) const {
    int row = toIndex<Board::Letter>(l), column = toIndex<Board::Number>(n);
    if (row < 0 || row >= GameParameters::BoardSize || column < 0 || column >= GameParameters::BoardSize
        || (row == GameParameters::CenterRow && column == GameParameters::CenterCol)) {
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
                board[i][j] = 0; // blank center
            } else {
                board[i][j] = boardDeck.getNext();
                if (!board[i][j]) throw NoMoreCards();
            }
        }
    }
}

// Destructs a Board, deleting all dynamically allocated Cards
// Params: none.
// Returns: nothing.
Board::~Board() {
    for (int i = 0; i < GameParameters::BoardSize; ++i) {
        for (int j = 0; j < GameParameters::BoardSize; ++j) {
            delete board[i][j];
        }
    }
}

// Checks if the card at a position is faced up
// Params: l (Letter), n (Number).
// Returns: boolean indicating if the card is faced up
// Throws: OutOfRange if parameters are invalid.
bool Board::isFaceUp(const Letter &l, const Number &n) const {
    validatePosition(l, n);
    return getCard(l, n)->isFaceUp();
}

// Gets the card at a position (non-const version).
// Params: l (Letter), n (Number).
// Returns: Pointer to Card.
// Throws: OutOfRange if invalid.
Card *Board::getCard(const Letter &l, const Number &n) {
    validatePosition(l, n);
    return board[toIndex<Letter>(l)][toIndex<Number>(n)];
}

// Gets the card at a position (const version).
// Params: l (Letter), n (Number).
// Returns: Const pointer to Card.
// Throws: OutOfRange if invalid.
const Card *Board::getCard(const Letter &l, const Number &n) const {
    validatePosition(l, n);
    return board[toIndex<Letter>(l)][toIndex<Number>(n)];
}

// Turns a card face up if it was down.
// Params: l (Letter), n (Number).
// Returns: true if flipped, false if already up.
// Throws: OutOfRange if invalid.
bool Board::turnFaceUp(const Letter &l, const Number &n) {
    validatePosition(l, n);
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
    validatePosition(l, n);
    Card *card = getCard(l, n);
    if (!card->isFaceUp()) return false;
    card->turnFaceDown();
    return true;
}

// Sets a card at a position, deleting the old one if present.
// Params: l (Letter), n (Number), c (pointer to Card).
// Returns: nothing.
// Throws: OutOfRange if invalid.
void Board::setCard(const Letter &l, const Number &n, Card *c) {
    validatePosition(l, n);
    int row = toIndex<Letter>(l), column = toIndex<Number>(n);
    delete board[row][column];
    board[row][column] = c;
}

// Swaps two cards on the board without deleting them.
// Params: l1,n1 and l2,n2 (positions).
// Returns: nothing.
// Throws: OutOfRange if any position invalid.
void Board::swapCards(const Letter &l1, const Number &n1, const Letter &l2, const Number &n2) {
    validatePosition(l1, n1);
    validatePosition(l2, n2);

    int row1 = toIndex<Letter>(l1);
    int col1 = toIndex<Number>(n1);
    int row2 = toIndex<Letter>(l2);
    int col2 = toIndex<Number>(n2);

    Card* temp = board[row1][col1];
    board[row1][col1] = board[row2][col2];
    board[row2][col2] = temp;
}

// Turns all cards face down (including non-center cards).
// Params: none.
// Returns: nothing.
void Board::allFacesDown() {
    for (int i = 0; i < GameParameters::BoardSize; ++i) {
        for (int j = 0; j < GameParameters::BoardSize; ++j) {
            if (board[i][j]) {
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
                const Card* card = b.board[row][col];
                if (card) {
                    os << (*card)(cardRow);
                } else {
                    os << "   "; // Blank card
                }
                if (col < GameParameters::BoardSize - 1) os << ' '; // space between cards in row
            }
            os << '\n';
        }
        os << '\n';
    }

    // construct board bottom margin
    int sizeOfCard = GameParameters::NumRowsCard;
    std::string bottomMargin(GameParameters::BoardPadding + 1, ' ');

    for (int i = 1; i <= GameParameters::BoardSize; ++i) {
        std::string num = std::to_string(i);

        int leftPadding  = (sizeOfCard - static_cast<int>(num.size())) / 2;
        int rightPadding = sizeOfCard - leftPadding - static_cast<int>(num.size());

        std::string belowCard(leftPadding, ' ');
        belowCard += num;
        belowCard += std::string(rightPadding, ' ');

        belowCard += std::string(1, ' ');

        bottomMargin += belowCard;
    }
    os << bottomMargin << '\n';

    return os;
}
