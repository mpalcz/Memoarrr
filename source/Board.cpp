#include "Board.h"
#include "CardDeck.h"
#include "Exceptions.h"

void Board::validatePosition(const Letter &l, const Number &n) const{
    int row = toIndex<Board::Letter>(l), column = toIndex<Board::Number>(n);
    std::tuple<int, int> cardPosition(row, column);
    if (row < 0 || row >= GameParameters::BoardSize || column < 0 || column >= GameParameters::BoardSize || cardPosition == GameParameters::CenterPosition) {
        throw OutOfRange();
    }
};

Board::Board() {
    // generate deck of cards and shuffle them
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

// GETTERS
Card *Board::getCard(const Letter &l, const Number &n) {
    validatePosition(l, n);
    int row = toIndex<Board::Letter>(l), column = toIndex<Board::Number>(n);
    return board[row][column].get();
}

const Card *Board::getCard(const Letter &l, const Number &n) const {
    validatePosition(l, n);
    int row = toIndex<Board::Letter>(l), column = toIndex<Board::Number>(n);
    return board[row][column].get();
}

bool Board::turnFaceUp(const Letter &l, const Number &n) {
    Card *card = getCard(l, n);
    if (card->isFaceUp()) return false;
    card->turnFaceUp();
    return true;
}

bool Board::turnFaceDown(const Letter &l, const Number &n) {
    Card *card = getCard(l, n);
    if (!card->isFaceUp()) return false;
    card->turnFaceDown();
    return true;
}

void Board::setCard(const Letter &l, const Number &n, Card *c) {
    // Check validity
    validatePosition(l, n);
    int row = toIndex<Board::Letter>(l), column = toIndex<Board::Number>(n);
    board[row][column].reset(c);
}

void Board::allFacesDown() {
    for (int i = 0; i < GameParameters::BoardSize; ++i) {
        for (int j = 0; j < GameParameters::BoardSize; ++j) {
            if (!(i == GameParameters::CenterRow && j == GameParameters::CenterCol)) {
                board[i][j]->turnFaceDown();
            }
        }
    }
}


// Go line by line downwards
std::ostream& operator<<(std::ostream& os, const Board& b) {
    for (int row = 0; row < GameParameters::BoardSize; ++row) {
        for (int cardRow = 0; cardRow < GameParameters::NumRowsCard; ++cardRow) {
            // Print left margin of the board
            os << ((cardRow == GameParameters::NumRowsCard/2) ? std::string(1, 'A' + row) : " ");
            os << std::string(GameParameters::BoardPadding, ' ');

            // Print the horizontal cards in the row
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