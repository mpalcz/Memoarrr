#include "Player.h"

using namespace std;

// Define player class
string Player::getName() const {
    return name;
}

void Player::setActive(bool activityStatus) {
    active = activityStatus;
}

bool Player::isActive() const {
    return active;
}

int Player::getNRubies() const {
    return numRubies;
}

void Player::addRubis(const Rubis&) {
    
}

void Player::setDisplayMode(bool endOfGame) {

}

Side Player::getSide() const {
    return side;
}

void Player::setSide(Side newSide) {
    side = newSide;
}