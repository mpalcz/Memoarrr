// Rubis.h: Header for Rubis class representing ruby rewards (1-4).

#ifndef RUBIS_H
#define RUBIS_H

#include <iostream>
#include <stdexcept>
#include "GameParameters.h"

class RubisDeck;

// Represents a ruby reward token (1–4 rubies).
class Rubis {
  // Friend classes
  friend class RubisDeck; // establish friendship for private constructor access

  private:
    // Instance variables
    int numRubies;

    // Constructor (private)
    // Params: val (int rubies).
    // Throws: invalid_argument if val not in [1,4].
    Rubis(int val) {
      if (val == 0 || val >= static_cast<int>(GameParameters::RubisDistribution.size()))
          throw std::invalid_argument("Rubies value must be between 1 and 4");
      numRubies = val;
    }

  public:
    // Conversion operator
    operator int() const { return numRubies; }

    // Prints the Rubis as "1 ruby" or "2 rubies".
    // Params: os (output stream), r (const Rubis&).
    // Returns: os for chaining.
    friend std::ostream& operator<<(std::ostream& os, const Rubis& r) {
        os << r.numRubies << " rub" << (r.numRubies == 1 ? "y" : "ies");
        return os;
    }
};

#endif
