#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Rubis; // forward reference

class Player {

  public:
    // either change it to be an enum class or move to GameEnums.h file
    enum class Side { top, bottom, left, right };

    // Constructors and destructor
    Player(std::string n, Side s) : name(n), side(s) {}
    Player() : name(""), side(Side::top) {} // default constructor (may need to delete or change)
    ~Player(); // is this necessary?

    // Public interface (inline functions)
    std::string getName() const { return name; };
    void setActive(bool newStatus) { active = newStatus; };
    bool isActive() const { return active; };
    int getNRubies() const { return numRubies; };
    void addRubis(const Rubis &rubisToAdd) { numRubies += rubisToAdd; };
    void setDisplayMode(bool endOfGame) { endOfGameDisplay = endOfGame; };
    Side getSide() const { return side; };
    void setSide(Side newSide) { side = newSide; };

    // Getters and setters
    std::string sideToString() const;

    // Friend functions
    friend std::ostream &operator<<(std::ostream &os, const Player &obj);

  private:
    // Instance variables with default intialization
    std::string name;
    Side side;
    bool active = true;
    int numRubies = 0;
    bool endOfGameDisplay = false;
};

#endif