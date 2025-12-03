// Rubis.h: Header for Rubis class representing rubis rewards (1-4).

#ifndef RUBIS_H
#define RUBIS_H

#include <iostream>
#include <stdexcept>
#include "GameParameters.h"

class RubisDeck;

class Rubis {
  friend class RubisDeck; // establish friendship for private constructor access

  private:
    // Instance variables
    int numRubis;

    // Constructor
    Rubis(int val) {
      if (val == 0 || val >= static_cast<int>(GameParameters::RubisDistribution.size())) throw std::invalid_argument("Rubis value must be between 1 and 4");
      numRubis = val;
    }

  public:
    operator int() const { return numRubis; }
    friend std::ostream& operator<<(std::ostream& os, const Rubis& r) {
        os << r.numRubis << " rubis";
        return os;
    }
};

#endif