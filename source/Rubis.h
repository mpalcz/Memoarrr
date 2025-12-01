#ifndef RUBIS_H
#define RUBIS_H

#include <iostream>

class RubisDeck;

class Rubis {
  friend class RubisDeck; // establish friendship for private constructor access

  private:
    // Instance variables
    int numRubis;

    // Constructor
    Rubis(int val); // private constructor
    ~Rubis(); // is this necessary?

  public:
    // int conversion operator (const since we do not change the object)
    operator int() const { return numRubis; }
    friend std::ostream &operator<<(std::ostream &os, const Rubis &obj);
};

#endif