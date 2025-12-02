#include "Board.h"
#include "CardDeck.h"
#include "Exceptions.h"

/*
bool Board::checkPositionValidity(int row, int column) const{
    std::tuple<int, int> cardPosition(row, column);
    if (row < 0 || row >= Game::BoardSize || column < 0 || column >= Game::BoardSize || cardPosition == Game::CenterPosition) {
        return false;
    }
    return true;
};
*/

void Board::validatePosition(const Letter &l, const Number &n) const{
    int row = toIndex<Board::Letter>(l), column = toIndex<Board::Number>(n);
    std::tuple<int, int> cardPosition(row, column);
    if (row < 0 || row >= Game::BoardSize || column < 0 || column >= Game::BoardSize || cardPosition == Game::CenterPosition) {
        throw InvalidPosition();
    }
};

Board::Board() {
    // generate deck of cards and shuffle them
    CardDeck &boardDeck = CardDeck::make_CardDeck();

    for (int i = 0; i < Game::BoardSize; ++i) {
        for (int j = 0; j < Game::BoardSize; ++j) {
            if (i == Game::CenterRow && j == Game::CenterCol) {
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
    for (int i = 0; i < Game::BoardSize; ++i) {
        for (int j = 0; j < Game::BoardSize; ++j) {
            if (!(i == Game::CenterRow && j == Game::CenterCol)) {
                board[i][j]->turnFaceDown();
            }
        }
    }
}

/*
std::ostream &operator<<(std::ostream &os, const Board &b) {

    for (int row = 0; row < 5; ++row) {
        for (int card_row = 0; card_row < 3; ++card_row) {
            // add letters at the beginning of each row (or blank spaces)
            if (card_row == 2) {
                char c = 'A' + row; // first row is 'A', second is 'B' etc. by incrementing ascii value
                os << c << "    ";
            } else {
                os << "     ";
            }

            for (int col = 0; col < 5; ++col) {
                const Card &card = b.board[row][col]; // needs to be const since board is const
                std::string out = card(card_row);
                os << out << " ";
            }
            os << std::endl; // end line after all 5 card rows were printed
        }
        os << "\n"; // leave a line in between before the next card row
    }
    os << "\n";

    // print numbers at the bottom
    os << " 1   2   3   4   5 ";
    return os;
}
*/

// Printing unchanged — still perfect match to PDF
// Go line by line downwards
std::ostream& operator<<(std::ostream& os, const Board& b) {
    for (int row = 0; row < Game::BoardSize; ++row) {
        for (int cardRow = 0; cardRow < Game::NumRowsCard; ++cardRow) {
            // Print left margin of the board
            os << ((cardRow == Game::NumRowsCard/2) ? std::string(1, 'A' + row) : " ");
            os << std::string(Game::BoardPadding, ' ');

            // Print the horizontal cards in the row
            for (int col = 0; col < Game::BoardSize; ++col) {
                const Card* card = b.board[row][col].get();
                os << (*card)(cardRow);
                if (col < 4) os << ' ';
            }
            os << '\n';
        }
        os << std::string(Game::BoardPadding, '\n');
    }
    os << std::string(Game::BoardPadding, ' ') << " 1   2   3   4   5\n";
    return os;
}