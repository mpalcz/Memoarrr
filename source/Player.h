// Player.h
#ifndef PLAYER_H
#define PLAYER_H

#include "GameParameters.h"
#include <string>
#include <iostream>

class Rubis; // forward reference

// Represents one player: name, side, active flag, rubies, etc.
class Player {

  public:
    // ==== Enums ====
    // either change it to be an enum class or move to GameEnums.h file
    enum class Side { top, bottom, left, right };

    // ==== Constructors and destructor ====
    Player(std::string n, Side s) : name(n), side(s) {}
    Player() : name(""), side(Side::top) {} // default constructor

    // ==== Public interface (inline functions) ====
    const std::string& getName() const { return name; } // should it return const string or string
    void setActive(bool newStatus) { active = newStatus; }
    bool isActive() const { return active; }
    int getNRubies() const { return numRubies; }
    void addRubis(const Rubis &rubisToAdd);
    void setDisplayMode(bool endOfGame);
    Side getSide() const { return side; }
    void setSide(Side newSide) { side = newSide; }

    // Getters and helpers
    std::string sideToString() const;

    // ==== Friend functions ====
    friend std::ostream &operator<<(std::ostream &os, const Player &obj);

  private:
    // ==== Instance variables with default intialization ====
    std::string name;
    Side side;
    bool active = true;
    int numRubies = 0;
    bool endOfGameDisplay = false;
};

#endif
