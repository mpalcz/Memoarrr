#include "Card.h"

/*
############## ENUM HELPERS ##################
map enums to chars for output
make these static for encapsulation within this file
*/

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

std::string Card::operator()(int row) const {
    if (isBlank) return "   ";
    if (!faceUp) return "zzz";

    // Card is square shaped (thus NumColumnsCard = NumRowsCard)
    std::string s(GameParameters::NumRowsCard, backgroundLetter(background));
    int middleIndex = GameParameters::NumRowsCard/2;
    if (row == middleIndex) s[middleIndex] = animalLetter(animal);
    return s;
}

std::ostream& operator<<(std::ostream& os, const Card& c) {
    for (int row = 0; row < c.getNRows(); ++row) os << c(row) << '\n';
    return os;
}