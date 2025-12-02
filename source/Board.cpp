#include <Board.h>
#include <CardDeck.h>
#include <DeckFactory.h>
#include <stdexcept>
#include <GameParameters.h>

// small class for NoMoreCards exception
class NoMoreCards : public std::runtime_error {
  public:
    NoMoreCards() : std::runtime_error("No more cards to draw from in the deck!") {}
};

class InvalidPosition : public std::runtime_error {
    public:
        InvalidPosition() : std::runtime_error("Card position chosen is invalid") {}
};

Board::Board() {
    // generate deck of cards and shuffle them
    CardDeck &boardDeck = CardDeck::make_CardDeck();
    boardDeck.shuffle();

    // add each card to the board but skip the middle one
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            // if its not the middle spot then add the card (0 indexed here)
            if (!(i == 2 && j == 2)) {
                if (boardDeck.isEmpty()) {
                    throw NoMoreCards();
                } else {
                    board[i][j] = *boardDeck.getNext(); // get next returns a card pointer so dereference it
                }
            }
        }
    }
}

bool Board::checkPositionValidity(int row, int column) const{
    std::tuple<int, int> cardPosition(row, column);
    if (row < 0 || row >= Game::boardSize || column < 0 || column >= Game::boardSize || cardPosition == Game::emptyCardPosition) {
        return false;
    }
    return true;
};

bool Board::isFaceUp(const Letter &l, const Number &n) const{
    const Card *card = getCard(l, n);
    return card->isFaceUp();
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

Card *Board::getCard(const Letter &l, const Number &n){
    int row = toIndex<Board::Letter>(l), column = toIndex<Board::Number>(n);
    if (!checkPositionValidity(row, column)) throw InvalidPosition();
    Card *card = &board[row][column];
    return card;
}

void Board::setCard(const Letter &l, const Number &n, Card *c) {
    Card *card = getCard(l, n);
    card = c;
}

void Board::allFacesDown() {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            // skip middle card again
            if (!(i == 2 && j == 2)) {
                Card card = board[i][j];
                card.turnFaceDown();
            }
        }
    }
}

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