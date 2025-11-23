#include "Player.h"

using namespace std;

// Define player class
string Player::getName() const { return name; }

void Player::setActive(bool activityStatus) {
  if (activityStatus != active)
    active = activityStatus;
}

bool Player::isActive() const { return active; }

int Player::getNRubies() const { return numRubies; }

void Player::addRubis(const Rubis &) {}

void Player::setDisplayMode(bool endOfGame) {}

Player::Side Player::getSide() const { return side; }

void Player::setSide(Side newSide) {
  if (newSide != side)
    side = newSide;
}

string Player::sideToString() const {
  switch (side) {
  case Player::left: return "left";
  case Player::right: return "right";
  case Player::top: return "top";
  case Player::bottom: return "bottom";
  default: return "unknown";
  }
}

// Operator<< definition
ostream &operator<<(ostream &os, const Player &obj) {
  os << obj.name << ": ";
  if (!obj.endOfGame) {
    os << obj.sideToString() << (obj.active ? " (active)" : " (inactive)") << endl;
  } else {
    os << obj.getNRubies() << " rubies" << endl;
  }
  return os;
}