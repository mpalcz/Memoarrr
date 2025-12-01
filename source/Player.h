#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Rubis; // forward reference to Rubis class (if only dealing with pointers and references)

class Player {

  public:
    // modern version of enums (cannot implicitly cast to integer)
    enum Side { top, bottom, left, right };

    // Constructors and destructor
    Player(std::string n, Side s) : name(n), side(s), active(true), numRubies(0), endOfGame(false) {}
    Player() : name(""), side(top) {} // default constructor
    ~Player();

    // Public interface
    std::string getName() const;
    void setActive(bool);
    bool isActive() const;
    int getNRubies() const;
    void addRubis(const Rubis &);
    void setDisplayMode(bool endOfGame);
    Side getSide() const;
    void setSide(Side);

    // Getters and setters
    std::string sideToString() const;

    // Friend functions
    friend std::ostream &operator<<(std::ostream &os, const Player &obj);

  private:
    // Instance variables
    std::string name;
    bool active;
    int numRubies;
    Side side;
    bool endOfGame;
};

#endif