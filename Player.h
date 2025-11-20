#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Rubis; // forward reference to Rubis class (if only dealing with pointers and references)

class Player {

    private:
        std::string name;
        bool isActive;
        int numRubies;

    public:
        // Constructors and destructor
        Player(std::string);
        ~Player();

        // Enumeration
        enum Side {
            top,
            bottom,
            left,
            right
        };

        // Public interface
        std::string getName() const;
        void setActive(bool);
        bool isActive();
        int getNRubies() const;
        void addRubis(const Rubis&);
        void setDisplayMode(bool endOfGame);
        Side Player::getSide();
        void Player::setSide(Side);

        // Getters and setters
        
        // Friend functions
        friend std::ostream& operator<<(std::ostream& os, const Player& obj);

};

#endif