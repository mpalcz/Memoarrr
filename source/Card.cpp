#include <Card.h>

/*
############## ENUM HELPERS ##################
map enums to chars for output
make these static for encapsulation within this file
*/

static char animalLetter(FaceAnimal a) {
    switch (a) {
    case Crab: return 'C';
    case Penguin: return 'P';
    case Octopus: return 'O';
    case Turtle: return 'T';
    case Walrus: return 'W';
    }
    return '?'; // fallback (should be impossible)
}

static char backgroundLetter(FaceBackground b) {
    switch (b) {
    case Red: return 'r';
    case Green: return 'g';
    case Purple: return 'p';
    case Blue: return 'b';
    case Yellow: return 'y';
    }
    return '?';
}

/*############## CLASS DEFINITIONS ##################*/

// constructor
Card::Card(FaceAnimal a, FaceBackground b) : animal(a), background(b) {}

// function operator() - returns a single row of of the card (1 of 3)
std::string Card::operator()(int row) const {
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

// print the entire card (3 rows)
std::ostream &operator<<(std::ostream &os, const Card &c) {
    for (int row = 0; row < c.getNRows(); ++row) {
        std::string rowString = c(row);
        std::cout << rowString << std::endl;
    }
}