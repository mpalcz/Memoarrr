#include <Card.h>

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

// function operator() - returns a single row of of the card (1 of 3)
std::string Card::operator()(int row) const {
    if (isBlank) {
        return "   "; // print spaces for middle board piece
    }

    // if the card is face down ever row is zzz
    if (!faceUp) {
        return "zzz";
    };

    char aChar = animalLetter(animal);
    char bChar = backgroundLetter(background);
    std::string s(3, bChar); // initialize with all background chars (like yyy)

    // if its the second row, make the second char the animal
    if (row == 2) {
        s[1] = aChar;
    }

    return s;
}

/*
// used for board turnFaceUp turnFaceDown
bool Card::turnFaceUp() {
    if (this->isFaceUp()) {
        return false;
    }
    faceUp = true;
    return true;
}

bool Card::turnFaceDown() {
    if (!this->isFaceUp()) {
        return false;
    }
    faceUp = false;
    return true;
}
*/

// print the entire card (3 rows)
std::ostream &operator<<(std::ostream &os, const Card &c) {
    for (int row = 0; row < c.getNRows(); ++row) {
        std::string rowString = c(row);
        os << rowString << std::endl;
    }
    return os;
}