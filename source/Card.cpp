// Card.cpp: Implements the Card class for representing game cards with animals and backgrounds.

#include "Card.h"

// Helper: Maps FaceAnimal enum to char for printing.
// Params: a (FaceAnimal).
// Returns: Char representation.
static char animalLetter(Card::FaceAnimal a) {
    switch (a) {
    case Card::FaceAnimal::Crab: return 'C';
    case Card::FaceAnimal::Penguin: return 'P';
    case Card::FaceAnimal::Octopus: return 'O';
    case Card::FaceAnimal::Turtle: return 'T';
    case Card::FaceAnimal::Walrus: return 'W';
    default: return '?'; // sentinel
    }
}

// Helper: Maps FaceBackground enum to char for printing.
// Params: b (FaceBackground).
// Returns: Char representation.
static char backgroundLetter(Card::FaceBackground b) {
    switch (b) {
    case Card::FaceBackground::Red: return 'r';
    case Card::FaceBackground::Green: return 'g';
    case Card::FaceBackground::Purple: return 'p';
    case Card::FaceBackground::Blue: return 'b';
    case Card::FaceBackground::Yellow: return 'y';
    default: return '?'; // sentinel value
    }
}

/*############## CLASS DEFINITIONS ##################*/

// Builds one horizontal slice (row) of the card drawing.
// Params: row (row index inside the card).
// Returns: string for that row.
std::string Card::operator()(int row) const {
    if (!faceUp) return "zzz";

    // Card is square shaped (thus NumColumnsCard = NumRowsCard)
    std::string s(GameParameters::NumRowsCard, backgroundLetter(background));
    int middleIndex = GameParameters::NumRowsCard/2;
    if (row == middleIndex) s[middleIndex] = animalLetter(animal);
    return s;
}

// Prints the whole card by calling operator() for each internal row.
// Params: os (output stream), c (const Card).
// Returns: os for chaining.
std::ostream& operator<<(std::ostream& os, const Card& c) {
    for (int row = 0; row < c.getNRows(); ++row) os << c(row) << '\n';
    return os;
}
