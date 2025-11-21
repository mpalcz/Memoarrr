#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class Rubis; // forward reference to Rubis class (if only dealing with pointers and references)

class Player {

    public:
        // Constructors and destructor
        Player(std::string);
        ~Player();

        // Enumeration
        enum Side { // modern version of enums (cannot implicitly cast to integer)
            top,
            bottom,
            left,
            right
        };

        // Public interface
        std::string getName() const;
        void setActive(bool);
        bool isActive() const;
        int getNRubies() const;
        void addRubis(const Rubis&);
        void setDisplayMode(bool endOfGame);
        Side getSide() const;
        void setSide(Side);

        // Getters and setters
        
        // Friend functions
        friend std::ostream& operator<<(std::ostream& os, const Player& obj);
    
    private:
        std::string name;
        bool active;
        int numRubies;
        Side side;
};

#endif