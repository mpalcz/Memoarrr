#include <Board.h>
#include <CardDeck.h>
#include <DeckFactory.h>
#include <stdexcept>

// small class for NoMoreCards exception
class NoMoreCards : public std::runtime_error {
  public:
    NoMoreCards() : std::runtime_error("No more cards to draw from in the deck!") {}
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

void Board::setCard(const Letter &l, const Number &n, Card *c) {
    int lIndex = l - 1; // implicit conversion to int
    int nIndex = n - 1;

    if ((lIndex > 4 || lIndex < 0 || nIndex > 4 || nIndex < 0)) {
        throw std::out_of_range("Invalid index for a card");
    } else {
        board[lIndex][nIndex] = *c;
    }
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